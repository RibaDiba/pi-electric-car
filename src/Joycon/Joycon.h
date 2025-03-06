#pragma once 

#include "../MotorLib/MotorLib.h"
#include <hidapi/hidapi.h>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>  

class Joycon:public Motors {
    public:
        unsigned short vendorId;
        unsigned short productId;
        hid_device *device;
        struct Speeds {
            int rSpeed;
            int lSpeed;
        };
        Speeds MotorSpeeds;
        // this is temp
        std::string state = "Stopped";

        Joycon(unsigned short vendorId, unsigned short productId, std::vector<MotorDriver*> motors);
        int initJoycon();
        void test();
        void JoyconMode(int maxSpeed);
        int AdjustableSpeed(const std::vector<int>&arrOfSpeeds);

    
    private: 
        long map(long x, long in_min, long in_max, long out_min, long out_max);
        std::string handleJoystickValues(uint8_t rawX, uint8_t rawY);
};