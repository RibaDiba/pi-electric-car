#include <iostream>

class MotorDriver {
     public:
          int PWM_pin;
          int DIR_pin;
          MotorDriver(int PWM_pin, int DIR_pin);
          void setSpeed(int speed);
};

MotorDriver::MotorDriver(int PWM_pin, int DIR_pin) {
     this->PWM_pin = PWM_pin;
     this->DIR_pin = DIR_pin;
     pinMode(PWM_pin, OUTPUT_PWM);
     pinMode(DIR_pin, OUTPUT);
}

void MotorDriver::setSpeed(int speed, int dir) {
     switch (dir) {
          case 0: 
               digitalWrite(DIR_pin, LOW);
               break;
          case 1: 
               digitalWrite(DIR_pin, HIGH);
               break;
          default: 
               std::cout << "Invalid direction" << std::endl;
     }
     analogWrite(PWM_pin, speed);
}

