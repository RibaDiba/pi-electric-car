# pi-electric-car

![Platform](https://img.shields.io/badge/Platform-Raspberry_PI-informational?color=B2113F&logo=raspberrypi&logoColor=white&style=flat
) ![Language](https://img.shields.io/badge/language-C%2B%2B-lightgrey)

<p>
  <a href="https://github.com/RibaDiba" target="_blank" rel="noopener noreferrer">
    <img src="https://images.weserv.nl/?url=avatars.githubusercontent.com/u/96350741?v=4&mask=circle&maxage=7d" width="60" height="60" alt="@RibaDiba" />
  </a>
  <a href="https://github.com/iamgod5" target="_blank" rel="noopener noreferrer">
    <img src="https://images.weserv.nl/?url=avatars.githubusercontent.com/u/118085362?v=4&mask=circle&maxage=7d" width="60" height="60" alt="@iamgod5" />
  </a>
</p>

**A Raspberry Pi–powered electric vehicle controlled via Joy-Con.**  
This project enables an electric car built from e-scooter motors to be driven using a Joy-Con controller over Bluetooth.

[Link to CAD file here](https://cad.onshape.com/documents/f188a9c0193ae862e4d85774/w/2e1b61a494eceb673373fd07/e/9c9974e0483e9adc0cc3e6ba?renderMode=0&uiState=6898a2caabd109049a96fbdb)  
_Created by [@iamgod5](https://github.com/iamgod5)_

---

## ​ Overview
- **Purpose**: Turn a Raspberry Pi and e-scooter motors into a Joy-Con–controlled electric car for the Odessey of the Mind HS competition.
- **Built with**: C++, WiringPi, Makefile, Joy-Con Bluetooth interface.

---

## Repository Structure

| Path / File | Description |
|-------------|-------------|
| **`Makefile`** | Build instructions for compiling the C++ source code. Defines targets for building and cleaning the project. |
| **`main.cpp`** | Main program logic for reading Joy-Con input and controlling the car’s motors via WiringPi. |
| **`joycon.h`** | Header file defining constants, function declarations, and data structures for Joy-Con Bluetooth communication. |
| **`joycon.cpp`** | Implementation file containing functions to read and parse Joy-Con input data. |
| **`joycons.h`** | Header file for Multi-Joycon bluetooth communication, defining constants, functions, and data structures |
| **`joycons.cpp`** | Implementation file containing  |
| **`MotorLib.h`** | Header defining motor control function prototypes and constants, includes definition for both control of sinular drivers as well as an array. |
| **`MotorDriver.cpp`** | Implementation for the control of singular motor drivers. |
| **`MotorArr.cpp`** | Implementation for the control of an array of motor drivers |

---

##  Features
- 4 Wheel differential drive, using a sproket and chain drivetrain.
- Real-time control via joystick input and button presses.
- Customizable wiring and input mapping for ease of modification.
- Ability to execute in place turns due to drive train desgin

---

##  Joy-Con Input Mapping

**Info**: Below is the results of a brief investigation to reverse engineering the joycon bluetooth interface

- The Joy-Con sends a 42-byte Bluetooth packet.
- Byte mappings:
  - Byte 5: Buttons (Up = `0x02`, Down = `0x01`, Right = `0x04`, etc.)
  - Byte 4: Special buttons (Minus = `0x01`, Capture = `0x20`, etc.)
  - Byte 7/8: Joystick X/Y values.

---

##  Control Logic

**Info**: These numbers come from the internal joycon bluetooth interface

- **Go forward**: Y > 200  
- **Go backward**: Y < 80  
- **Turn left**: X > 80 **and** Y > 160  
- **Turn right**: X > 170 **and** Y > 170

---

##  Setup & Build
```bash
git clone https://github.com/RibaDiba/pi-electric-car.git
cd pi-electric-car
make
sudo ./run-car

