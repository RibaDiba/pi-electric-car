#pragma once
#include "MotorLib.h"

Motors::Motors(MotorType::motorArray_t motors)
    : motorArray(motors) {
    std::cout << "Motors Initialized with " << motors.size() << " motor(s)." << std::endl;
}

// loops through and debugs all drivers in array 
void Motors::debugAll(int time) {
    for (auto motor : motorArray) {
        motor->debug_driver(time);
    }
}

void Motors::stop() {
    for (auto motor : motorArray) {
        motor->setSpeed(0, 0);
    }
    std::cout << "Stopped" << std::endl;
}

/* These functions below are only for joycon movement */

void Motors::forwards(int speed) {
    motorArray[0]->setSpeed(speed, 1);
    motorArray[1]->setSpeed(speed, 0);
    motorArray[2]->setSpeed(speed, 1);
    motorArray[3]->setSpeed(speed, 0);
}

void Motors::backwards(int speed) {
    motorArray[0]->setSpeed(speed, 0);
    motorArray[1]->setSpeed(speed, 1);
    motorArray[2]->setSpeed(speed, 0);
    motorArray[3]->setSpeed(speed, 1);
}

void Motors::spinRight(int speed) {
    motorArray[0]->setSpeed(speed, 0);
    motorArray[1]->setSpeed(speed, 1);
    motorArray[2]->setSpeed(speed, 1);
    motorArray[3]->setSpeed(speed, 0);
}

void Motors::spinLeft(int speed) {
    motorArray[0]->setSpeed(speed, 1);
    motorArray[1]->setSpeed(speed, 0);
    motorArray[2]->setSpeed(speed, 0);
    motorArray[3]->setSpeed(speed, 1);
}

void Motors::turnRight(int speed) {
    motorArray[0]->setSpeed(speed *.5, 0);
    motorArray[1]->setSpeed(speed, 0);
    motorArray[2]->setSpeed(speed*.5, 1);
    motorArray[3]->setSpeed(speed, 1);
}

void Motors::turnLeft(int speed) {
    motorArray[0]->setSpeed(speed, 0);
    motorArray[1]->setSpeed(speed, 1);
    motorArray[2]->setSpeed(speed, 0);
    motorArray[3]->setSpeed(speed, 1);
}
