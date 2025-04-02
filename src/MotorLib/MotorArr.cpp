#pragma once
#include "MotorLib.h"

Motors::Motors(MotorType::motorArray_t motors)
    : motorArray(motors) {
    std::cout << "Motors Initialized with " << motors.size() << " motor(s)." << std::endl;
}

// util function 
long Motors::map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
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
    motorArray[4]->sparkSetSpeed(150);
    motorArray[5]->sparkSetSpeed(150);
    // std::cout << "Stopped" << std::endl;
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

/* edit these values */

void Motors::spinRight(int speed) {
    motorArray[0]->setSpeed(250, 0);
    motorArray[1]->setSpeed(250, 0);
    motorArray[2]->setSpeed(250, 0);
    motorArray[3]->setSpeed(250, 0);

    int mapped = map(speed, 0, 255, 100, 200);
    std::cout << "Mapped speed for sparks: " << mapped << std::endl;

    motorArray[4]->sparkSetSpeed(mapped);
    motorArray[5]->sparkSetSpeed(mapped);
}

void Motors::spinLeft(int speed) {
    motorArray[0]->setSpeed(250, 1);
    motorArray[1]->setSpeed(250, 1);
    motorArray[2]->setSpeed(250, 1);
    motorArray[3]->setSpeed(250, 1);

    int mapped = map(speed, 0, 255, 100, 200);
    std::cout << "Mapped speed for sparks" << mapped << std::endl;

    motorArray[4]->sparkSetSpeed(mapped);
    motorArray[5]->sparkSetSpeed(mapped);
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
