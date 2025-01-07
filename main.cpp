#include <wiringPi>
#include "MotorLib.h"

int main() {
    MotorDriver m1 = MotorDriver(1, 2);
    std::cout << "Motor initialized" << std::endl;
    return 0;
}