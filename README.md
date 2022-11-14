# Simple Treat Tracker
An arduino based touch-screen treat tracker so we don't make our cat too fat.
![Willow](images/willow.jpg)

## Hardware:
- [Arduino Mega (clone)](https://www.amazon.ca/gp/product/B01H4ZDYCE/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
- [3.5" TFT Touch Display](https://www.amazon.ca/gp/product/B077ZT7S38/ref=ppx_yo_dt_b_search_asin_image?ie=UTF8&psc=1)

## Libaries:
- Adafruit_BusIO
- Adafruit_GFX_Library
- Adafruit_TouchScreen
- MCUFRIEND_kbv

## "Considerations":
- As _ok_ as the arduino IDE is, I think this is the perfect time to start using [PlatformIO](https://platformio.org/). Having intellisense outweighs the fact that managing arduino libraries is slightly clunkier with PlatformIO than the arduino IDE is a tradeoff I'm willing to make. 
- My touchscreen had to be calibrated, the `TouchScreen_Calibr_native.ino` sketch included in the examples of the `MCUFRIEND_kbv` library provides all the necessary calibration info required to get my screen functioning properly.

## TODO:
[Jira Board](https://kwardynski.atlassian.net/jira/software/projects/TT1/boards/3)
- [ ] Install the screen in the purchased box
- [ ] Re-draw buttons as pressed/released when pressed/released 
- [ ] Try thinning out the imported fonts libraries (remove unused characters) to reduce memory and see if it can be run on the UNO (this will reduce the draw latency on the screen with the Mega)
