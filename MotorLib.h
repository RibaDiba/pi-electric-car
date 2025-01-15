#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>
#include <vector>

class MotorDriver {
    public:
        int PWM_pin;
        int DIR_pin;
        int I2C_channel;

        MotorDriver(int PWM_pin, int DIR_pin, int I2C_channel);
        void setSpeed(int speed, int dir);
        void debug_driver(int time);
};

MotorDriver::MotorDriver(int PWM_pin, int DIR_pin, int I2C_channel)
    : PWM_pin(PWM_pin), DIR_pin(DIR_pin), I2C_channel(I2C_channel) {
    pinMode(DIR_pin, OUTPUT);
    softPwmCreate(PWM_pin, 0, 255);
}

void MotorDriver::setSpeed(int speed, int dir) {
    if (dir == 0) {
        digitalWrite(DIR_pin, LOW);
    } else if (dir == 1) {
        digitalWrite(DIR_pin, HIGH);
    } else {
        std::cout << "Invalid Direction Value" << std::endl;
        return;
    }
    softPwmWrite(PWM_pin, speed);
}

void MotorDriver::debug_driver(int time) {
    setSpeed(100, 0);
    std::cout << "Motor PWM Pin moving 0: " << PWM_pin << std::endl;
    delay(time);
    setSpeed(100, 1);
    std::cout << "Motor PWM Pin moving 1: " << PWM_pin << std::endl;
    delay(time);
    setSpeed(0, 0);
}

class Motors {
private:
    std::vector<MotorDriver*> motorArray;

public:
    Motors(std::vector<MotorDriver*> motors);
    void debugAll(int time);
    void tcaselect(uint8_t i);
    void debug_magencoders();
    void init_multiplex();
    int fd;
};

Motors::Motors(std::vector<MotorDriver*> motors)
    : motorArray(motors) {
    std::cout << "Motors Initialized with " << motors.size() << " motor(s)." << std::endl;

    init_multiplex();
}

void Motors::debugAll(int time) {
    for (auto motor : motorArray) {
        motor->debug_driver(time);
    }
}
