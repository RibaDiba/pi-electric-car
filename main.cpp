#include <iostream>
#include "MotorLib.h"
#include <wiringPi.h>

void startup() {

    MotorDriver m1 = MotorDriver(1, 2, 3);
    MotorDriver m2 = MotorDriver(2, 2, 3);
    MotorDriver m3 = MotorDriver(3, 2, 3);
    MotorDriver m4 = MotorDriver(4, 2, 3);

    MotorDriver* Motors[4] = {&m1, &m2, &m3, &m4};

    m1.debug_driver(2000, 200, Motors, 4);
    std::cout << "Compiled Correctly";
}

void test() {
    MotorDriver m1 = MotorDriver(1, 2, 0);
    m1.setSpeed(100, 0);
    std::cout << "Motor 1 spinning Right" << std::endl;
    delay(2000);
    m1.setSpeed(100, 1);
    std::cout << "Motor 1 spinning Left" << std::endl;
    delay(2000);
    m1.setSpeed(0, 0);
    std::cout << "Motor 1 stopped" << std::endl;
}

int main() {
    if (wiringPiSetupGpio() == -1) {
        std::cerr << "WiringPi setup failed!" << std::endl;
        return 1;
    }

    test();
    return 0;
}