
// Touchscreen libraries
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>

#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <FreeDefaultFonts.h>
#include <gfxfont.h>

// Touchscreen init/setup
MCUFRIEND_kbv tft;
#define MINPRESSURE 200
#define MAXPRESSURE 1000
const int XP=8,XM=A2,YP=A3,YM=9; 
const int TS_LEFT=961,TS_RT=94,TS_TOP=905,TS_BOT=118;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
uint16_t screen_width = 480;
uint16_t screen_height = 320;
int16_t x1, y1;
uint16_t w, h, text_left;
int touch_x, touch_y;

// Button Setup
Adafruit_GFX_Button total_dec_btn, total_inc_btn, jade_dec_btn, jade_inc_btn, kacper_dec_btn, kacper_inc_btn, reset_btn;
uint16_t total_y = 120;
uint16_t jade_y = 180;
uint16_t kacper_y = 240;
uint16_t button_width = 60;
uint16_t button_height = 32;
uint16_t dec_button_x;
uint16_t inc_button_x;
byte button_buffer_x = 12;
byte button_buffer_y = 6;

uint16_t counters_left = 270;
uint16_t reset_btn_height = 40;
uint16_t reset_btn_width;
uint16_t reset_btn_y = kacper_y+4*button_buffer_y;
uint16_t reset_btn_x = counters_left;

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define MAGENTA 0xF81F
#define WHITE   0xFFFF

// #define GREEN   0x07E0
// #define CYAN    0x07FF
// #define YELLOW  0xFFE0

void find_button_dimensions() {
    tft.setFont(&FreeMonoBold18pt7b);
    tft.getTextBounds("00/00", 0, 0, &x1, &y1, &w, &h);

    dec_button_x = counters_left - (button_buffer_x + button_width);
    inc_button_x = counters_left + w + 1.5*button_buffer_x;
    reset_btn_width = w;
}

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

        // PRINT TOUCH COORDINATES FOR DEBUGGIN
        char buffer[10];
        sprintf (buffer, "(%03d, %03d)", touch_x, touch_y);
        Serial.println(buffer);
    }
    return pressed;
} 

void setup(void) {
    Serial.begin(9600);

    uint16_t ID = tft.readID();
    tft.begin(ID);
    tft.setRotation(1);
    tft.fillScreen(BLACK);

    find_button_dimensions();

    tft.setFont(NULL);
    total_dec_btn.initButtonUL(&tft, dec_button_x, total_y-button_height+button_buffer_y, button_width, button_height, WHITE, BLUE, WHITE, "-", 2);
    total_dec_btn.drawButton(false);

    total_inc_btn.initButtonUL(&tft, inc_button_x, total_y-button_height+button_buffer_y, button_width, button_height, WHITE, BLUE, WHITE, "+", 2);
    total_inc_btn.drawButton(false);

    jade_dec_btn.initButtonUL(&tft, dec_button_x, jade_y-button_height+button_buffer_y, button_width, button_height, WHITE, BLUE, WHITE, "+", 2);
    jade_dec_btn.drawButton(false);

    jade_inc_btn.initButtonUL(&tft, inc_button_x, jade_y-button_height+button_buffer_y, button_width, button_height, WHITE, BLUE, WHITE, "+", 2);
    jade_inc_btn.drawButton(false);

    kacper_dec_btn.initButtonUL(&tft, dec_button_x, kacper_y-button_height+button_buffer_y, button_width, button_height, WHITE, BLUE, WHITE, "+", 2);
    kacper_dec_btn.drawButton(false);

    kacper_inc_btn.initButtonUL(&tft, inc_button_x, kacper_y-button_height+button_buffer_y, button_width, button_height, WHITE, BLUE, WHITE, "+", 2);
    kacper_inc_btn.drawButton(false);

    reset_btn.initButtonUL(&tft, reset_btn_x, reset_btn_y, reset_btn_width, reset_btn_height, WHITE, RED, WHITE, "RESET", 2);
    reset_btn.drawButton(false);

}

void loop (void) {

    bool pressed = get_touch_coordinates();

}


