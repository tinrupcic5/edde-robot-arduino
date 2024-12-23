# Edde the Robot :robot:

This project focuses on creating a robot with animated, movable eyes that can interact and chat with users. Powered by Arduino, the robot features eye movements. It connects to a Spring Boot application, enabling AI capabilities to answer questions and engage in conversations.

:warning: Still in progress

Key features:
- Animated eye movements
- Wi-Fi connectivity to a Spring Boot app
- AI-powered question answering functionality

### Display Specifications:
- **Model**: Adafruit SH1106 (a common variant of the SH110X series)
- **Resolution**: 128x64 pixels (common for many small OLED displays)
- **Size**: Typically 1.3 inches diagonal (although size can vary)


## Technologies
- Arduino MKR WIFI 1010
- Wi-Fi (WiFiNINA)
- Spring Boot (AI interaction)

## How it works
- The robot communicates with the Spring Boot app to query AI models for responses.
- Eye animations are controlled based on the robot's state, adding personality to interactions.
<img src="https://github.com/tinrupcic5/edde-robot-arduino/blob/main/images/edde%20message.png" alt="Response" width="600"/>

## Setup
1. Upload the Arduino code to the board.
2. Set up the Spring Boot backend to handle AI requests [API](https://github.com/tinrupcic5/edde-rest-api).
3. Connect the robot to Wi-Fi and let it interact with the app.

# Connecting SH1106 OLED Display to Arduino

### Wiring:
| SH1106 Pin | Arduino Pin     |
|------------|-----------------|
| **VCC**    |  **VCC**        |
| **GND**    |  **GND**        |
| **SCK**    |  **SCL**        |
| **SDA**    |  **SDA**        |


## Future of Edde:
- **Face Recognition**: In the future, Edde will be equipped with a camera to recognize faces. This feature will allow Edde to identify and interact with specific individuals, offering personalized responses.
- **Improved AI Integration**: As AI capabilities evolve, Edde will be able to handle more complex conversations and even adapt its behavior based on previous interactions with users.
- **Enhanced Interactivity**: With the addition of cameras and other sensors, Edde will become even more interactive, responding to visual cues and gestures in real-time.
- **Android App Communication**: Future plans include developing an Android app that will allow users to communicate with Edde directly. The app will facilitate text-based or voice-based interaction, enabling users to ask questions and receive responses in real-time.

<img src="https://github.com/tinrupcic5/edde-robot-arduino/blob/main/images/edde1.jpeg" alt="Arduino" width="300"/>
<img src="https://github.com/tinrupcic5/edde-robot-arduino/blob/main/images/edde2.jpeg" alt="Edde Eyes" width="300"/>



