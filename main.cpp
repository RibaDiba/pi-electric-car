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

int main() {
    startup();
    return 0;
}