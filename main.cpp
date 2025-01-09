#include <iostream>
#include "MotorLib.h"
#include <wiringPi.h>

void test() {
    MotorDriver m1 = MotorDriver(0, 1, 0); 
    m1.setSpeed(100, 0);  // Spin Right
    std::cout << "Motor 1 spinning Right" << std::endl;
    delay(2000);  // Wait for 2 seconds

    m1.setSpeed(100, 1);  // Spin Left
    std::cout << "Motor 1 spinning Left" << std::endl;
    delay(2000);  // Wait for 2 seconds

    m1.setSpeed(0, 0);  // Stop Motor
    std::cout << "Motor 1 stopped" << std::endl;
}

int main() {
    if (wiringPiSetup() == -1) {
        std::cerr << "WiringPi setup failed!" << std::endl;
        return 1;
    }

    test();  // Run the test function
    return 0;
}
