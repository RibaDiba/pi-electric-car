#include <iostream>

class MotorDriver {
public:
    int PWM_pin;
    int DIR_pin;
    int I2C_channel;

    MotorDriver(int PWM_pin, int DIR_pin, int I2C_channel);
    void setSpeed(int speed, int dir);
    void debug_driver(int time, int speed, MotorDriver* array[], int array_size);
};

MotorDriver::MotorDriver(int PWM_pin, int DIR_pin, int I2C_channel)
    : PWM_pin(PWM_pin), DIR_pin(DIR_pin), I2C_channel(I2C_channel) {
    // pinMode(PWM_pin, PWM_OUTPUT);
    // pinMode(DIR_pin, OUTPUT);
}

void MotorDriver::setSpeed(int speed, int dir) {
    // Handle direction values
    switch (dir) {
    case 0:
        // digitalWrite(DIR_pin, LOW);
        break;
    case 1:
        // digitalWrite(DIR_pin, HIGH);
        break;
    default:
        std::cout << "Invalid Direction Value" << std::endl;
        return;
    }

    // analogWrite(PWM_pin, speed);
}

void MotorDriver::debug_driver(int time, int speed, MotorDriver* array[], int array_size) {
    for (int i = 0; i < array_size; ++i) {
        MotorDriver* obj = array[i];
        obj->setSpeed(200, 0);
        std::cout << obj->PWM_pin << std::endl;
        // delay(time);
    }
}
