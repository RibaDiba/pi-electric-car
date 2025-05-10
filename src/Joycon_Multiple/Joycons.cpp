#pragma once
#include "Joycons.h"

/*
Note for the future: this codebase has a lot of issues 
    - the way accel is handled is scuffed 
    - spinning right and left is given a constant max speed in the other file 
    - always sends a speed of 2 no matter what (doesn't affect stopping because it actually calls a static function called stop)
    - THE STATE VARIABLE IS LOCAL TO THE FUNCTION??? WHY 

    terrible code that works
    also i was too lazy to change the names of the file (this is only for 1 joycon)
*/

Joycons::Joycons(std::vector<int>& arrOfSpeeds, std::vector<MotorDriver*> motors)
    : arrOfSpeeds(arrOfSpeeds), Motors(motors) {
    leftJoycon = hid_open(leftVendorId, leftProductId, NULL);
}

long Joycons::map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int Joycons::initJoycons() {
    if (hid_init()) {
        std::cerr << "Failed to Init HID" << std::endl;
        return 1;
    }

    leftJoycon = hid_open(leftVendorId, leftProductId, NULL);
    return leftJoycon ? 0 : 1;
}

JoyconsState Joycons::handleJoystickValues(uint8_t rawX, uint8_t rawY) {
    rawX = ((rawX & 0x0F) << 4) | ((rawX & 0xF0) >> 4);
    int joystickX = map(static_cast<int>(rawX), 55, 215, 75, 190);
    int joystickY = static_cast<int>(rawY);

    if (joystickY > 210) return JoyconsState::FOWARDS;
    if (joystickY < 80) return JoyconsState::BACKWARDS;
    if (joystickX > 160) return JoyconsState::SPIN_RIGHT;
    if (joystickX < 80) return JoyconsState::SPIN_LEFT;
    return JoyconsState::STOPPED;
}

int Joycons::handleSpeed(int speedSent, int &currentSpeed, JoyconsState state) {
    int accelStep = 2; // Rate of acceleration per cycle

    if (state == JoyconsState::STOPPED) {
        speedSent = 0; // Target speed is 0 when stopped, but decelerate smoothly
    }

    if (currentSpeed < speedSent) {
        currentSpeed = std::min(currentSpeed + accelStep, speedSent);
    } else if (currentSpeed > speedSent) {
        currentSpeed = std::max(currentSpeed - accelStep, speedSent);
    }

    return currentSpeed;
}

int Joycons::run() {
    unsigned char leftData[61];
    auto lastPressTimeUp = std::chrono::steady_clock::now();
    auto lastPressTimeDown = std::chrono::steady_clock::now();
    const std::chrono::milliseconds debounceInterval(200);

    int currentSpeed = 0;
    int currentSpeedIndex = 0;
    int targetSpeed = arrOfSpeeds[0];

    JoyconsState lastState = JoyconsState::STOPPED; 

    while (true) {
        int rawLeftData = hid_read(leftJoycon, leftData, sizeof(leftData));
        uint8_t buttonData = leftData[5];
        int buttonState = static_cast<int>(buttonData);
        auto now = std::chrono::steady_clock::now();

        if (buttonState == 1 && now - lastPressTimeDown > debounceInterval) {
            currentSpeedIndex = std::max(0, currentSpeedIndex - 1);
            targetSpeed = arrOfSpeeds[currentSpeedIndex];
            lastPressTimeDown = now;
        } else if (buttonState == 2 && now - lastPressTimeUp > debounceInterval) {
            currentSpeedIndex = std::min(static_cast<int>(arrOfSpeeds.size()) - 1, currentSpeedIndex + 1);
            targetSpeed = arrOfSpeeds[currentSpeedIndex];
            lastPressTimeUp = now;
        }

        JoyconsState state = handleJoystickValues(leftData[7], leftData[8]);
        int speedSent = handleSpeed(targetSpeed, currentSpeed, state);

        if (speedSent > 0 && state == JoyconsState::STOPPED) {
            if (lastState == JoyconsState::SPIN_RIGHT || lastState == JoyconsState::SPIN_LEFT) {
                lastState = state;
            } else {
                state = lastState;  
            }
        } else {
            lastState = state;
        }

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

        std::cout << "State: " << state << " Last State: " << lastState << " Speed: " << speedSent << std::endl;
    }

    return 0;
}
