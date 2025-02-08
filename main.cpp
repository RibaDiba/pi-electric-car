#include <iostream>
#include "MotorLib.h"
#include <wiringPi.h>
#include "Joycon.h"


 void test() {

    MotorDriver m1 = MotorDriver(28, 29, 0); 
    m1.setSpeed(100, 0);  
    std::cout << "Motor 1 spinning Right" << std::endl;
    delay(2000); 

    m1.setSpeed(100, 1);  // Spin Left
    std::cout << "Motor 1 spinning Left" << std::endl;
    delay(2000); 

    m1.setSpeed(0, 0);  // Stop Motor
    std::cout << "Motor 1 stopped" << std::endl;
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

    Motors array = Motors({&m1, &m2, &m3, &m4});
    Joycon left = Joycon(0x057E, 0x2006, {&m1, &m2, &m3, &m4});

    left.getValues(200);
    array.stop();
    // test();
    return 0;
}
