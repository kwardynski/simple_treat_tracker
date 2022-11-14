
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

// TouchScreen - DRAW
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define MAGENTA 0xF81F
#define WHITE   0xFFFF
MCUFRIEND_kbv tft;
const uint16_t g_screen_width = 480;
const uint16_t g_screen_height = 320;
uint16_t g_text_left;

// TouchScreen - TOUCH
#define MINPRESSURE 50
#define MAXPRESSURE 1000
const int XP=8,XM=A2,YP=A3,YM=9; 
const int TS_LEFT=961,TS_RT=94,TS_TOP=905,TS_BOT=118;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
int16_t x1, y1;
uint16_t w, h;
bool pressed_state;
bool previous_pressed_state = false;
bool is_pressed = false;
long debounce_reference = 0;
const long g_debounce_delay = 50;
uint16_t touch_x, touch_y;
bool button_pressed = false;

// Button Setup
Adafruit_GFX_Button total_dec_btn, total_inc_btn, jade_dec_btn, jade_inc_btn, kacper_dec_btn, kacper_inc_btn, reset_btn;
const uint16_t g_total_y = 120;
const uint16_t g_jade_y = 180;
const uint16_t g_kacper_y = 240;
const uint16_t g_button_width = 60;
const uint16_t g_button_height = 32;
uint16_t dec_button_x;
uint16_t inc_button_x;
const byte g_button_buffer_x = 12;
const byte g_button_buffer_y = 6;

uint16_t reset_btn_width;
const uint16_t g_counters_left = 270;
const uint16_t g_reset_btn_height = 40;
const uint16_t g_reset_btn_y = g_kacper_y+4*g_button_buffer_y;
const uint16_t g_reset_btn_x = g_counters_left;

// Counter Setup
byte total_treats = 0;
byte max_treats = 8;
byte kacper_treats = 0;
byte jade_treats = 0;
char treats_string[5];


void find_button_dimensions() {
    tft.setFont(&FreeMonoBold18pt7b);
    tft.getTextBounds("00/00", 0, 0, &x1, &y1, &w, &h);
    dec_button_x = g_counters_left - (g_button_buffer_x + g_button_width);
    inc_button_x = g_counters_left + w + 1.5*g_button_buffer_x;
    reset_btn_width = w;
}

void draw_text(uint16_t x, uint16_t y, String text) {
    tft.setCursor(x, y);
    tft.print(text);
}

void render_title() {
    uint16_t title_buffer = 12;
    String title_text = "Willow's Treat Tracker";
    tft.getTextBounds(title_text, 0, 0, &x1, &y1, &w, &h);
    g_text_left = (g_screen_width - w - 2*title_buffer)/2;

    tft.drawRect(
        g_text_left,
        title_buffer,
        w + 2*title_buffer,
        h + 2*title_buffer,
        MAGENTA
    );

    tft.setCursor((g_screen_width - w)/2, 2*title_buffer + h);
    tft.setTextColor(WHITE);
    tft.print(title_text);
}

void draw_treats(int used, int max, uint16_t ypos, char* treats_string) {
    tft.setFont(&FreeMonoBold18pt7b);
    sprintf(treats_string, "%02d/%02d", used, max);

    tft.getTextBounds(treats_string, 0, 0, &x1, &y1, &w, &h);
    tft.fillRect(g_counters_left, ypos-h, 1.1*w, 1.1*h, BLACK);

    tft.setCursor(g_counters_left, ypos);
    tft.print(treats_string);
}

void setup(void) {
    Serial.begin(9600);

    uint16_t ID = tft.readID();
    tft.begin(ID);
    tft.setRotation(1);
    tft.fillScreen(BLACK);

    find_button_dimensions();

    tft.setFont(NULL);
    total_dec_btn.initButtonUL(&tft, dec_button_x, g_total_y-g_button_height+g_button_buffer_y, g_button_width, g_button_height, WHITE, BLUE, WHITE, "-", 2);
    total_dec_btn.drawButton(false);

    total_inc_btn.initButtonUL(&tft, inc_button_x, g_total_y-g_button_height+g_button_buffer_y, g_button_width, g_button_height, WHITE, BLUE, WHITE, "+", 2);
    total_inc_btn.drawButton(false);

    jade_dec_btn.initButtonUL(&tft, dec_button_x, g_jade_y-g_button_height+g_button_buffer_y, g_button_width, g_button_height, WHITE, BLUE, WHITE, "-", 2);
    jade_dec_btn.drawButton(false);

    jade_inc_btn.initButtonUL(&tft, inc_button_x, g_jade_y-g_button_height+g_button_buffer_y, g_button_width, g_button_height, WHITE, BLUE, WHITE, "+", 2);
    jade_inc_btn.drawButton(false);

    kacper_dec_btn.initButtonUL(&tft, dec_button_x, g_kacper_y-g_button_height+g_button_buffer_y, g_button_width, g_button_height, WHITE, BLUE, WHITE, "-", 2);
    kacper_dec_btn.drawButton(false);

    kacper_inc_btn.initButtonUL(&tft, inc_button_x, g_kacper_y-g_button_height+g_button_buffer_y, g_button_width, g_button_height, WHITE, BLUE, WHITE, "+", 2);
    kacper_inc_btn.drawButton(false);

    reset_btn.initButtonUL(&tft, g_reset_btn_x, g_reset_btn_y, reset_btn_width, g_reset_btn_height, WHITE, RED, WHITE, "RESET", 2);
    reset_btn.drawButton(false);

    tft.setFont(&FreeSansBold18pt7b);
    tft.setTextSize(1);
    render_title();

    tft.setFont(&FreeSans18pt7b);
    draw_text(g_text_left, g_total_y, "TOTAL:");
    draw_text(g_text_left, g_jade_y, "Jade:");
    draw_text(g_text_left, g_kacper_y, "Kacper");

    draw_treats(0, max_treats, g_total_y, treats_string);
    draw_treats(0, max_treats/2, g_jade_y, treats_string);
    draw_treats(0, max_treats/2, g_kacper_y, treats_string);
}



void loop (void) {

    // Check for touch point
    TSPoint touch_point = ts.getPoint();
    pinMode(YP, OUTPUT);
    pinMode(XM, OUTPUT); 

    // Check to see if screen is pressed and re-set debounce reference
    if (touch_point.z > MINPRESSURE && touch_point.z < MAXPRESSURE) {
        is_pressed = true;
        debounce_reference = millis();
    }

    // Determine whether the screen is actually released or a false negative requires debounce
    if (is_pressed == true && touch_point.z < MINPRESSURE) {
        if ((millis() - debounce_reference) > g_debounce_delay) {
            pressed_state = false;
        }
        else {
            pressed_state = true;
        }
    }

    // If initial press is registered, determine whether it is within the bounds of a button
    // and handle input appropriately
    if (previous_pressed_state == false && pressed_state == true) {

        touch_x = map(touch_point.y, TS_LEFT, TS_RT, 0, g_screen_width);
        touch_y = map(touch_point.x, TS_TOP, TS_BOT, 0, g_screen_height); 
    
        if (reset_btn.contains(touch_x, touch_y)) {
            total_treats = 0;
            jade_treats = 0;
            kacper_treats = 0;
            button_pressed = true;
        }

        else if (total_dec_btn.contains(touch_x, touch_y)) {
            if (max_treats > 0) {
                max_treats = max_treats - 2;
                button_pressed = true;
            }
        }

        else if (total_inc_btn.contains(touch_x, touch_y)) {
            max_treats = max_treats + 2;
            button_pressed = true;
        }

        else if (jade_dec_btn.contains(touch_x, touch_y)) {
            if (jade_treats > 0) {
                jade_treats = jade_treats - 1;
                button_pressed = true;
            }
        }

        else if (jade_inc_btn.contains(touch_x, touch_y)) {
            jade_treats = jade_treats + 1;
            button_pressed = true;
        }

        else if (kacper_dec_btn.contains(touch_x, touch_y)) {
            if (kacper_treats > 0) {
                kacper_treats = kacper_treats - 1;
                button_pressed = true;
            }
        }

        else if (kacper_inc_btn.contains(touch_x, touch_y)) {
            kacper_treats = kacper_treats + 1;
            button_pressed = true;
        }

        if (button_pressed) {
            draw_treats(jade_treats+kacper_treats, max_treats, g_total_y, treats_string);
            draw_treats(jade_treats, max_treats/2, g_jade_y, treats_string);
            draw_treats(kacper_treats, max_treats/2, g_kacper_y, treats_string);
        }
    }

    // If release is registered, reset button draw to false (unpressed) state 
    if (previous_pressed_state == true && pressed_state == false) {
        
    }

    previous_pressed_state = pressed_state;
    button_pressed = false;
}
