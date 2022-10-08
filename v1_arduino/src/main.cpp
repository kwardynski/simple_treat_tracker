#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <Adafruit_GFX.h>

// #include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <FreeDefaultFonts.h>
#include <gfxfont.h>


// Calibration Values
const int XP=8,XM=A2,YP=A3,YM=9;
const int TS_LEFT=151,TS_RT=861,TS_TOP=923,TS_BOT=114;


// Touchscreen Constructors
MCUFRIEND_kbv tft;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
#define MINPRESSURE 200
#define MAXPRESSURE 200

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
// #define GREEN   0x07E0
// #define CYAN    0x07FF
#define MAGENTA 0xF81F
// #define YELLOW  0xFFE0
#define WHITE   0xFFFF

int16_t x1, y1;
uint16_t w, h, text_left;
uint16_t screen_width = 480;
uint16_t screen_height = 320;
uint16_t total_y = 120;
uint16_t jade_y = 180;
uint16_t kacper_y = 240;

uint16_t counters_left = 270;
byte max_treats = 12;
byte kacper_treats = 0;
byte jade_treats = 0;

uint16_t button_width = 60;
uint16_t button_height = 32;
uint16_t dec_button_x;
uint16_t inc_button_x;
byte button_buffer_x = 12;
byte button_buffer_y = 6;

uint16_t reset_btn_height = 40;
uint16_t reset_btn_width;
uint16_t reset_btn_y = kacper_y+4*button_buffer_y;
uint16_t reset_btn_x = counters_left;

Adafruit_GFX_Button total_dec_btn, total_inc_btn, jade_dec_btn, jade_inc_btn, kacper_dec_btn, kacper_inc_btn, reset_btn;

uint16_t pixel_x, pixel_y;

void draw_text(uint16_t x, uint16_t y, String text) {
    tft.setCursor(x, y);
    tft.print(text);
}

void render_title() {
    uint16_t title_buffer = 12;
    String title_text = "Willow's Treat Tracker";
    tft.getTextBounds(title_text, 0, 0, &x1, &y1, &w, &h);
    text_left = (screen_width - w - 2*title_buffer)/2;

    tft.drawRect(
        text_left,
        title_buffer,
        w + 2*title_buffer,
        h + 2*title_buffer,
        MAGENTA
    );
    
    tft.setCursor((screen_width - w)/2, 2*title_buffer + h);
    tft.setTextColor(WHITE);
    tft.print(title_text);
}

void render_treats_count(int used, int max, uint16_t ypos) {
    char buffer[5];
    sprintf(buffer, "%02d/%02d", used, max);
    draw_text(counters_left, ypos, buffer);
}

void find_button_dimensions() {
    tft.setFont(&FreeMonoBold18pt7b);
    tft.getTextBounds("00/00", 0, 0, &x1, &y1, &w, &h);

    dec_button_x = counters_left - (button_buffer_x + button_width);
    inc_button_x = counters_left + w + 1.5*button_buffer_x;
    reset_btn_width = w;
}

bool Touch_getXY(void)
{
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   //because TFT control pins
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
    if (pressed) {
        pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
        pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());

        Serial.print("(");
        Serial.print(pixel_x);
        Serial.print(", ");
        Serial.print(pixel_y);
        Serial.println(")");
    }
    return pressed;
}

void setup(void) {

    Serial.begin(9600);

    // Initialize the touchscreen
    tft.reset();
    uint16_t id = tft.readID();
    tft.begin(id);
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

    tft.setFont(&FreeSansBold18pt7b);
    tft.setTextSize(1);
    render_title();

    tft.setFont(&FreeSans18pt7b);
    draw_text(text_left, total_y, "TOTAL:");
    draw_text(text_left, jade_y, "Jade:");
    draw_text(text_left, kacper_y, "Kacper");

    tft.setFont(&FreeMonoBold18pt7b);
    render_treats_count(0, max_treats, total_y);
    render_treats_count(0, max_treats/2, jade_y);
    render_treats_count(0, max_treats/2, kacper_y);
}

void loop(void) {

    bool down = Touch_getXY();
    
}