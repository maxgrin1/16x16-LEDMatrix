

// This function draws color waves with an ever-changing,
// widely-varying set of parameters, using a color palette.
void colorwaves( CRGB* ledarray, uint16_t numleds, CRGBPalette16& palette) 
{
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;
 
  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 300, 1500);
  
  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5,9);
  uint16_t brightnesstheta16 = sPseudotime;
  
  for( uint16_t i = 0 ; i < numleds; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;
    uint16_t h16_128 = hue16 >> 7;
    if( h16_128 & 0x100) {
      hue8 = 255 - (h16_128 >> 1);
    } else {
      hue8 = h16_128 >> 1;
    }

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);
    
    uint8_t index = hue8;
    //index = triwave8( index);
    index = scale8( index, 240);

    CRGB newcolor = ColorFromPalette( palette, index, bri8);

    uint16_t pixelnumber = i;
    pixelnumber = (numleds-1) - pixelnumber;
    
    nblend( ledarray[pixelnumber], newcolor, 128);
  }
}

void palettetest( CRGB* ledarray, uint16_t numleds, const CRGBPalette16& gCurrentPalette)
{
  static uint8_t startindex = 0;
  startindex--;
  fill_palette( ledarray, numleds, startindex, (256 / NUM_LEDS) + 1, gCurrentPalette, 255, LINEARBLEND);
}





// Gradient Color Palette definitions for 33 different cpt-city color palettes.
//    956 bytes of PROGMEM for all of the palettes together,
//   +618 bytes of PROGMEM for gradient palette code (AVR).
//  1,494 bytes total for all 34 color palettes and associated code.

// Gradient palette "ib_jul01_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ing/xmas/tn/ib_jul01.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE( ib_jul01_gp ) {
    0, 194,  1,  1,
   94,   1, 29, 18,
  132,  57,131, 28,
  255, 113,  1,  1};

DEFINE_GRADIENT_PALETTE( girlcat_gp ) {
    0, 173,229, 51,
   73, 139,199, 45,
  140,  46,176, 37,
  204,   7, 88,  5,
  255,   0, 24,  0};

DEFINE_GRADIENT_PALETTE( bhw1_sunconure_gp ) {
    0,  20,223, 13,
  160, 232, 65,  1,
  252, 232,  5,  1,
  255, 232,  5,  1};

DEFINE_GRADIENT_PALETTE( bhw1_purplered_gp ) {
    0, 255,  0,  0,
  255, 107,  1,205};

DEFINE_GRADIENT_PALETTE( rainbow_gp ) {
    0, 126,  1,142,
   25, 171,  1, 26,
   48, 224,  9,  1,
   71, 237,138,  1,
   94,  52,173,  1,
  117,   1,201,  1,
  140,   1,211, 54,
  163,   1,124,168,
  186,   1,  8,149,
  209,  12,  1,151,
  232,  12,  1,151,
  255, 171,  1,190 };
  
DEFINE_GRADIENT_PALETTE( autumnrose_gp ) {
    0,  71,  3,  1,
   45, 128,  5,  2,
   84, 186, 11,  3,
  127, 215, 27,  8,
  153, 224, 69, 13,
  188, 229, 84,  6,
  226, 242,135, 17,
  255, 247,161, 79};

DEFINE_GRADIENT_PALETTE( aquamarinemermaid_gp ) {
    0,  23,  4, 32,
   63,  98, 31, 52,
  127, 224,138, 24,
  191,   7, 55,164,
  255,  23,  4, 32};
// Gradient palette "titannightfall_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/titannightfall.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( titannightfall_gp ) {
    0, 173, 72,109,
   28, 112, 33, 68,
   51,  72, 19, 67,
  127,   2,  1, 33,
  204,  72, 19, 67,
  229, 112, 33, 68,
  255, 173, 72,109};
// Gradient palette "ib33_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ing/general/tn/ib33.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE( ib33_gp ) {
    0, 112,  0,  7,
   12, 123,  0, 10,
   25, 133,  0, 14,
   35,  51,  0,  1,
  124, 215,  0, 23,
  201,  68,  0, 10,
  209, 232,  0, 48,
  255,  35,  0,  1};
// Gradient palette "ib_jul22_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ing/xmas/tn/ib_jul22.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE( ib_jul22_gp ) {
    0, 255,  3,  1,
   69, 247, 55, 31,
   99, 237,184,153,
  140,   6, 33,  1,
  146,  12, 42,  1,
  163,  21, 54,  1,
  234,  14, 36,  1,
  255,  14, 36,  1};
// Gradient palette "German_flag_smooth_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ggr/tn/German_flag_smooth.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE( German_flag_smooth_gp ) {
    0,   0,  0,  0,
   63,  42,  0,  0,
  127, 255,  0,  0,
  191, 255, 55,  0,
  255, 255,255,  0};
// Gradient palette "bhw4_007_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw4/tn/bhw4_007.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw4_007_gp ) {
    0,  94, 82, 95,
   53, 171, 77, 37,
  124, 229, 37, 40,
  165, 217, 93, 35,
  255, 173,  6,  4};
// Gradient palette "bhw2_50_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_50.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw2_50_gp ) {
    0,   8,  2, 23,
   84,  47,  7,102,
  138,  16, 46,147,
  173,   2,127,203,
  255,   1,  7, 11};
// Gradient palette "bhw2_22_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_22.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw2_22_gp ) {
    0,   0,  0,  0,
   99, 227,  1,  1,
  130, 249,199, 95,
  155, 227,  1,  1,
  255,   0,  0,  0};
// Gradient palette "bhw3_02_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw3/tn/bhw3_02.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

// Gradient palette "bhw3_61_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw3/tn/bhw3_61.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw3_61_gp ) {
    0,  14,  1, 27,
   48,  17,  1, 88,
  104,   1, 88,156,
  160,   1, 54, 42,
  219,   9,235, 52,
  255, 139,235,233};
// Gradient palette "bhw3_32_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw3/tn/bhw3_32.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 52 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw3_32_gp ) {
    0, 234,231,  1,
   15, 171, 43,  6,
   40, 121,  0,  0,
   53,  95,  1, 29,
   71,  73,  1,168,
   94,  38, 63,221,
  109, 115, 51,221,
  127,  38, 63,221,
  147,  73,  1,168,
  181, 203, 28,  1,
  193, 155, 16, 11,
  216,  73,  1,168,
  255,   1,  4, 29};
// Gradient palette "bhw3_13_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw3/tn/bhw3_13.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw3_13_gp ) {
    0,   3,  6, 72,
   38,  12, 50,188,
  109, 217, 35,  1,
  135, 242,175, 12,
  178, 161, 32, 87,
  255,  24,  6,108};
// Gradient palette "bhw3_02_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw3/tn/bhw3_02.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw3_02_gp ) {
    0, 121,  1,  1,
   63, 255, 57,  1,
  112, 255, 79, 25,
  145, 255, 79, 25,
  188, 244,146,  3,
  255, 115, 14,  1};
// Gradient palette "bhw1_justducky_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_justducky.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw1_justducky_gp ) {
    0,  47, 28,  2,
   76, 229, 73,  1,
  163, 255,255,  0,
  255, 229, 73,  1};
// Gradient palette "bhw1_greeny_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_greeny.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw1_greeny_gp ) {
    0,   0,  0,  0,
   39,   7, 55,  8,
   99,  42,255, 45,
  153,   7, 55,  8,
  255,   0,  0,  0};
// Gradient palette "winter_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/h5/tn/winter.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 8 bytes of program space.

DEFINE_GRADIENT_PALETTE( winter_gp ) {
    0,   0,  0,255,
  255,   0,255, 44};
// Gradient palette "cool_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/h5/tn/cool.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 8 bytes of program space.

DEFINE_GRADIENT_PALETTE( cool_gp ) {
    0,   0,255,255,
  255, 255,  0,255};

const TProgmemRGBGradientPalettePtr gGradientPalettes[] = {
rainbow_gp,
bhw1_sunconure_gp,
bhw1_purplered_gp,
girlcat_gp,
titannightfall_gp,
ib33_gp,
ib_jul22_gp,
bhw4_007_gp,
bhw2_50_gp,
bhw2_22_gp,
bhw3_02_gp,
bhw3_61_gp,
bhw3_32_gp,
bhw3_13_gp,
bhw1_justducky_gp,
bhw1_greeny_gp,
winter_gp,
cool_gp
 };

const uint8_t gGradientPaletteCount = 
  sizeof( gGradientPalettes) / sizeof( TProgmemRGBGradientPalettePtr );
