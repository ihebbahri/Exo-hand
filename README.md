# Exo-hand

## Overview

Exo-hand is an open-source project for a proportional control exoskeleton hand using EMG (Electromyography) signals and servo motors. The system reads muscle activity from an EMG sensor and translates it into smooth, proportional finger movements using five servos, one for each finger.

## Features

- Reads EMG signals from a sensor
- Controls five servos for thumb, index, middle, ring, and pinky fingers
- Proportional mapping of muscle contraction to finger movement
- Designed for ESP32 microcontroller

## Hardware Requirements

- ESP32 microcontroller
- 5x Servo motors
- EMG sensor (analog output)
- Jumper wires
- Power supply for servos

## Pin Connections

- EMG sensor analog output: GPIO 34
- Servo Thumb: GPIO 13
- Servo Index: GPIO 14
- Servo Middle: GPIO 27
- Servo Ring: GPIO 26
- Servo Pinky: GPIO 25

## How It Works

1. The EMG sensor detects muscle activity and outputs an analog signal.
2. The ESP32 reads the EMG value and maps it proportionally to a servo angle (e.g., 60° to 120°).
3. All five servos move together, mimicking the strength of the muscle contraction.
4. Serial output provides live feedback for debugging and calibration.

## Getting Started

1. Connect the hardware as described above.
2. Open `exohand_code/exohand_code.ino` in the Arduino IDE.
3. Select ESP32 as the board and upload the code.
4. Adjust `minEMG` and `maxEMG` in the code to calibrate for your EMG sensor.

## Code Overview

The main loop reads the EMG value, constrains it, maps it to a servo angle, and writes the angle to all five servos. Serial output helps with calibration and debugging.

```cpp
#include <Servo.h>
// ...existing code...
void loop() {
  emgValue = analogRead(emgPin);
  emgValue = constrain(emgValue, minEMG, maxEMG);
  servoAngle = map(emgValue, minEMG, maxEMG, 60, 120);
  servoPouce.write(servoAngle);
  // ...existing code...
}
```

## License

This project is licensed under the MIT License. See `LICENSE` for details.