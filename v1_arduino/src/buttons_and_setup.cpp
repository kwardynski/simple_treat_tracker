// /* 
//     Moving anything not directly used by main.cpp to register a press into this file for debuggin
//     I want to separate as much as possible to track down the root of the issue - once it is
//     solved, the components will be moved back in and this file will be removed
// */ 



// // uint16_t screen_width = 480;
// // uint16_t screen_height = 320;

// byte max_treats = 12;
// byte kacper_treats = 0;
// byte jade_treats = 0;


// // uint16_t pixel_x, pixel_y;

// void draw_text(uint16_t x, uint16_t y, String text) {
//     tft.setCursor(x, y);
//     tft.print(text);
// }

// void render_title() {
//     uint16_t title_buffer = 12;
//     String title_text = "Willow's Treat Tracker";
//     tft.getTextBounds(title_text, 0, 0, &x1, &y1, &w, &h);
//     text_left = (screen_width - w - 2*title_buffer)/2;

//     tft.drawRect(
//         text_left,
//         title_buffer,
//         w + 2*title_buffer,
//         h + 2*title_buffer,
//         MAGENTA
//     );
    
//     tft.setCursor((screen_width - w)/2, 2*title_buffer + h);
//     tft.setTextColor(WHITE);
//     tft.print(title_text);
// }

// void render_treats_count(int used, int max, uint16_t ypos) {
//     char buffer[5];
//     sprintf(buffer, "%02d/%02d", used, max);
//     draw_text(counters_left, ypos, buffer);
// }





// void setup(void) {


//     tft.setFont(&FreeSansBold18pt7b);
//     tft.setTextSize(1);
//     render_title();

//     tft.setFont(&FreeSans18pt7b);
//     draw_text(text_left, total_y, "TOTAL:");
//     draw_text(text_left, jade_y, "Jade:");
//     draw_text(text_left, kacper_y, "Kacper");

//     tft.setFont(&FreeMonoBold18pt7b);
//     render_treats_count(0, max_treats, total_y);
//     render_treats_count(0, max_treats/2, jade_y);
//     render_treats_count(0, max_treats/2, kacper_y);
// }

// void loop(void) {

//     // bool down = Touch_getXY();
    
// }