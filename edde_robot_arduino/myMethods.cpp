// myMethods.cpp
#include "myMethods.h"
#include <WiFiNINA.h>
#include <Arduino.h> /
// Define the screen dimensions
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


extern const char* ssid; 
extern const char* password;
extern int status;

void connect() {
    Serial.begin(9600);
    while (!Serial) {
        ; 
    }

    if (WiFi.status() == WL_NO_MODULE) {
        Serial.println("Communication with WiFi module failed!");
        while (true);
    }

    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid);
        status = WiFi.begin(ssid, password);
        delay(10000);
    }

    Serial.println("Connected to WiFi!");
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Signal strength (RSSI): ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
}

void httpRequestGetVersion() {
    WiFiClient client;

    const char* server = "192.168.1.65";
    int port = 8888;
    const char* path = "/api/info/";

    Serial.print("Connecting to ");
    Serial.print(server);
    Serial.print(":");
    Serial.println(port);

    if (client.connect(server, port)) {
        Serial.println("Connected to server");
        client.print("GET ");
        client.print(path);
        client.println(" HTTP/1.1");
        client.print("Host: ");
        client.println(server);
        client.println("Connection: close");
        client.println();

        while (client.connected() && !client.available()) {
            delay(100);
        }

        while (client.available()) {
            String line = client.readStringUntil('\r');
            Serial.print(line);
        }

        client.stop();
        Serial.println("Connection closed");
    } else {
        Serial.println("Connection to server failed");
    }
}

void httpRequestCreateChat() {
    WiFiClient client;

    const char* server = "192.168.1.65";
    int port = 8888;
    const char* path = "/api/chat/";
    String jsonPayload = "{\"prompt\": \"What is your name?\"}";

    Serial.print("Connecting to ");
    Serial.print(server);
    Serial.print(":");
    Serial.println(port);

    if (client.connect(server, port)) {
        Serial.println("Connected to server");
        client.print("GET ");
        client.print(path);
        client.println(" HTTP/1.1");
        client.print("Host: ");
        client.println(server);
        client.println("Content-Type: application/json");
        client.print("Content-Length: ");
        client.println(jsonPayload.length());
        client.println("Connection: close");
        client.println();
        client.println(jsonPayload);

        while (client.connected() && !client.available()) {
            delay(100);
        }

        while (client.available()) {
            String line = client.readStringUntil('\r');
            Serial.print(line);
        }

        client.stop();
        Serial.println("Connection closed");
    } else {
        Serial.println("Connection to server failed");
    }
}
void draw_eyes(bool update) {
    display.clearDisplay();
    // Draw from center
    int x = left_eye_x - left_eye_width / 2;
    int y = left_eye_y - left_eye_height / 2;
    display.fillRoundRect(x, y, left_eye_width, left_eye_height, ref_corner_radius, SH110X_WHITE);
    x = right_eye_x - right_eye_width / 2;
    y = right_eye_y - right_eye_height / 2;
    display.fillRoundRect(x, y, right_eye_width, right_eye_height, ref_corner_radius, SH110X_WHITE);
    if (update) {
        display.display();
    }
}

void center_eyes(bool update) {
    left_eye_height = ref_eye_height;
    left_eye_width = ref_eye_width;
    right_eye_height = ref_eye_height;
    right_eye_width = ref_eye_width;

    left_eye_x = SCREEN_WIDTH / 2 - ref_eye_width / 2 - ref_space_between_eye / 2;
    left_eye_y = SCREEN_HEIGHT / 2;
    right_eye_x = SCREEN_WIDTH / 2 + ref_eye_width / 2 + ref_space_between_eye / 2;
    right_eye_y = SCREEN_HEIGHT / 2;

    draw_eyes(update);
}
void blink(int speed, int times) {
    draw_eyes();

    for (int t = 0; t < times; t++) {
        for (int i = 0; i < 3; i++) {
            left_eye_height -= speed;
            right_eye_height -= speed;
            draw_eyes();
            delay(1);
        }
        
        for (int i = 0; i < 3; i++) {
            left_eye_height += speed;
            right_eye_height += speed;
            draw_eyes();
            delay(1); 
        }

        delay(500);
    }
}



void sleep() {
    left_eye_height = 2;
    right_eye_height = 2;
    draw_eyes(true);  
}

void sleepFromEyesOpen() {
    for(int h = ref_eye_height; h >= 2; h -= 2) {
        left_eye_height = h;
        right_eye_height = h;
        draw_eyes(true);
    }
}

void wakeup() {
    center_eyes(false);
    
    sleep(); 

    for(int h = 0; h <= ref_eye_height; h += 2) {
        left_eye_height = h;
        right_eye_height = h;
        draw_eyes(true);
    }
}

void happy_eye() {
    center_eyes(false);
    int offset = ref_eye_height / 2;
    for(int i = 0; i < 10; i++) {
        display.fillTriangle(left_eye_x - left_eye_width / 2 - 1, left_eye_y + offset,
                             left_eye_x + left_eye_width / 2 + 1, left_eye_y + 5 + offset,
                             left_eye_x - left_eye_width / 2 - 1, left_eye_y + left_eye_height + offset,
                             SH110X_BLACK);
                             
        display.fillTriangle(right_eye_x + right_eye_width / 2 + 1, right_eye_y + offset,
                             right_eye_x - right_eye_width / 2 - 1, right_eye_y + 5 + offset,
                             right_eye_x + right_eye_width / 2 + 1, right_eye_y + right_eye_height + offset,
                             SH110X_BLACK);
        offset -= 2;
        display.display();
        delay(1);
    }
    display.display();
    delay(1000);
}

void saccade(int direction_x, int direction_y) {
    int direction_x_movement_amplitude = 8;
    int direction_y_movement_amplitude = 6;
    int blink_amplitude = 8;

    for(int i = 0; i < 1; i++) {
        left_eye_x += direction_x_movement_amplitude * direction_x;
        right_eye_x += direction_x_movement_amplitude * direction_x;    
        left_eye_y += direction_y_movement_amplitude * direction_y;
        right_eye_y += direction_y_movement_amplitude * direction_y;    

        right_eye_height -= blink_amplitude;
        left_eye_height -= blink_amplitude;
        draw_eyes();
        delay(1);
    }

    for(int i = 0; i < 1; i++) {
        left_eye_x += direction_x_movement_amplitude * direction_x;
        right_eye_x += direction_x_movement_amplitude * direction_x;    
        left_eye_y += direction_y_movement_amplitude * direction_y;
        right_eye_y += direction_y_movement_amplitude * direction_y;

        right_eye_height += blink_amplitude;
        left_eye_height += blink_amplitude;
        draw_eyes();
        delay(1);
    }
}

void move_right_big_eye() {
    move_big_eye(1);
}

void move_left_big_eye() {
    move_big_eye(-1);
}

void move_big_eye(int direction) {
    int direction_oversize = 1;
    int direction_movement_amplitude = 2;
    int blink_amplitude = 5;

    for(int i = 0; i < 3; i++) {
        left_eye_x += direction_movement_amplitude * direction;
        right_eye_x += direction_movement_amplitude * direction;    
        right_eye_height -= blink_amplitude;
        left_eye_height -= blink_amplitude;
        if(direction > 0) {
            right_eye_height += direction_oversize;
            right_eye_width += direction_oversize;
        } else {
            left_eye_height += direction_oversize;
            left_eye_width += direction_oversize;
        }
        draw_eyes();
        delay(1);
    }
    for(int i = 0; i < 3; i++) {
        left_eye_x += direction_movement_amplitude * direction;
        right_eye_x += direction_movement_amplitude * direction;
        right_eye_height += blink_amplitude;
        left_eye_height += blink_amplitude;
        if(direction > 0) {
            right_eye_height += direction_oversize;
            right_eye_width += direction_oversize;
        } else {
            left_eye_height += direction_oversize;
            left_eye_width += direction_oversize;
        }
        draw_eyes();
        delay(1);
    }

    delay(1000);

    for(int i = 0; i < 3; i++) {
        left_eye_x -= direction_movement_amplitude * direction;
        right_eye_x -= direction_movement_amplitude * direction;    
        right_eye_height -= blink_amplitude;
        left_eye_height -= blink_amplitude;
        if(direction > 0) {
            right_eye_height -= direction_oversize;
            right_eye_width -= direction_oversize;
        } else {
            left_eye_height -= direction_oversize;
            left_eye_width -= direction_oversize;
        }
        draw_eyes();
        delay(1);
    }
    for(int i = 0; i < 3; i++) {
        left_eye_x -= direction_movement_amplitude * direction;
        right_eye_x -= direction_movement_amplitude * direction;    
        right_eye_height += blink_amplitude;
        left_eye_height += blink_amplitude;
        if(direction > 0) {
            right_eye_height -= direction_oversize;
            right_eye_width -= direction_oversize;
        } else {
            left_eye_height -= direction_oversize;
            left_eye_width -= direction_oversize;
        }
        draw_eyes();
        delay(1);
    }
}
