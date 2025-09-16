# Arduino Smart Home Automation System
Arduino Smart Home Hub with MATLAB GUI. Controls door/garge access via RFID &amp; ultrasonic sensors. Automates lights &amp; fan using LDR and DHT11. Streams real-time sensor data to MATLAB for monitoring and remote control.

An integrated smart home system built on Arduino Uno that combines RFID access control, environmental monitoring, and automated appliance control. The system interfaces with MATLAB for real-time data visualization and remote command execution.

![Arduino](https://img.shields.io/badge/Arduino-Uno-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![MATLAB](https://img.shields.io/badge/MATLAB-R2023a-0076A8?style=for-the-badge&logo=mathworks&logoColor=white)
![C++](https://img.shields.io/badge/C++-Arduino%20Framework-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)

## Features

- ** RFID Door Access:** Secure door locking mechanism activated by authorized RFID tags.
- ** Automatic Garage Control:** Ultrasonic sensor detects vehicles and automatically operates the garage door.
- ** Smart Lighting:** LDR sensor triggers LED lights based on ambient light levels.
- ** Climate Control:** DHT11 sensor monitors temperature and controls a cooling fan.
- ** MATLAB GUI:** Desktop interface for real-time sensor data monitoring and remote system control.

## Hardware Components

| Component | Quantity |
| :--- | :--- |
| Arduino Uno | 1 |
| MFRC522 RFID Reader & Tags | 1 |
| HC-SR04 Ultrasonic Sensor | 1 |
| DHT11 Temperature Sensor | 1 |
| LDR (Light Dependent Resistor) | 1 |
| SG90 Servo Motors | 2 |
| LED | 1 |
| 5V Fan Module | 1 |
| Breadboard | 1 |
| Jumper Wires | ~20 |

## 📋 Arduino Pinout

| Component | Arduino Pin |
| :--- | :--- |
| RFID SDA | A0 |
| RFID RST | A4 |
| Distance Servo | 9 |
| RFID Servo | A5 |
| DHT11 Sensor | 8 |
| Ultrasonic Trig | 5 |
| Ultrasonic Echo | 6 |
| LDR Digital Out | 2 |
| LED | 10 |
| Fan | 7 |

## Project Structure

## Installation & Setup

1.  **Hardware Assembly:**
    *   Connect all components according to the pinout table above.
    *   Refer to the `Fritzing_Diagram.fzz` file for a visual wiring guide.

2.  **Arduino IDE Setup:**
    *   Install the required libraries:
        *   `MFRC522` by GithubCommunity
        *   `DHT sensor library` by Adafruit
        *   `Servo` (built-in)
    *   Upload the `Smart_Home_Automation.ino` sketch to your Arduino Uno.

3.  **MATLAB Setup:**
    *   Open MATLAB and navigate to the `MATLAB/` directory.
    *   Open and run `Smart_Home_GUI.m`.
    *   Ensure the correct COM port is selected in the GUI for Arduino communication.

## Usage

1.  **Power on** the Arduino system.
2.  **Run the MATLAB GUI** application.
3.  The GUI will display real-time data from:
    *   Distance Sensor (cm)
    *   Temperature (°C)
    *   Light Level (Dark/Bright)
    *   RFID Tag Scans
4.  Use the GUI buttons to send remote commands:
    *   `LED_ON` / `LED_OFF`
    *   `FAN_ON` / `FAN_OFF`
    *   `GARAGE_OPEN` / `GARAGE_CLOSE`
    *   `DOOR_OPEN` / `DOOR_CLOSE`

## Serial Communication Protocol

The Arduino communicates with MATLAB using a simple protocol:

- `D[value]` : Distance in cm (e.g., `D15`)
- `T[value]` : Temperature in °C (e.g., `T25.30`)
- `L[value]` : LDR state (0/1 for Dark/Bright)
- `G[UID]`   : Scanned RFID Tag UID (e.g., `Gaa bb cc dd`)

**Anas Alghannam** - [GitHub Profile](https://github.com/AnasAlghannam)
