#include "SmartLEDTon.h"
void showGradient() {
    hue++;
    // Use HSV to create nice gradient
    for ( int i = 0; i != LED_COUNT; i++ )
        leds[ i ] = Hsv{ static_cast< uint8_t >( hue + 30 * i ), 255, 255 };
    leds.show();
    // Show is asynchronous; if we need to wait for the end of transmission,
    // we can use leds.wait(); however we use double buffered mode, so we
    // can start drawing right after showing.
}

void showRgb() {
    leds[ 0 ] = Rgb{ 255, 0, 0 };
    leds[ 1 ] = Rgb{ 0, 255, 0 };
    leds[ 2 ] = Rgb{ 0, 0, 255 };
    leds[ 3 ] = Rgb{ 0, 0, 0 };
    leds[ 4 ] = Rgb{ 255, 255, 255 };
    leds.show();
}