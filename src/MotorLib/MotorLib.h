#pragma once
#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>
#include <vector>
#include <cstdint>

namespace MotorType {
    typedef std::vector<MotorDriver*> motorArray_t;
}

class MotorDriver {
    public:
        int PWM_pin;
        int DIR_pin;
        int I2C_channel;

        MotorDriver(int PWM_pin, int DIR_pin, int I2C_channel);
        void setSpeed(int speed, int dir);
        void debug_driver(int time);
};

class Motors {
    public:
        Motors(MotorType::motorArray_t motors);
        void debugAll(int time);
        void spinInPlace(int time, int speed);
        void moveForwards(int time, int speed);

        // these are for joycons 
        void forwards(int spped);
        void backwards(int speed);
        void spinRight(int speed);
        void spinLeft(int speed);

        // these are for turning with joycons 
        void turnRight(int speed);
        void turnLeft(int speed);

        void stop();
    private:
        MotorType::motorArray_t motorArray;
        int fd;
};