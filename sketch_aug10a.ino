#include "FastLED.h"
//'instellen' van Matrix
#define DATA_PIN    6
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    256
#define MAXBRIGHTNESS 150
CRGB leds[NUM_LEDS];
#define SECONDS_PER_PALETTE 15
int state = 0;
void setup() {
  delay(1000);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setDither(MAXBRIGHTNESS < 255);
  FastLED.setBrightness(MAXBRIGHTNESS);
  Serial.begin(9600); // Voor de communicatie met Bluetooth en debug
  debugInfo();
}
//Allemaal dingen voor de palletes
extern const TProgmemRGBGradientPalettePtr gGradientPalettes[];
extern const uint8_t gGradientPaletteCount;
uint8_t gCurrentPaletteNumber = 0;
CRGBPalette16 gCurrentPalette( CRGB::Black);
CRGBPalette16 gTargetPalette( gGradientPalettes[0] );


void loop(){
  //Check of er data is doorgegeven
  SerialCheck();
//Als de loop hier komt heeft hij data(YEAAHHS),
  while(state == 1){
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    SerialCheck();
  }
  while(state == 2){
  FastLED.clear(); //Zet alle leds uit anders kan je rare mixen gaan krijgen.
      EVERY_N_SECONDS( SECONDS_PER_PALETTE ) {
        gCurrentPaletteNumber = addmod8( gCurrentPaletteNumber, 1, gGradientPaletteCount);
        gTargetPalette = gGradientPalettes[ gCurrentPaletteNumber ];
      }

      EVERY_N_MILLISECONDS(40) {
        nblendPaletteTowardPalette( gCurrentPalette, gTargetPalette, 16);
      }
      colorwaves( leds, NUM_LEDS, gCurrentPalette);
      FastLED.show();
      SerialCheck();
  }
  while(state == 3){
    fill_solid(leds, NUM_LEDS, CRGB::Red);
    FastLED.show();
    SerialCheck();
  }
  while(state == 4){
    fill_solid(leds, NUM_LEDS, CRGB::Blue);
    FastLED.show();
    SerialCheck();
  }
}


