#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <Adafruit_GFX.h>

#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeSans18pt7b.h>

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
uint16_t w, h;
uint16_t screen_width = 480;
uint16_t screen_height = 320;

void render_title() {
    uint16_t title_buffer = 12;
    String title_text = "Willow's Treat Tracker";
    tft.setFont(&FreeSans18pt7b);
    tft.getTextBounds(title_text, 0, 0, &x1, &y1, &w, &h);

    tft.drawRect(
        (screen_width - w - 2*title_buffer)/2,
        title_buffer,
        w + 2*title_buffer,
        h + 2*title_buffer,
        MAGENTA
    );
    
    tft.setCursor((screen_width - w)/2, 2*title_buffer + h);
    tft.setTextColor(WHITE);
    tft.print(title_text);
}

void render_static_text() {}

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
}


void loop(void) {}