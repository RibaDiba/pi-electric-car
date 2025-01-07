#include <iostream>
#include <wiringPi.h>
#include <softPwm.h> // For PWM control

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
    pinMode(PWM_pin, OUTPUT);
    pinMode(DIR_pin, OUTPUT);

    // Initialize softPWM on the PWM pin
    softPwmCreate(PWM_pin, 0, 100); // PWM pin, initial value (0), range (0-100)
}

void MotorDriver::setSpeed(int speed, int dir) {
    // Handle direction values
    switch (dir) {
    case 0:
        digitalWrite(DIR_pin, LOW);
        break;
    case 1:
        digitalWrite(DIR_pin, HIGH);
        break;
    default:
        std::cout << "Invalid Direction Value" << std::endl;
        return;
    }

    // Set the speed using softPWM
    softPwmWrite(PWM_pin, speed); // PWM pin and speed (0-100)
}

void MotorDriver::debug_driver(int time, int speed, MotorDriver* array[], int array_size) {
    for (int i = 0; i < array_size; ++i) {
        MotorDriver* obj = array[i];
        obj->setSpeed(200, 0); // This might need to be adjusted if "speed" exceeds 100
        std::cout << "Motor PWM Pin: " << obj->PWM_pin << std::endl;
        delay(time); // Delay in milliseconds
    }
}
