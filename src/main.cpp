#include <iostream>
#include "MotorLib/MotorLib.h"
#include <wiringPi.h>
#include "Joycon/Joycon.h"


 void test() {
    MotorDriver m1 = MotorDriver(0, 1, 0); 
    m1.debug_driver(4000);
    while (true) {m1.setSpeed(0, 0);}
 }

int main() {
    if (wiringPiSetup() == -1) {
        std::cerr << "WiringPi setup failed!" << std::endl;
        return 1;
    }

    MotorDriver m1 = MotorDriver(0, 1, 0); 
    MotorDriver m2 = MotorDriver(2, 3, 0);
    MotorDriver m3 = MotorDriver(28, 29, 0);
    MotorDriver m4 = MotorDriver(12, 13, 0);

    Joycon left = Joycon(0x057E, 0x2006, {&m1, &m2, &m3, &m4});

    left.AdjustableSpeed({20, 40, 80, 150, 180, 210, 250});

    std::cout << left.initJoycon() << std::endl;
    if (left.initJoycon() == 1) {
        return 1;
    }
    
    return 0;
}
