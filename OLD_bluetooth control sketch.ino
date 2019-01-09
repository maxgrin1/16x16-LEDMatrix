//This is an old sketch, will upload the updated one(for example with brightness adjustments) when I get to it.

#include "FastLED.h"
//A bunch of variables
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
  Serial.begin(9600); // Needed in order to use Bluetooth(mobile app), and for debug info
  debugInfo();
}
//for the pallets from the fastled library
extern const TProgmemRGBGradientPalettePtr gGradientPalettes[];
extern const uint8_t gGradientPaletteCount;
uint8_t gCurrentPaletteNumber = 0;
CRGBPalette16 gCurrentPalette( CRGB::Black);
CRGBPalette16 gTargetPalette( gGradientPalettes[0] );


void loop(){
  //Check if there is data
  SerialCheck();
//if the loop gets here, we have data YEAHHHH
  if(state == 1){
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    SerialCheck();
  }
  while(state == 2){ 
  FastLED.clear(); //turn off all the LEDs
      EVERY_N_SECONDS( SECONDS_PER_PALETTE ) {
        gCurrentPaletteNumber = addmod8( gCurrentPaletteNumber, 1, gGradientPaletteCount);
        gTargetPalette = gGradientPalettes[ gCurrentPaletteNumber ];
      }

      EVERY_N_MILLISECONDS(40) {
        nblendPaletteTowardPalette( gCurrentPalette, gTargetPalette, 16);
      }
      colorwaves( leds, NUM_LEDS, gCurrentPalette);
      FastLED.show();
      //Here you can adjust the brightness
      SerialCheck();
  }
  if(state == 3){
    fill_solid(leds, NUM_LEDS, CRGB::Red);
    FastLED.show();
    SerialCheck();
  }
  if(state == 4){
    fill_solid(leds, NUM_LEDS, CRGB::Blue);
    FastLED.show();
    SerialCheck();
  }
  if(state == 8){ //Here comes brightness.
    
  }
}

//Check if there is Serial data comming from the Bluetooth Module, if so store that data in the state variable.
void SerialCheck(){
  if(Serial.available() > 0){
    state = Serial.read();
    Serial.println(state);
  }
}

void debugInfo(){
  Serial.println("Sketch made by Max van Grinsven");
  Serial.print("Sketch: ");
  Serial.println(__FILE__);
  Serial.print("Date: ");
  Serial.println(__DATE__);
}

