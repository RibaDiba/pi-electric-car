#pragma once
#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>
#include <vector>
#include <cstdint> // For uint8_t

class MotorDriver {
public:
    int PWM_pin;
    int DIR_pin;
    int I2C_channel;

    MotorDriver(int PWM_pin, int DIR_pin, int I2C_channel);
    void setSpeed(int speed, int dir);
    void debug_driver(int time);
};

// typedef for clarity 
typedef std::vector<MotorDriver*> motorArray_t;

MotorDriver::MotorDriver(int PWM_pin, int DIR_pin, int I2C_channel)
    : PWM_pin(PWM_pin), DIR_pin(DIR_pin), I2C_channel(I2C_channel) {
    pinMode(DIR_pin, OUTPUT);
    softPwmCreate(PWM_pin, 0, 255);
}

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

void MotorDriver::debug_driver(int time) {
    setSpeed(100, 0);
    std::cout << "Motor PWM Pin moving 0: " << PWM_pin << std::endl;
    delay(time);
    setSpeed(100, 1);
    std::cout << "Motor PWM Pin moving 1: " << PWM_pin << std::endl;
    delay(time);
    setSpeed(0, 0);
}

class Motors {
public:
    Motors(motorArray_t motors);
    void debugAll(int time);
    void spinInPlace(int time, int speed);
    void moveForwards(int time, int speed);
    void stop();
private:
    motorArray_t motorArray;
    int fd;
};

Motors::Motors(motorArray_t motors)
    : motorArray(motors) {
    std::cout << "Motors Initialized with " << motors.size() << " motor(s)." << std::endl;
}

void Motors::debugAll(int time) {
    for (auto motor : motorArray) {
        motor->debug_driver(time);
    }
}

void Motors::spinInPlace(int time, int speed) {
    if (motorArray.size() < 4) {
        std::cerr << "Insufficient motors for spinning in place." << std::endl;
        return;
    }
    motorArray[0]->setSpeed(speed, 0);
    motorArray[1]->setSpeed(speed, 0);

    motorArray[2]->setSpeed(speed, 1);
    motorArray[3]->setSpeed(speed, 1);
    delay(time);

    // Stop motors after spinning
    for (auto motor : motorArray) {
        motor->setSpeed(0, 0);
    }
}

void Motors::moveForwards(int time, int speed) {
    if (motorArray.size() < 4) {
        std::cerr << "Not enough Motors" << std::endl;
        return;
    }

    motorArray[0]->setSpeed(speed, 0);
    motorArray[1]->setSpeed(speed, 0);
    motorArray[2]->setSpeed(speed, 1);
    motorArray[3]->setSpeed(speed, 1);
    delay(time);
}

// stops
void Motors::stop() {
    for (auto motor : motorArray) {
        motor->setSpeed(0, 0);
    }
    std::cout << "Stopped" << std::endl;
}
