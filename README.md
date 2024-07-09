# Blynk_PZEM_PowerMonitor

This project implements a power monitoring system using an ESP32, Blynk, and PZEM-004T sensors. The system measures voltage, current, power, frequency, power factor, and total energy consumption from two separate PZEM-004T sensors and sends the data to the Blynk app for real-time monitoring.

## How It Works

1. **Initialization**:
    - The ESP32 connects to a Wi-Fi network using the provided credentials.
    - It initializes the serial ports for communication with the PZEM-004T sensors.
    - It connects to the Blynk cloud platform using the provided authentication token.
    - It initializes the preferences library to store and retrieve total energy consumption values.

2. **Reading Sensor Data**:
    - The system continuously reads voltage, current, power, frequency, power factor, and energy from two PZEM-004T sensors.
    - It calculates the total energy consumption for both sensors and stores these values in non-volatile storage.

3. **Sending Data to Blynk**:
    - The system sends the measured values to the Blynk app using virtual pins.
    - If the power reading is zero or negative, the system sets all readings to zero to avoid invalid data.

4. **Resetting Total Energy**:
    - The system includes a reset button in the Blynk app that allows the user to reset the total energy consumption for both sensors.

## Components Used

- **ESP32**: Microcontroller to manage the system and connect to Wi-Fi.
- **PZEM-004T**: Power monitoring sensors to measure voltage, current, power, frequency, power factor, and energy.
- **Blynk**: IoT platform to display the measured values in real-time.

## Libraries Used

- `WiFi.h`: For Wi-Fi connectivity.
- `BlynkSimpleEsp32.h`: For interacting with Blynk.
- `PZEM004Tv30.h`: For communicating with PZEM-004T sensors.
- `Preferences.h`: For storing total energy consumption values in non-volatile storage.

## Code Overview

### Setup

In the `setup()` function, the ESP32:

1. Initializes serial communication for debugging.
2. Initializes serial communication with the PZEM-004T sensors.
3. Connects to the Wi-Fi network.
4. Connects to the Blynk platform.
5. Initializes the preferences library and retrieves total energy consumption values.

### Main Loop

In the `loop()` function, the ESP32:

1. Runs the Blynk process.
2. Reads values from both PZEM-004T sensors.
3. Prints the values to the Serial Monitor.
4. Sends the values to the Blynk app using virtual pins.
5. Saves the total energy consumption values to non-volatile storage.

### Functions

- `resetTotalPower()`: Resets the total energy consumption values for both sensors and saves them to non-volatile storage.
- `BLYNK_WRITE(V_PIN_RESET_BUTTON)`: Resets the total energy consumption values when the reset button is pressed in the Blynk app.

## Getting Started

1. **Clone the Repository**:
    ```bash
    git clone https://github.com/yourusername/Blynk_PZEM_PowerMonitor.git
    ```

2. **Install Required Libraries**:
    - WiFi
    - Blynk
    - PZEM004Tv30
    - Preferences

3. **Set Up Your Hardware**:
    - Connect the PZEM-004T sensors to the ESP32 as per the pin configuration in the code.

4. **Configure Your Wi-Fi and Blynk Credentials**:
    - Replace the placeholders in the code with your Wi-Fi SSID, password, and Blynk authentication token.

5. **Upload the Code**:
    - Upload the code to your ESP32 using the Arduino IDE.

6. **Monitor Your Power Consumption**:
    - Open the Blynk app and add the appropriate widgets to display the voltage, current, power, frequency, power factor, and total energy values.
