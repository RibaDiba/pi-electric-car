#include <iostream>

class MotorDriver {
    int PWM_pin;
    int DIR_pin;
    int I2C_Channel;
    MotorDriver(int PWM_pin, int DIR_pin, int I2C_Channel);
    void setSpeed(int speed, int dir);
};

MotorDriver::MotorDriver(int PWM_pin, int DIR_pin, int I2C_Channel)
    : PWM_pin(PWM_pin), DIR_pin(DIR_pin), I2C_Channel(I2C_Channel)
{
    // pinMode(PWM_pin, PWM_output);
    // pinMode(DIR_pin, OUTPUT);
}

void MotorDriver::setSpeed(int speed, int dir)
{
    switch (dir)
    {
    case 0:
        // digitalWrite(DIR_pin, LOW);
        break;
    case 1:
        // digitalWrite(DIR_pin, HIGH);
    default:
        std::cout << "INVALID DIRECTION" << std::endl;
    }
}
