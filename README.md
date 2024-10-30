# Edde : The Interactive Robot with Wi-Fi Capabilities :space_invader:

## Overview
Edde is an interactive robot designed to simulate expressive eye movements and responses using an OLED display. It incorporates Wi-Fi connectivity to enable communication with a server, making it a versatile platform for various IoT applications. 

## Features
- **Expressive Eyes**: Utilizes a 128x64 OLED display to render dynamic eye animations.
- **Wi-Fi Connectivity**: Connects to a specified Wi-Fi network and can make HTTP requests to a designated server, facilitating data exchange and remote control.
- **Modular Design**: The eye movements and animations can be easily modified or extended, making it adaptable for various projects.
- **Simple API Requests**: Retrieves data from a server through basic HTTP GET requests, enabling integration with other web services.

## Components
- **Microcontroller**: Built on an Arduino-compatible platform MKR WiFi 1010.
- **Display**: Features an Adafruit SH1106G OLED screen for clear visual feedback and animations.
- **Wi-Fi Module**: Powered by the WiFiNINA library, allowing seamless connection to Wi-Fi networks for remote operation.

## Future of Edde
The vision for Edde includes the development of an AI backend that will enable more sophisticated eye movements and interactions. Future enhancements may include:
- **Face Tracking**: Integrating a camera to track faces, allowing Edde to follow users with its eyes.
- **Interactive Responses**: Adding capabilities for Edde to respond with text, enabling a more engaging and interactive experience.
- **Autonomous Behavior**: Implementing AI algorithms to allow Edde to move its eyes freely and react to its environment dynamically.

## Edde communication to RestApi
- Edde AI Rest Api ([repository](https://github.com/tinrupcic5/edde-rest-api.git))
- Edde will utilize the AI REST API to facilitate real-time communication, enabling it to respond intelligently to user queries.


