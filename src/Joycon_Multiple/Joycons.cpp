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

int Joycons::handleSpeed(uint8_t rawX, uint8_t rawY, int speed) {
    int joystickX = static_cast<int>(rawX);
    int joysticky = static_cast<int>(rawY);
    int speedReturn;



    // output for joystick debugging
    // std::cout << "Joystick X: " << joystickX << " Joystick Y: " << joystickY << std::endl;
    if (joysticky < 130 && joysticky > 110) {
        joysticky = 0;
        speedReturn = 0;
    } else if (joysticky < 110) {
        joysticky = 0;
        speedReturn = 0;
    } else {
        speedReturn = map(joysticky, 130, 186, 0, speed);
    }

    return speedReturn;
}   

int Joycons::run() {
    unsigned char rightData[61];
    unsigned char leftData[61];

    // debounce for button presses
    auto lastPressTimeUp = std::chrono::steady_clock::now();
    auto lastPressTimeDown = std::chrono::steady_clock::now();
    const std::chrono::milliseconds debounceInterval(200);

    int currentSpeed = arrOfSpeeds[0];
    int currentSpeedIndex = 0;

    while (true) {
        int rawRightData = hid_read(rightJoycon, rightData, sizeof(rightData));
        int rawleftData = hid_read(leftJoycon, leftData, sizeof(leftData));
    
        // handle button data
        uint8_t buttonData = leftData[5];
        int buttonState = static_cast<int>(buttonData);
        bool upButtonState = false;
        bool downButtonState = false;

        if (buttonState == 1) {  // Down button pressed
            auto now = std::chrono::steady_clock::now();
            if (now - lastPressTimeDown > debounceInterval) {
                currentSpeedIndex--;  // Decrease the index
                if (currentSpeedIndex < 0) {
                        currentSpeedIndex = 0;  // Prevent going below zero
                }
                currentSpeed = arrOfSpeeds[currentSpeedIndex];  // Update the speed
                downButtonState = true;
                lastPressTimeDown = now;  // Update the last press time for down button
            }
        }
        else if (buttonState == 2) {  // Up button pressed
            auto now = std::chrono::steady_clock::now();
            if (now - lastPressTimeUp > debounceInterval) {
                currentSpeedIndex++;  // Increase the index
                if (currentSpeedIndex >= arrOfSpeeds.size()) {
                        currentSpeedIndex = arrOfSpeeds.size() - 1;  // Prevent going beyond the last index
                }
                currentSpeed = arrOfSpeeds[currentSpeedIndex];  // Update the speed
                upButtonState = true;
                lastPressTimeUp = now;  // Update the last press time for up button
            }
        } else {
            upButtonState = false;
            downButtonState = false;
        }

        int speedSent = currentSpeed;

        JoyconsState state = handleJoystickValues(leftData[7], leftData[8]);
        speedSent = handleSpeed(rightData[10], rightData[11], speedSent);

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
    }

    return 0;
}