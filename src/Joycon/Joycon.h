#pragma once
#include <iostream>

enum class JoyconState {
    STOPPED,
    FOWARDS,
    BACKWARDS,
    SPIN_RIGHT,
    SPIN_LEFT
};

// Define operator<< for JoyconState
inline std::ostream& operator<<(std::ostream& os, const JoyconState& state) {
    switch (state) {
        case JoyconState::STOPPED: return os << "STOPPED";
        case JoyconState::FOWARDS: return os << "FOWARDS";
        case JoyconState::BACKWARDS: return os << "BACKWARDS";
        case JoyconState::SPIN_RIGHT: return os << "SPIN_RIGHT";
        case JoyconState::SPIN_LEFT: return os << "SPIN_LEFT";
        default: return os << "UNKNOWN";
    }
}

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

        // this is temp
        std::string state = "Stopped";

        Joycon(unsigned short vendorId, unsigned short productId, std::vector<MotorDriver*> motors);
        int initJoycon();
        void test();
        int AdjustableSpeed(const std::vector<int>&arrOfSpeeds);
        JoyconState handleJoystickValues(uint8_t rawX, uint8_t rawY);

    
    private: 
        long map(long x, long in_min, long in_max, long out_min, long out_max);
};

// Define operator<< for JoyconState
