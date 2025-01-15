#include <iostream>
#include "MotorLib.h"
#include <wiringPi.h>


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

    MotorDriver m2 = MotorDriver(2, 3, 0);
    MotorDriver m1 = MotorDriver(0, 1, 0); 
    MotorDriver m3 = MotorDriver(4, 5, 0);
    MotorDriver m4 = MotorDriver(12, 13, 0);

    Motors array = Motors({&m1, &m2, &m3, &m4});
   
    //array.debugAll(2000);
    array.spinInPlace(20, 1000);
    while (true) {m1.setSpeed(0,0); m2.setSpeed(0,0); m3.setSpeed(0,0); m4.setSpeed(0,0);}

    // test();
    return 0;
}
