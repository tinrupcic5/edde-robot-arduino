#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <SPI.h>
#include <WiFiNINA.h>

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

  // Initialize the display
  display.begin(i2c_Address, true);
  display.clearDisplay();

  // Show initial display buffer contents on the screen
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.println(F("Edde is Waking up..."));
  display.display();
  delay(4600);
  

  connect();
}

void draw_eyes(bool update=true) {
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

void center_eyes(bool update=true) {
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

void blink(int speed=12) {
    draw_eyes();

    for(int i = 0; i < 3; i++) {
        left_eye_height -= speed;
        right_eye_height -= speed;    
        draw_eyes();
        delay(1);
    }
    for(int i = 0; i < 3; i++) {
        left_eye_height += speed;
        right_eye_height += speed;
        draw_eyes();
        delay(1);
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
    // First center the eyes
    center_eyes(false);
    
    sleep(); 

    // Animate the eyes opening
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


void connect() {
  // Initialize serial communication
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for the serial port to connect. Needed for native USB port only
  }

  // Check for the WiFi module
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // Don't continue
    while (true);
  }

  // Attempt to connect to WiFi network
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);

    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, password);

    // Wait 10 seconds for connection
    delay(10000);
  }

  // If connected to WiFi
  Serial.println("Connected to WiFi!");
  printWiFiStatus();
}

void printWiFiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}


void httpRequest() {
  WiFiClient client; // Create a WiFi client

  const char* server = "192.168.1.113"; // IP address of the server
  int port = 8888; // Port number of the server
  const char* path = "/api/properties/version"; // Path of the API endpoint

  // Connect to the server at the specified IP address and port
  Serial.print("Connecting to ");
  Serial.print(server);
  Serial.print(":");
  Serial.println(port);

  if (client.connect(server, port)) {
    Serial.println("Connected to server");

    // Make an HTTP GET request to the specified path
    client.print("GET ");
    client.print(path);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println(); // End of the request headers

  } else {
    Serial.println("Connection to server failed");
    return; // Exit the function if the connection failed
  }

  while (client.connected() && !client.available()) {
    delay(100); 
  }

  // Read the response from the server
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line); // Print the response to the Serial Monitor
  }

  // Close the connection
  client.stop();
  Serial.println();
  Serial.println("Connection closed");
}

// Define a time interval for switching cases
const unsigned long SWITCH_INTERVAL = 5000; // 5000 milliseconds = 5 seconds

// Variables to manage timing and current case
unsigned long lastSwitchTime = 0;
int currentCase = 0;

void loop() {
    unsigned long currentTime = millis(); // Get the current time

    if (currentTime - lastSwitchTime >= SWITCH_INTERVAL) {
        lastSwitchTime = currentTime;

        switch (currentCase) {
            case 0:
                wakeup();
                break;
            case 1:
                move_right_big_eye();
                break;
            case 2:
                move_left_big_eye();
                break;
            case 3:
                blink(10);
                break;
            case 4:
                happy_eye();
                break;
            case 5:
                sleepFromEyesOpen();
                break;
            case 6:
                httpRequest();
                break;
        }

        currentCase++;
        if (currentCase > 6) {
            currentCase = 0;
        }
    }
}
