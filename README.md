# Colorino
Colorino is an innovative and educational project designed to **sort Lacasitos (similar to M&M's) by color**. This advanced sorting machine is capable of detecting and categorizing Lacasitos into different containers based on their color. The project serves as a practical application to learn about the **TCS3200 color sensor**, **sequential state machine implementation**, **calibration** operations, **debugging** techniques, and **user interface** design through a selection **menu**. Furthermore, it introduces the concept of artificial intelligence by integrating a **basic [neural network model](https://github.com/moretticb/Neurona)** (Multiple-Layer Perceptron) for **enhanced color classification**.

## How It Works:

The operational model of Colorino involves a drum with three internal spaces, each corresponding to a specific stage in the sorting process. 
- The cycle begins by placing a Lacasito at the top of the drum. Upon initiating the program, the drum rotates to align the Lacasito with the TCS3200 color sensor for color detection.
- Once the color is determined, a selector tube moves to position the Lacasito into the appropriate container based on its color.
- The drum then rotates to the next position, allowing the Lacasito to fall through the selector tube into the container.


![Screenshot from 2023-12-29 16-52-35](https://github.com/blascarr/Colorino/assets/6161706/44c80c03-7cdd-438d-85b6-1fa9b9ba8703)


![Screenshot from 2023-12-29 16-52-16](https://github.com/blascarr/Colorino/assets/6161706/56174ff2-29a6-45bc-94b3-1511b87bf0fd)

## Materials
- 3D Printed Parts ( 20 Screws )
- TCS3200 Color Sensor
- Infrared Sensor
- MG90S Servo Motor (Positional)
- Continuous Servo Motor
- 
- I2C Display
- Rotary Encoder
- Push Button
- Arduino UNO, MEGA (ESP8266, ESP32 Compatibility)
- Connection Shield

## Calibration:

To ensure accurate color detection, **Colorino requires initial calibration** to adapt to varying light conditions and environmental settings. This calibration can be conveniently conducted through a serial port menu or an I2C-connected display, interfaced with an encoder and a button. This flexibility allows users to fine-tune the sensor for optimal performance in different lighting conditions.

## Extra Features:

**Colorino** integrates a **[Neuronal system](https://github.com/moretticb/Neurona)** to eliminate the need for manual color calibration. Colorino can predict the color of a Lacasito with a single reading. 

Calibration of **Black** and **White** color define the references necessary for accurate color readings. These **calibration values are stored in the EEPROM**, eliminating the need for recalibration each time the system is powered on.

# Colorino Course

**Colorino** is not just a fun and interactive tool but also an excellent educational platform. It offers hands-on experience with hardware-software integration, programming concepts, AI basics, and an introduction to user interface design. This project is ideal for students, hobbyists, and anyone interested in exploring the realms of electronics, programming, and robotics.

- Sensor State Detection.
- Non-blocking operations during execution with **[Ticker library](https://github.com/sstaub/Ticker)**.
- Color Calibration.
- Menu Interface with debugging tools.
- **[State Machine](https://github.com/jrullan/StateMachine)** Concept for sequential operations involved in the model.
- **[Neuronal system](https://github.com/moretticb/Neurona)** application in order to improve Color classification system.

## Libraries required 

- **[State Machine](https://github.com/jrullan/StateMachine)** library from Library Manager. Maybe [PCINT](https://github.com/neu-rah/PCINT/blob/master/src/pcint.h) is also required.
- **[Ticker library](https://github.com/sstaub/Ticker)** library from Library Manager.
- **[Neurona](https://github.com/moretticb/Neurona)** library from Library Manager.
- **[TCS3200](https://github.com/blascarr/TCS3200/)**. Download Library and copy on libraries Arduino folder.
- **[Bounce2](https://github.com/thomasfredericks/Bounce2/)** library from Library Manager.
- **[ArduinoMenu](https://github.com/neu-rah/ArduinoMenu)** library from Library Manager.
- **[LiquidCrystal_PCF8574](https://github.com/mathertel/LiquidCrystal_PCF8574)** library from Library Manager.


## Support and Compatibility

- **Arduino UNO**(Limited by memory constraints)
- **Arduino MEGA** (Extended menu for detailed calibration)
- **ESP8266/ESP32** (Features under development)
