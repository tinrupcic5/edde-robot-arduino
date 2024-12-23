#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include "myMethods.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)
#define i2c_Address 0x3c // Initialize with the I2C address

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Wi-Fi credentials and server details
const char* ssid = "";
const char* password = "";
int status = WL_IDLE_STATUS; // The WiFi radio's status

// Reference state
int ref_eye_height = 40;
int ref_eye_width = 40;
int ref_space_between_eye = 10;
int ref_corner_radius = 10;

// Current state of the eyes
int left_eye_height = ref_eye_height;
int left_eye_width = ref_eye_width;
int left_eye_x = 32;
int left_eye_y = 32;
int right_eye_x = 32 + ref_eye_width + ref_space_between_eye;
int right_eye_y = 32;
int right_eye_height = ref_eye_height;
int right_eye_width = ref_eye_width;


void setup() {
    Serial.begin(115200);
    display.begin(i2c_Address, true);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 0);
    display.println(F("Edde is Waking up..."));
    display.display();
    delay(4600);
    connect();
}

const unsigned long SWITCH_INTERVAL = 5000; // 5000 milliseconds = 5 seconds
unsigned long lastSwitchTime = 0;
int currentCase = 0;

void loop() {
    unsigned long currentTime = millis(); 

    if (currentTime - lastSwitchTime >= SWITCH_INTERVAL) {
        lastSwitchTime = currentTime;

        switch (currentCase) {
            case 0:
                wakeup();
                break;
            case 1:
                blink(10,2);
                break;   
            case 2:
                move_right_big_eye();
                break;
            case 3:
                move_left_big_eye();
                break;
            case 4:
                blink(10,1);
                break;
            case 5:
                happy_eye();
                break;
            case 6:
                sleepFromEyesOpen();
                break;
            case 7:
                httpRequestCreateChat(getRandomQuestion());
                break;
        }

        currentCase++;
        if (currentCase > 7) {
            currentCase = 0;
        }
    }
}
const String questions[] = {
    "What is your name?",
    "What is your favorite color?",
    "How old are you?",
    "Where do you live?",
    "What is your favorite food?",
    "What is your hobby?",
    "What is the meaning of life?",
    "What is your favorite movie?"
};

const int numQuestions = sizeof(questions) / sizeof(questions[0]);
String getRandomQuestion() {
    int randomIndex = random(numQuestions);  
    return questions[randomIndex];  
}
