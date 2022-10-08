
// Touchscreen libraries
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>

// Touchscreen init/setup
MCUFRIEND_kbv tft;
#define MINPRESSURE 200
#define MAXPRESSURE 1000
const int XP=8,XM=A2,YP=A3,YM=9; 
const int TS_LEFT=961,TS_RT=94,TS_TOP=905,TS_BOT=118;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
uint16_t screen_width = 480;
uint16_t screen_height = 320;

int touch_x, touch_y;

#define BLACK   0x0000

bool get_touch_coordinates(void) {
    TSPoint p = ts.getPoint();
    
    pinMode(YP, OUTPUT);
    pinMode(XM, OUTPUT);

    digitalWrite(YP, HIGH);
    digitalWrite(XM, HIGH);

    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        touch_x = map(p.y, TS_LEFT, TS_RT, 0, screen_width);
        touch_y = map(p.x, TS_TOP, TS_BOT, 0, screen_height);

        Serial.print("(");
        Serial.print(touch_x);
        Serial.print(", ");
        Serial.print(touch_y);
        Serial.println(")");
    }
    return pressed;
} 

void setup(void) {
    Serial.begin(9600);

    uint16_t ID = tft.readID();
    tft.begin(ID);
    tft.setRotation(1);
    tft.fillScreen(BLACK);

}

void loop (void) {
    bool pressed = get_touch_coordinates();
}


