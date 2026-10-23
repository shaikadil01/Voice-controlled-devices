# Voice-Controlled Devices Using voice Assistant

## 📌 About the Project
This project uses an ESP32 to control a light and a fan through voice commands. It uses Wi-Fi and Sinric Pro to connect the devices with Google Home.

## 🛠️ Components Required
- ESP32 development board
- 2-channel 5V relay module
- Jumper wires
- Light and fan
- Power supply
- 
📚 Libraries Used
- Arduino.h – Provides basic Arduino functions
- WiFi.h – Connects the ESP32 to Wi-Fi
- SinricPro.h – Connects the ESP32 to the Sinric Pro cloud
- ArduinoJson – Handles JSON data used by Sinric Pro.
- WebSockets – Enables communication with the Sinric Pro service.

## ⚙️ How It Works
1. Give a voice command through Google Home.
2. Sinric Pro sends the command over Wi-Fi.
3. ESP32 receives the command.
4. The relay switches the light or fan ON or OFF.

## 🔌 Pin Connections

| Device | ESP32 GPIO Pin |
|---|---|
| Light | GPIO 13 |
| Fan | GPIO 14 |

## 💻 Software Required
- Arduino IDE
- ESP32 board package
- Sinric Pro account and Arduino library
- Google Home

## 🚀 How to Run
1. Install the required ESP32 and Sinric Pro libraries.
2. Add your Wi-Fi name and password to the code.
3. Enter your Sinric Pro App Key, App Secret, and device IDs.
4. Upload the code to the ESP32 using Arduino IDE.
5. Connect your Sinric Pro account with Google Home.
6. Use voice commands to control the devices.

## 🎙️ Example Voice Commands
- "Hey Google, turn on the light."
- "Hey Google, turn off the light."
- "Hey Google, turn on the fan."
- "Hey Google, turn off the fan."

## ✅ Result
The project successfully demonstrates voice-based control of a light and a fan using ESP32, Wi-Fi, Sinric Pro, and Google Home.

## 🔮 Future Improvements
- Add more appliances.
- Monitor devices through a mobile app.
- Expand the system for smart home automation.
