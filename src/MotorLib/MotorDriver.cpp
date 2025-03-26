#pragma once 
#include "MotorLib.h"
#include <algorithm>

MotorDriver::MotorDriver(int PWM_pin, int DIR_pin, int I2C_channel)
    : PWM_pin(PWM_pin), DIR_pin(DIR_pin), I2C_channel(I2C_channel) {
    pinMode(DIR_pin, OUTPUT);
    softPwmCreate(PWM_pin, 0, 255);
}

int MotorDriver::mapToPWM(int speed) {
    speed = std::clamp(speed, -255, 255);
    int pwmValue = 150 + (speed * 50) / 255;
    return pwmValue;
}

MotorDriver::MotorDriver(int PWM_pin) 
    : PWM_pin(PWM_pin) {
    // softPwmCreate(PWM_pin, 0, 255);
    pinMode(PWM_pin, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(2000);
    pwmSetClock(192);
}

MotorDriver::MotorDriver(int LPWM_pin, int RPWM_pin) 
    : LPWM_pin(LPWM_pin), RPWM_pin(RPWM_pin) {
    // pinMode(LPWM_pin, OUTPUT);
    // pinMode(RPWM_pin, OUTPUT);

    // softPwmCreate(LPWM_pin, )
}

// function is set to global for now (debug purposes)
void MotorDriver::setSpeed(int speed, int dir) {
    if (dir == 0) {
        digitalWrite(DIR_pin, LOW);
    } else if (dir == 1) {
        digitalWrite(DIR_pin, HIGH);
    } else {
        std::cout << "Invalid Direction Value" << std::endl;
        return;
    }
    softPwmWrite(PWM_pin, speed);
}

// sets speed for spark motor drivers 
void MotorDriver::setSpeedNew(int speed, int dir) {
}

void MotorDriver::sparkSetSpeed(int speed) {
    // softPwmWrite(PWM_pin, speed);
    pwmWrite(PWM_pin, speed);
}

// spins wheel in both directions (useful for debugging)
void MotorDriver::debug_driver(int time) {
    setSpeed(100, 0);
    std::cout << "Motor PWM Pin moving 0: " << PWM_pin << std::endl;
    delay(time);
    setSpeed(100, 1);
    std::cout << "Motor PWM Pin moving 1: " << PWM_pin << std::endl;
    delay(time);
    setSpeed(0, 0);
}

void MotorDriver::calibrateSpark() {

    std::cout << "Starting calibration sequence..." << std::endl;



    // Step 1: Send full forward (2.0 ms pulse)

    // This should signal full throttle to the SPARK controller.

    std::cout << "Sending full forward (PWM value = 200) for 3 seconds..." << std::endl;

    pwmWrite(PWM_pin, 200);

    delay(3000);  // Hold full forward for 3 seconds (adjust timing as needed)



    // Step 2: Drop to neutral (1.5 ms pulse)

    // This tells the controller the neutral throttle position.

    std::cout << "Setting to neutral (PWM value = 150) for 2 seconds..." << std::endl;

    pwmWrite(PWM_pin, 150);

    delay(2000);  // Hold neutral for 2 seconds
}