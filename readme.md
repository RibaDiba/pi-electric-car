# pi-electric-car

**A Raspberry Pi–powered electric vehicle controlled via Joy-Con.**  
This project enables an electric car built from e-scooter motors to be driven using a Joy-Con controller over Bluetooth.

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

