# Water Level Monitoring System for Agriculture & Flood Control
This project is a real-time water level monitoring system designed for agricultural and flood control applications. It utilizes an ESP32, an ultrasonic sensor, and a set of servo motors to monitor and control water levels in various environments (e.g., irrigation systems, levees, and dams). The system tracks water level trends (e.g., fast/slow rises, falls, and stable states) and automatically opens or closes valves to protect farmland and infrastructure.

Features
Real-time water level monitoring using an ultrasonic sensor.

Servo control to automate water management (e.g., opening or closing valves).

Fast/slow rise or fall detection of water levels.

Cost-effective IoT solution with easy deployment for agriculture and flood management.

Hardware Requirements
ESP32 development board (DOIT ESP32 DEVKIT V1 or equivalent).

HC-SR04 ultrasonic sensor.

VCC → 5V

GND → GND

TRIG → GPIO 5

ECHO → GPIO 18

2 Servo Motors for controlling water pump and drainage valve.

LEDs for visual status indication (optional).

Jumper wires and breadboard for connections.

Software Requirements
Arduino IDE (version 1.8.19 or higher).

ESP32 Board Package installed in the Arduino IDE.

Libraries:

WiFi.h (for ESP32 Wi-Fi functionality).

Ultrasonic.h (for ultrasonic sensor control, or manual code for reading ultrasonic data).

Servo.h (for controlling servo motors).

Installation Instructions
Step 1: Install Arduino IDE
Download and install the Arduino IDE if you don't have it installed.

Open the Arduino IDE and go to File > Preferences.

Add the following ESP32 Board Manager URL in the Additional Boards Manager URLs field:

arduino
Copy
https://dl.espressif.com/dl/package_esp32_index.json
Go to Tools > Board > Boards Manager, search for ESP32, and install it.

Step 2: Install Libraries
In Arduino IDE, go to Sketch > Include Library > Manage Libraries.

Search for and install the following libraries:

WiFi.h (for ESP32 Wi-Fi support).

Ultrasonic.h (or manually use digitalWrite() and pulseIn() for the ultrasonic sensor).

Servo.h (for controlling servos).

Step 3: Set Up Hardware
Connect the HC-SR04 ultrasonic sensor to the ESP32 using the following pin assignments:

TRIG → GPIO 5

ECHO → GPIO 18

VCC → 5V

GND → GND

Connect the Servo Motors to GPIO 13 and GPIO 12 for controlling the pump and drainage.

If using LEDs, connect them to appropriate GPIO pins (e.g., GPIO 23 for the red LED and GPIO 22 for the green LED).

Step 4: Upload Code to ESP32
Open the Arduino IDE.

Select DOIT ESP32 DEVKIT V1 under Tools > Board.

Connect the ESP32 to your computer via USB and select the correct port under Tools > Port.

Upload the provided code (in the water_level_monitoring.ino file) to the ESP32.

Code Explanation
Ultrasonic Sensor:
The system uses the HC-SR04 ultrasonic sensor to measure the distance to the water surface. This distance is used to calculate the water level in the system. The code triggers the sensor to emit an ultrasonic pulse and then listens for the echo. Based on the time it takes for the echo to return, the distance is calculated.

Servo Motors:
The system controls two servo motors:

Water Pump (Servo 1): Opens when water levels are low and needs to be filled.

Drainage Valve (Servo 2): Opens when water levels are too high and needs to be drained.

Water Level Trend Detection:
The system tracks whether the water level is rising or falling, and based on the rate of change, it takes actions:

Fast Rise: Trigger the drainage valve.

Slow Rise: Trigger the water pump to refill.

Fast Fall: Trigger the water pump to refill.

Slow Fall: Trigger the drainage valve.
