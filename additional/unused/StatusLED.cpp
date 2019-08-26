/*
 StatusLED V1.0
*/
    // libary we are using
    
     #include "StatusLED.h"

//Funktionen
void LEDshow(){
    for(int whiteLed = 0; whiteLed < ANZAHL_LEDS; whiteLed = whiteLed + 1) {
      // Turn our current led on to white, then show the leds
      leds[whiteLed] = CRGB::White;

      // Show the leds (only one of which is set to white, from above)
      FastLED.show();

      // Wait a little bit
      delay(100);

      // Turn our current led back to black for the next loop around
      leds[whiteLed] = CRGB::Black;
   }
   FastLED.show();
}

void sinustest() {
  byte lHelligkeit;
  for (byte i = 0; i < ANZAHL_LEDS; i++) {
    lHelligkeit = sin8(sinus + i * ANZAHL_LEDS);
    //Serial.println(lHelligkeit);
    leds[i] = CHSV(0, 255, lHelligkeit);
  }
}

void fade()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, ANZAHL_LEDS, 50);
  byte pos = beatsin8( 30, 0, ANZAHL_LEDS-1 );
  leds[pos] = CHSV( 0, 255, 255);
}

void fade2()
{
  fadeToBlackBy( leds, ANZAHL_LEDS, 25);
  byte pos = (beat8(60)*ANZAHL_LEDS) / 255;
  leds[pos] = CHSV( 0, 255, 255);
}