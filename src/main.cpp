#include <iostream>
#include "MotorLib/MotorLib.h"
#include <wiringPi.h>
#include "Joycon/Joycon.h"
#include "Joycon_Multiple/Joycons.h"


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

    MotorDriver mf = MotorDriver(23);
    MotorDriver md = MotorDriver(24);

    // Create vectors before passing them to the constructor
    std::vector<int> speeds = {80, 100, 150, 180, 250};
    std::vector<MotorDriver*> motors = {&m1, &m2, &m3, &m4, &mf, &md};
    
    Joycons obj = Joycons(speeds, motors);
    obj.initJoycons();
    obj.run();

    // Joycon left = Joycon(0x057E, 0x2006, {&m1, &m2, &m3, &m4, &mf, &md});

    // left.AdjustableSpeed({20, 30, 40, 50, 60, 70, 80, 100, 150, 180, 250});

    std::cout << obj.initJoycons() << std::endl;
    if (obj.initJoycons() == 1) {
        return 1;
    }
    
    return 0;
}
