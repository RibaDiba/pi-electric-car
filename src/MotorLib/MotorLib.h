#pragma once
#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>
#include <vector>
#include <cstdint>

// Forward declaration of MotorDriver
class MotorDriver;

namespace MotorType {
    typedef std::vector<MotorDriver*> motorArray_t;
}

class MotorDriver {
    public:
        int PWM_pin;
        int DIR_pin;
        int I2C_channel;

        // for new motor controllers
        int LPWM_pin;
        int RPWM_pin;

        MotorDriver(int PWM_pin, int DIR_pin, int I2C_channel);
        MotorDriver (int LPWM_pin, int RPWM_pin);
        MotorDriver (int PWM_pin);
        void setSpeed(int speed, int dir);
        void sparkSetSpeed(int speed);
        void debug_driver(int time);
        void calibrateSpark();

        void setSpeedNew(int speed, int dir);
    private: 
        int mapToPWM(int speed);
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
