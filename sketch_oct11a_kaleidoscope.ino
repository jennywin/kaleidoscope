#include "FastLED.h"

#define STRIP_A_PIN 11
#define NUM_LEDS_STRIP_A 17
CRGB leds_A[NUM_LEDS_STRIP_A];

#define STRIP_B_PIN 10
#define NUM_LEDS_STRIP_B 14
CRGB leds_B[NUM_LEDS_STRIP_B];

#define STRIP_C_PIN 8
#define NUM_LEDS_STRIP_C 12
CRGB leds_C[NUM_LEDS_STRIP_C];

#define STRIP_D_PIN 7
#define NUM_LEDS_STRIP_D 10
CRGB leds_D[NUM_LEDS_STRIP_D];

#define STRIP_E_PIN 9
#define NUM_LEDS_STRIP_E 9
CRGB leds_E[NUM_LEDS_STRIP_E];

#define STRIP_F_PIN 6
#define NUM_LEDS_STRIP_F 7
CRGB leds_F[NUM_LEDS_STRIP_F];

#define STRIP_G_PIN 5
#define NUM_LEDS_STRIP_G 6
CRGB leds_G[NUM_LEDS_STRIP_G];

#define STRIP_H_PIN 4
#define NUM_LEDS_STRIP_H 5
CRGB leds_H[NUM_LEDS_STRIP_H];

#define STRIP_I_PIN 3
#define NUM_LEDS_STRIP_I 4
CRGB leds_I[NUM_LEDS_STRIP_I];

#define STRIP_J_PIN 2
#define NUM_LEDS_STRIP_J 55
CRGB leds_J[NUM_LEDS_STRIP_J];

#define BRIGHTNESS          200
#define FRAMES_PER_SECOND  240
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

#define LED_TYPE WS2812

void setup() {
  FastLED.addLeds<LED_TYPE, STRIP_A_PIN>(leds_A, NUM_LEDS_STRIP_A);
  FastLED.addLeds<LED_TYPE, STRIP_B_PIN>(leds_B, NUM_LEDS_STRIP_B);
  FastLED.addLeds<LED_TYPE, STRIP_C_PIN>(leds_C, NUM_LEDS_STRIP_C);
  FastLED.addLeds<LED_TYPE, STRIP_D_PIN>(leds_D, NUM_LEDS_STRIP_D);
  FastLED.addLeds<LED_TYPE, STRIP_E_PIN>(leds_E, NUM_LEDS_STRIP_E);
  FastLED.addLeds<LED_TYPE, STRIP_F_PIN>(leds_F, NUM_LEDS_STRIP_F);
  FastLED.addLeds<LED_TYPE, STRIP_G_PIN>(leds_G, NUM_LEDS_STRIP_G);
  FastLED.addLeds<LED_TYPE, STRIP_H_PIN>(leds_H, NUM_LEDS_STRIP_H);
  FastLED.addLeds<LED_TYPE, STRIP_I_PIN>(leds_I, NUM_LEDS_STRIP_I);
  FastLED.addLeds<LED_TYPE, STRIP_J_PIN>(leds_J, NUM_LEDS_STRIP_J);
  FastLED.setBrightness(200);
}

void loop() {
    sinelon();
    juggle();
    // lightning();
    confetti();
    rainbow();
    bpm();
    FastLED.show();
    FastLED.delay(1000/FRAMES_PER_SECOND);
    EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds_A, NUM_LEDS_STRIP_A, 20);
  int pos_A = beatsin16( 13, 0, NUM_LEDS_STRIP_A-1 );
  leds_A[pos_A] += CHSV( gHue, 255, 192);

  // fadeToBlackBy( leds_B, NUM_LEDS_STRIP_B, 20);
  // int pos_B = beatsin16( 13, 0, NUM_LEDS_STRIP_B-1 );
  // leds_B[pos_B] += CHSV( gHue, 255, 192);

  fadeToBlackBy( leds_C, NUM_LEDS_STRIP_C, 20);
  int pos_C = beatsin16( 13, 0, NUM_LEDS_STRIP_C-1 );
  leds_C[pos_C] += CHSV( gHue, 255, 192);

  fadeToBlackBy( leds_H, NUM_LEDS_STRIP_H, 20);
  int pos_H = beatsin16( 13, 0, NUM_LEDS_STRIP_H-1 );
  leds_H[pos_H] += CHSV( gHue, 255, 192);
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds_J, NUM_LEDS_STRIP_J, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds_J[beatsin16( i+7, 0, NUM_LEDS_STRIP_J-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }

  fadeToBlackBy( leds_E, NUM_LEDS_STRIP_E, 20);
  byte dothue2 = 0;
  for( int i = 0; i < 8; i++) {
    leds_E[beatsin16( i+7, 0, NUM_LEDS_STRIP_E-1 )] |= CHSV(dothue2, 200, 255);
    dothue += 32;
  }
}

void lightning() {
  uint8_t frequency = 30;                                       // controls the interval between strikes
  uint8_t flashes = 7;                                          //the upper limit of flashes per strike
  unsigned int dimmer = 1;
  uint8_t ledstart;                                             // Starting location of a flash
  uint8_t ledlen;    
  ledstart = 0;                               // Determine starting location of flash
  ledlen = NUM_LEDS_STRIP_D;                        // Determine length of flash
  CRGB colors[2];
  colors[0] = CHSV(255, 0, 255);
  colors[1] = CHSV(random16(1, 255), 255, 255);
  
  for (int flashCounter = 0; flashCounter < random8(3,flashes); flashCounter++) {
    if(flashCounter == 0) dimmer = 5;                         // the brightness of the leader is scaled down by a factor of 5
    else dimmer = random8(1,3);                              // return strokes are brighter than the leader
    
    fill_solid(leds_D+ledstart,ledlen,colors[random8(0,2)]);
    FastLED.show();                       // Show a section of LED's
    delay(random8(4,10));                                     // each flash only lasts 4-10 milliseconds
    fill_solid(leds_D+ledstart,ledlen,CHSV(255,0,0));           // Clear the section of LED's
    FastLED.show();
    
    if (flashCounter == 0) delay (150);                       // longer delay until next flash after the leader
    
    delay(50+random8(100));                                   // shorter delay between strokes  
  }
}

void confetti()
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy(leds_D, NUM_LEDS_STRIP_D, 10);
  int pos = random16(NUM_LEDS_STRIP_D);
  leds_D[pos] += CHSV(gHue + random8(64), 200, 255);

  fadeToBlackBy(leds_G, NUM_LEDS_STRIP_G, 10);
  int pos1 = random16(NUM_LEDS_STRIP_G);
  leds_G[pos1] += CHSV(gHue + random8(64), 200, 255);
}

void rainbow()
{
  // FastLED's built-in rainbow generator
  fill_rainbow(leds_I, NUM_LEDS_STRIP_I, gHue, 7);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 130;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8(BeatsPerMinute, 130, 255);
  for (int i = 0; i < NUM_LEDS_STRIP_B; i++)
  { //9948
    leds_B[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
  }
  for (int i = 0; i < NUM_LEDS_STRIP_F; i++)
  { //9948
    leds_F[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
  }
}
