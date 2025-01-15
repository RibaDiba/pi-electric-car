#include "MotorLib.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>

void Motors::init_multiplex() {
    fd = wiringPiI2CSetup(0x70);
    if (fd == -1) {
        printf("Failed to initialize I2C communication.\n");
        return -1;
    }
    printf("I2C setup successful. File descriptor: %d\n", fd);
}

void Motors::tcaselect(uint8_t i) {
    if (i > 7) return; 

    if (fd == -1) {
        printf("Failed to initialize I2C communication with TCA9548A.\n");
        return;
    }

    int status = wiringPiI2CWrite(fd, 1 << i);
    if (status == -1) {
        printf("Failed to select channel %d on TCA9548A.\n", i);
        return;
    }

    printf("Switched to Channel: %d\n", i);
}

void Motors::debug_magencoders() {
    Serial.println("\nTCAScanner ready!");

    for (uint8_t t = 0; t < 8; t++) {
        tcaselect(t);
        delay(5); // Allow time for channel switching
        Serial.print("TCA Port #");
        Serial.println(t);

        for (uint8_t addr = 1; addr < 127; addr++) {
            if (addr == TCAADDR) continue;

            Wire.beginTransmission(addr);
            if (Wire.endTransmission() == 0) {
                Serial.print("Found I2C device at 0x");
                Serial.println(addr, HEX);
                ifFound[t] = true;
            }
        }
    }

    for (int i = 0; i < (sizeof(ifFound) / sizeof(ifFound[0])); i++) {
        if (!ifFound[i]) {
            Serial.println("Unable to Access Encoders on Channel: " + String(i));
        }
    }

    Serial.println("Setup successful if no errors above!");
}