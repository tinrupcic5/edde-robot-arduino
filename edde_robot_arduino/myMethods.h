#ifndef MYMETHODS_H
#define MYMETHODS_H

#include <Adafruit_SH110X.h>

extern int ref_eye_height;
extern int ref_eye_width;
extern int ref_space_between_eye;
extern int ref_corner_radius;
extern int left_eye_x;
extern int left_eye_y;
extern int right_eye_x;
extern int right_eye_y;
extern int left_eye_height;
extern int left_eye_width;
extern int right_eye_height;
extern int right_eye_width;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern Adafruit_SH1106G display;

void draw_eyes(bool update = true);
void center_eyes(bool update = true);
void blink(int speed = 12, int times = 1);
void sleep();
void sleepFromEyesOpen();
void wakeup();
void happy_eye();
void saccade(int direction_x, int direction_y);
void move_right_big_eye();
void move_left_big_eye();
void move_big_eye(int direction);

void connect();
void httpRequestGetVersion();
void httpRequestCreateChat(String prompt);

#endif
