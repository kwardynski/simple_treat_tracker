#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>

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

void setup(void)
{
    Serial.begin(9600);
}

void loop(void)
{
    
}


