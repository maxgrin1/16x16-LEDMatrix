#include "FastLED.h"
//'instellen' van Matrix
#define DATA_PIN    6
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    256
#define MAXBRIGHTNESS 150
CRGB leds[NUM_LEDS];
#define SECONDS_PER_PALETTE 15
int state = 0; //Geen idee waarom deze 0 moet zijn maar anders doet hij het niet.
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
//Als de loop hier komt heeft hij data(YEAAHHS).
  if(state == 1){
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    SerialCheck();
  }
  while(state == 2){ //Moet while zijn omdat het een animatie is dat moet blijven loopen
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
      //Hier kan ik de felheid aanpassen, heeft continu effect
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
  if(state == 8){ //Plaats voor de felheid.
    
  }
}

//Check de Serial of er data beschikbaar is, zoja sla deze op in de 'state' variable.
void SerialCheck(){
  if(Serial.available() > 0){
    state = Serial.read();
    Serial.println(state);
  }
}

void debugInfo(){
  Serial.println("Sketch gemaakt door Max");
  Serial.print("Sketch: ");
  Serial.println(__FILE__);
  Serial.print("Datum: ");
  Serial.println(__DATE__);
}

