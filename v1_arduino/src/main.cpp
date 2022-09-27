#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <Adafruit_GFX.h>

// #include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>

// Calibration Values
const int XP=8,XM=A2,YP=A3,YM=9;
const int TS_LEFT=140,TS_RT=872,TS_TOP=936,TS_BOT=104;

// Touchscreen Constructors
MCUFRIEND_kbv tft;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

int16_t x1, y1;
uint16_t w, h, text_left;
uint16_t screen_width = 480;
uint16_t screen_height = 320;
uint16_t total_y = 120;
uint16_t jade_y = 180;
uint16_t kacper_y = 240;

uint16_t counters_left = 250;
byte max_treats = 12;
byte kacper_treats = 0;
byte jade_treats = 0;


void render_title() {
    uint16_t title_buffer = 12;
    String title_text = "Willow's Treat Tracker";
    tft.setFont(&FreeSansBold18pt7b);
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


void render_static_text() {
    tft.setFont(&FreeSans18pt7b);
    
    tft.setCursor(text_left, total_y);
    tft.print("TOTAL:");

    tft.setCursor(text_left, jade_y);
    tft.print("Jade:");

    tft.setCursor(text_left, kacper_y);
    tft.print("Kacper:");
}


void render_treats_count(int used, int max, uint16_t ypos) {
    char buffer[5];
    sprintf(buffer, "%02d/%02d", used, max);
    tft.setFont(&FreeMonoBold18pt7b);
    tft.setCursor(counters_left, ypos);
    tft.print(buffer);
}


void render_initial_treats_count() {
    render_treats_count(0, max_treats, total_y);
    render_treats_count(kacper_treats, max_treats/2, kacper_y);
    render_treats_count(jade_treats, max_treats/2, jade_y);
}


void setup(void)
{
    // Initialize the touchscreen
    tft.reset();
    uint16_t id = tft.readID();
    tft.begin(id);
    tft.setRotation(1);
    tft.fillScreen(BLACK);

    render_title();
    render_static_text();
    render_initial_treats_count();
}

void loop(void) {}