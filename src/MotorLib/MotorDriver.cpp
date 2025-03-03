#pragma once 
#include "MotorLib.h"

MotorDriver::MotorDriver(int PWM_pin, int DIR_pin, int I2C_channel)
    : PWM_pin(PWM_pin), DIR_pin(DIR_pin), I2C_channel(I2C_channel) {
    pinMode(DIR_pin, OUTPUT);
    softPwmCreate(PWM_pin, 0, 255);
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