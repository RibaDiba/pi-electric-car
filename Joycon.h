#include "MotorLib.h"
#include "calc.h"
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
    void test();
    void getValues(int maxSpeed);
};

Joycon::Joycon(unsigned short vendorId, unsigned short productId, std::vector<MotorDriver*> motors)
    : Motors(motors), vendorId(vendorId), productId(productId) {
    
     if (hid_init()) {
          std::cerr << "Failed to Init HID" << std::endl;
          return;
     }

     device = hid_open(vendorId, productId, NULL);  // Corrected variable assignment
     if (!device) {
          std::cerr << "Failed to open Joy-Con device!" << std::endl;
          return;
     }
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Joycon::getValues(int maxSpeed) {
    unsigned char data[61];
    while (true) {
        int bytesRead = hid_read(device, data, sizeof(data));
        if (bytesRead > 0 ) {
            uint8_t rawX = data[7];
            rawX = ((rawX & 0x0F) << 4) | ((rawX & 0xF0) >> 4);
            uint8_t rawY = data[8];

            // map 50 to 200 for X
            // 75 to 200 for y 
            int joystickX = static_cast<int>(rawX);
            int joystickY = static_cast<int>(rawY);

            // joystickX needs to be fixed (my case only?)
            joystickX = map(joystickX, 55, 215, 75, 190);

            // test map y + correction ->
            int PWMJoystickY = map(joystickY, 75, 212, -maxSpeed, maxSpeed);
            // would be fixed if drift is fixed --> maybe?
            if (abs(PWMJoystickY) < 10) {
                PWMJoystickY = 0;
            }

            // test map x 
            int PWMJoystickX = map(joystickX, 75, 190, -maxSpeed, maxSpeed);

            if (PWMJoystickY > maxSpeed/2) {
                state = "moving Forwards";
            } else if (PWMJoystickY < -maxSpeed/2) {
                state = "moving Backwards";
            } else if (PWMJoystickX > maxSpeed/2) {
                state = "moving right";
            } else if (PWMJoystickX < -maxSpeed/2) {
                state = "moving left";
            } else {
                state = "stopped";
            }

            std::cout << "X: " << PWMJoystickX << " Y: " << PWMJoystickY << " State: " << state << std::endl;
        } else {
            std::cout << "Unable to get Values" << std::endl;
        }
    }
}

void Joycon::test() {
    unsigned char data[61]; // Buffer size based on Joy-Con report size

    while (true) {
        int bytesRead = hid_read(device, data, sizeof(data));
        if (bytesRead > 0) {
            // Print raw data
            std::cout << "Data Read (" << bytesRead << " bytes): ";
            for (int i = 0; i < bytesRead; ++i) {
                printf("%02X ", data[i]);
            }
            std::cout << std::endl;

            uint8_t rawX = data[7];
            uint8_t reversedX = ((rawX & 0x0F) << 4) | ((rawX & 0xF0) >> 4);
            uint8_t rawY = data[8];

            // Convert raw values to integers
            int joystickX = static_cast<int>(reversedX);
            int joystickY = static_cast<int>(rawY);

            // Output the joystick positions
            std::cout << "Joystick Position -> X: " << joystickX << ", Y: " << joystickY << std::endl;

            // Add your data interpretation logic here
        } else if (bytesRead < 0) {
            // Handle read error
            std::cerr << "Error reading from device: " << hid_error(device) << std::endl;
            break; // Exit the loop if there's an error
        }
        // Small delay to prevent CPU overuse
        delay(10);
    }
}





