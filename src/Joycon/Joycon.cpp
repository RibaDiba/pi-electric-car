#pragma once 
#include "Joycon.h" 

Joycon::Joycon(unsigned short vendorId, unsigned short productId, std::vector<MotorDriver*> motors)
    : Motors(motors), vendorId(vendorId), productId(productId) {
     device = hid_open(vendorId, productId, NULL); 
}

long Joycon::map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// see if joycon is active 
int Joycon::initJoycon() {
    if (hid_init()) {
          std::cerr << "Failed to Init HID" << std::endl;
          return 1;
     }

     device = hid_open(vendorId, productId, NULL); 
     if (!device) {
          return 1;
     } else {
        return 0;
     }
}

JoyconState Joycon::handleJoystickValues(uint8_t rawX, uint8_t rawY) {
     rawX = ((rawX & 0x0F) << 4) | ((rawX & 0xF0) >> 4);

     int joystickX = static_cast<int>(rawX);
     int joysticky = static_cast<int>(rawY);

     // joystickX needs to be fixed (my case only?)
     joystickX = map(joystickX, 55, 215, 75, 190);
     int joystickY = static_cast<int>(rawY);

     // output for joystick debugging
     // std::cout << "Joystick X: " << joystickX << " Joystick Y: " << joystickY << std::endl;

     if (joystickY > 210) {
          return JoyconState::FOWARDS;
     } else if (joystickY < 80) {
          return JoyconState::BACKWARDS;
     } else if (joystickX > 160) {
          return JoyconState::SPIN_RIGHT;
     } else if (joystickX < 80) {
          return JoyconState::SPIN_LEFT;
     } else {
          return JoyconState::STOPPED;
     }

}

int Joycon::AdjustableSpeed(const std::vector<int>& arrOfSpeeds) {
     unsigned char data[61];

     // debounce for button presses
     auto lastPressTimeUp = std::chrono::steady_clock::now();
     auto lastPressTimeDown = std::chrono::steady_clock::now();
     const std::chrono::milliseconds debounceInterval(200);

     int currentSpeed = arrOfSpeeds[0];
     int currentSpeedIndex = 0;

     if (!device) {
          std::cerr << "Failed to open Joycons" << std::endl;
          return 1;
     }

     while (true) {
          // check if devices is stil there
          if (!device) {
               std::cerr << "Failed to open Joycons" << std::endl;
               return 1;
          } 

          int rawData = hid_read(device, data, sizeof(data));

          if (rawData < 0) {
               std::cerr << "Failed to Open" << std::endl;
               return 1;
          }

          // handle button data
          uint8_t buttonData = data[5];
          int buttonState = static_cast<int>(buttonData);
          bool upButtonState = false;
          bool downButtonState = false;

          if (buttonState == 1) {  // Down button pressed
               auto now = std::chrono::steady_clock::now();
               if (now - lastPressTimeDown > debounceInterval) {
                    currentSpeedIndex--;  // Decrease the index
                    if (currentSpeedIndex < 0) {
                         currentSpeedIndex = 0;  // Prevent going below zero
                    }
                    currentSpeed = arrOfSpeeds[currentSpeedIndex];  // Update the speed
                    downButtonState = true;
                    lastPressTimeDown = now;  // Update the last press time for down button
               }
          }
            else if (buttonState == 2) {  // Up button pressed
               auto now = std::chrono::steady_clock::now();
               if (now - lastPressTimeUp > debounceInterval) {
                    currentSpeedIndex++;  // Increase the index
                    if (currentSpeedIndex >= arrOfSpeeds.size()) {
                         currentSpeedIndex = arrOfSpeeds.size() - 1;  // Prevent going beyond the last index
                    }
                    currentSpeed = arrOfSpeeds[currentSpeedIndex];  // Update the speed
                    upButtonState = true;
                    lastPressTimeUp = now;  // Update the last press time for up button
               }
          } else {
               upButtonState = false;
               downButtonState = false;
          }

          JoyconState state = handleJoystickValues(data[7], data[8]);
          int speedSent = currentSpeed;

          switch (state) {
               case JoyconState::FOWARDS:
                    forwards(speedSent);
                    break;
               case JoyconState::BACKWARDS:
                    backwards(speedSent);
                    break;
               case JoyconState::SPIN_RIGHT:
                    spinRight(speedSent);
                    break;
               case JoyconState::SPIN_LEFT:
                    spinLeft(speedSent);
                    break;
               default:
                    stop();
          }

          std::cout << "State: " << state << " Speed: " << speedSent << std::endl;
     }

     return 0;
}


