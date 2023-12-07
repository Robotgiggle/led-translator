#include <FastLED.h>
#include "presets.h"

#define LED_PIN 7
#define NUM_LEDS 60

CRGB leds[NUM_LEDS];
CRGB colorBlobs[10][6];
int micInput = 43;
int scrambleCoordsToFloat(int x, int y);
void sendToLeds(const CRGB (&source)[10][6], CRGB (&leds)[60]);
void debugShow(const CRGB (&leds)[60]);

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);

  sendToLeds(ALL_OFF,leds);
  FastLED.show();
  delay(300);

  sendToLeds(LOGO,leds);
  FastLED.show();
  delay(1500);
}

void loop() {
  // generate array of randomized color blobs
  for (int i = 0; i<10; i++){
    for (int j = 0; j<6; j++){
      float baseHue = scrambleCoordsToFloat(j,i);
      float multiplier = scrambleCoordsToFloat(i,j)/20;
      int finalHue = baseHue+(multiplier*micInput);
      colorBlobs[i][j] = CHSV(finalHue,255,200);
    }
  }

  // display color blobs
  sendToLeds(colorBlobs,leds);
  FastLED.show();
  
  // increment input for randomizer
  micInput += 1;
  delay(10);
}

// -------- < Additional Functions > --------

// converts the X and Y coordinates of each LED into a float from 0 to 255, based on a relatively chaotic function
int scrambleCoordsToFloat(int x, int y){
  float a = sin(0.57*(x-1.5)) + cos(0.67*(y+1));
  float b = sin(0.93*(x-0.7)) + cos(0.45*(y+1));
  float c = sin(0.45*(x+1.3)) + cos(0.27*(y+3));
  float d = sin(0.25*(x-0.3)) + cos(0.95*(y+2));
  return 50*abs(a) + 60*abs(b) - 50*abs(c) + 40*abs(d) + 40;
}

// updates the LED array with the content of the provided source array, rearranged into the proper order
void sendToLeds(const CRGB (&source)[10][6], CRGB (&leds)[60]){
  for (int i = 0; i<10; i++){
    leds[i] = source[i][0];
    leds[19-i] = source[i][1];
    leds[20+i] = source[i][2];
    leds[39-i] = source[i][3];
    leds[40+i] = source[i][4];
    leds[59-i] = source[i][5];
  }
}

// prints the LED array into the serial monitor instead of displaying it on the actual LEDs
void debugShow(const CRGB (&leds)[60]){
  Serial.println("-----------");
  for (int i = 0; i<10; i++){
    char hexStr[9];
    sprintf(hexStr,"0x%02X%02X%02X ",leds[i].r,leds[i].g,leds[i].b);
    Serial.print(hexStr);
    sprintf(hexStr,"0x%02X%02X%02X ",leds[19-i].r,leds[19-i].g,leds[19-i].b);
    Serial.print(hexStr);
    sprintf(hexStr,"0x%02X%02X%02X ",leds[20+i].r,leds[20+i].g,leds[20+i].b);
    Serial.print(hexStr);
    sprintf(hexStr,"0x%02X%02X%02X ",leds[39-i].r,leds[39-i].g,leds[39-i].b);
    Serial.print(hexStr);
    sprintf(hexStr,"0x%02X%02X%02X ",leds[40+i].r,leds[40+i].g,leds[40+i].b);
    Serial.print(hexStr);
    sprintf(hexStr,"0x%02X%02X%02X ",leds[59-i].r,leds[59-i].g,leds[59-i].b);
    Serial.println(hexStr);
  }
  Serial.println("-----------");
}