#pragma once
#include "Joycons.h"

Joycons::Joycons(std::vector<int>&arrOfSpeeds, std::vector<MotorDriver*> motors)
    : arrOfSpeeds(arrOfSpeeds), Motors(motors) {
    // init both joycons
    leftJoycon = hid_open(leftVendorId, leftProductId, NULL);
    rightJoycon = hid_open(rightVendorId, rightProductId, NULL);
}

// convienent map function
long Joycons::map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// see if joycon is active 
int Joycons::initJoycons() {
    if (hid_init()) {
        std::cerr << "Failed to Init HID" << std::endl;
        return 1;
    }

    leftJoycon = hid_open(leftVendorId, leftProductId, NULL);
    rightJoycon = hid_open(rightVendorId, rightProductId, NULL);
    if (!leftJoycon || !rightJoycon) {
        return 1;
    } else {
        return 0;
    }
}

JoyconsState Joycons::handleJoystickValues(uint8_t rawX, uint8_t rawY) {
    rawX = ((rawX & 0x0F) << 4) | ((rawX & 0xF0) >> 4);

    int joystickX = static_cast<int>(rawX);
    int joysticky = static_cast<int>(rawY);

    // joystickX needs to be fixed (my case only?)
    joystickX = map(joystickX, 55, 215, 75, 190);
    int joystickY = static_cast<int>(rawY);

    // output for joystick debugging
    // std::cout << "Joystick X: " << joystickX << " Joystick Y: " << joystickY << std::endl;

    if (joystickY > 210) {
         return JoyconsState::FOWARDS;
    } else if (joystickY < 80) {
         return JoyconsState::BACKWARDS;
    } else if (joystickX > 160) {
         return JoyconsState::SPIN_RIGHT;
    } else if (joystickX < 80) {
         return JoyconsState::SPIN_LEFT;
    } else {
         return JoyconsState::STOPPED;
    }

}

int Joycons::handleSpeed(uint8_t rawX, uint8_t rawY, int targetSpeed, int &currentSpeed) {
    int joystickY = static_cast<int>(rawY);
    int mappedSpeed;

    if (joystickY < 130 && joystickY > 110) {
        mappedSpeed = 0;
    } else if (joystickY < 110) {
        mappedSpeed = 0;
    } else {
        mappedSpeed = map(joystickY, 130, 186, 0, targetSpeed);
    }

    // Acceleration logic
    int accelStep = 2; // Change per cycle
    if (currentSpeed < mappedSpeed) {
        currentSpeed = std::min(currentSpeed + accelStep, mappedSpeed);
    } else if (currentSpeed > mappedSpeed) {
        currentSpeed = std::max(currentSpeed - accelStep, mappedSpeed);
    }

    return currentSpeed;
}

int Joycons::run() {
    unsigned char rightData[61];
    unsigned char leftData[61];

    auto lastPressTimeUp = std::chrono::steady_clock::now();
    auto lastPressTimeDown = std::chrono::steady_clock::now();
    const std::chrono::milliseconds debounceInterval(200);

    int currentSpeed = 0;
    int currentSpeedIndex = 0;
    int targetSpeed = arrOfSpeeds[0];

    while (true) {
        int rawRightData = hid_read(rightJoycon, rightData, sizeof(rightData));
        int rawLeftData = hid_read(leftJoycon, leftData, sizeof(leftData));

        uint8_t buttonData = leftData[5];
        int buttonState = static_cast<int>(buttonData);
        auto now = std::chrono::steady_clock::now();

        if (buttonState == 1 && now - lastPressTimeDown > debounceInterval) {
            currentSpeedIndex = std::max(0, currentSpeedIndex - 1);
            targetSpeed = arrOfSpeeds[currentSpeedIndex];
            lastPressTimeDown = now;
        } else if (buttonState == 2 && now - lastPressTimeUp > debounceInterval) {
            currentSpeedIndex = std::min((int)arrOfSpeeds.size() - 1, currentSpeedIndex + 1);
            targetSpeed = arrOfSpeeds[currentSpeedIndex];
            lastPressTimeUp = now;
        }

        JoyconsState state = handleJoystickValues(leftData[7], leftData[8]);
        int speedSent = handleSpeed(rightData[10], rightData[11], targetSpeed, currentSpeed);

        switch (state) {
            case JoyconsState::FOWARDS:
                forwards(speedSent);
                break;
            case JoyconsState::BACKWARDS:
                backwards(speedSent);
                break;
            case JoyconsState::SPIN_RIGHT:
                spinRight(speedSent);
                break;
            case JoyconsState::SPIN_LEFT:
                spinLeft(speedSent);
                break;
            default:
                stop();
        }

        std::cout << "State: " << state << " Speed: " << speedSent << std::endl;

        // std::this_thread::sleep_for(std::chrono::milliseconds(20)); // Smooth acceleration delay
    }

    return 0;
}