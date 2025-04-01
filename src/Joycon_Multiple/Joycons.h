#pragma once
#include <iostream>
#include "../MotorLib/MotorLib.h"
#include <hidapi/hidapi.h>
#include <vector>
#include <thread>
#include <chrono> 

enum class JoyconsState {
    STOPPED,
    FOWARDS,
    BACKWARDS,
    SPIN_RIGHT,
    SPIN_LEFT
};

// Define operator<< for JoyconsState
inline std::ostream& operator<<(std::ostream& os, const JoyconsState& state) {
    switch (state) {
        case JoyconsState::STOPPED: return os << "STOPPED";
        case JoyconsState::FOWARDS: return os << "FOWARDS";
        case JoyconsState::BACKWARDS: return os << "BACKWARDS";
        case JoyconsState::SPIN_RIGHT: return os << "SPIN_RIGHT";
        case JoyconsState::SPIN_LEFT: return os << "SPIN_LEFT";
        default: return os << "UNKNOWN";
    }
}

class Joycons:public Motors {
    public:
        const std::vector<int>&arrOfSpeeds;
        Joycons(std::vector<int>&arrOfSpeeds, std::vector<MotorDriver*> motors);
        // used for error handling in main.cpp
        int initJoycons();
        int run();
    private:
        unsigned short rightVendorId = 0x057E;
        unsigned short rightProductId = 0x2007;
        unsigned short leftVendorId = 0x057E;
        unsigned short leftProductId = 0x2006;

        hid_device *leftJoycon;
        hid_device *rightJoycon;

        std::string state = "Stopped";
        JoyconsState handleJoystickValues(uint8_t rawX, uint8_t rawY);
        int handleSpeed(uint8_t rawX, uint8_t rawY, int speed);
        long map(long x, long in_min, long in_max, long out_min, long out_max);
};