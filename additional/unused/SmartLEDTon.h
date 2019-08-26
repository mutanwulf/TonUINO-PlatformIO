// Definitionfile for StatusLED
#ifndef SmartLEDTon_H
    #define SmartLEDTon_H
    #include <Arduino.h>
    #include <SmartLeds.h>
    //settings
    const int LED_COUNT = 15;
    const int DATA_PIN = 5;
    const int CHANNEL = 0;

    // SmartLed -> RMT driver (WS2812/WS2812B/SK6812/WS2813)
    SmartLed leds( LED_WS2812, LED_COUNT, DATA_PIN, CHANNEL, DoubleBuffer );
    uint8_t hue;
#endif