// Definitionfile for StatusLED
#ifndef StatusLED_H
    #define StatusLED_H
    #include <FastLED.h>
    //settings
    #define ANZAHL_LEDS 16
    #define LED_PIN 5
    #define LED_TYP WS2812B
    #define BRIGHTNESS 60
    #define FRAMES_PER_SECOND 30
    CRGB leds[ANZAHL_LEDS];

    uint8_t lbpm = 80;
    uint16_t sinusPlusInMilli = 1200/lbpm; //
    byte LEDGeschwindigkeit=5; // Wenn gröer 128 geht in andere richtung
    const byte maxByte = 255;
    byte sinus = 0;
#endif