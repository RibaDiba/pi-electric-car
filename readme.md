This repo contains information on a electric car made with e-scooter motors, included is important information

## Wire notes 

- [Motor Driver Pin] = [WiringPi Pin] = [Labeled Wire Number]

- pwm 1 = 2 = 5
- dir 0 = 14 = 4
- dir 1 = 1 = 6
- pwm 0 = 0 = 7
- pwm 3 = 12 = 3
- dir 3 = 13 = 2
- pwm 2 = 28 = 1
- dir 2 = 29 = 0

## Joycon Notes

Joycons are used as the control system, using bluetooth the joycon sends a 42 byte long response in which it details information about the rumble, joystick, button handling, etc. This information is for the left joycon. There are also values that are sent if two buttons are pressed at the same time, these are just individual.

- Byte 5: Button Handling
     - Up = 02
     - Down = 01
     - Right = 04
     - Left = 08
     - L = 40
     - ZR = 80
     - Sr = 10
     - LR = 20
- Byte 4: Button Handling (for some unique buttons)
     - Minus = 01
     - Capture Button = 20
     - Joystick Button = 08
- Byte 7: X nimble on joystick 
- Byte 8: Y nimble on joystick

## Direction Mapping Notes 

- Turn left and straight: X  > 80 + 200 > Y > 160
- Turn right and straight: x > 170 + 200 > Y > 170

- Go forwards: just a Y value above 200
- Go backwards: Just a Y value below 80

- Go left and forwards

