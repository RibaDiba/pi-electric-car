#include <iostream>
#include <wiringPi.h>
#include <softPwm.h> // For PWM control

class Motors {
    public: 
        MotorDriver* Motors[];
        int* encoderArray;
        Motors(MotorDriver* Motors);
}

Motors::Motors(int MotorDriver* Motors)
    : Motors(Motors) {
        std::cout << "Array Initialized" << std::endl;
    }

class MotorDriver: public Motors {
public:
    int PWM_pin;
    int DIR_pin;
    int I2C_channel;

    MotorDriver(int PWM_pin, int DIR_pin, int I2C_channel);
    void setSpeed(int speed, int dir);
    void debug_driver(int time, MotorDriver* array[], int array_size);
};

MotorDriver::MotorDriver(int PWM_pin, int DIR_pin, int I2C_channel)
    : PWM_pin(PWM_pin), DIR_pin(DIR_pin), I2C_channel(I2C_channel) {
    pinMode(DIR_pin, OUTPUT);  // Initialize the direction pin as an output
    softPwmCreate(PWM_pin, 0, 255);  // Initialize PWM on the specified pin with a range of 0-255
}

void MotorDriver::setSpeed(int speed, int dir) {
    // Handle direction values
    switch (dir) {
    case 0:  // Forward
        digitalWrite(DIR_pin, LOW);  // Set direction to LOW (forward)
        break;
    case 1:  // Reverse
        digitalWrite(DIR_pin, HIGH); // Set direction to HIGH (reverse)
        break;
    default:
        std::cout << "Invalid Direction Value" << std::endl;
        return;
    }

    // Set the PWM speed
    softPwmWrite(PWM_pin, speed);  // Set PWM speed (0-255)
}

void MotorDriver::debug_driver(int time, MotorDriver* array[], int array_size) {
    for (int i = 0; i < array_size; ++i) {
        MotorDriver* obj = array[i];
        obj->setSpeed(255, 0);  // Set to maximum speed in forward direction
        std::cout << "Motor PWM Pin: " << obj->PWM_pin << std::endl;
        delay(time);  // Delay in milliseconds
        obj->setSpeed(0, 0);  // Stop the motor
    }
}


