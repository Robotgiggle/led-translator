#include <FastLED.h>
#include "presets.h"

#define LED_PIN 2
#define NUM_LEDS 60

CRGB leds[NUM_LEDS];
int scrambleCoordsToFloat(int x, int y);
void sendToLeds(const CRGB (&source)[10][6], CRGB (&leds)[60]);
void debugShow(const CRGB (&leds)[60]);

void setup() {
  //FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);

  int micInput = 43; // once we get the microphone set up, this will be the loudness (or maybe pitch) from it

  CRGB colorBlobs[10][6];
  for (int i = 0; i<10; i++){
    for (int j = 0; j<6; j++){
      float baseHue = scrambleCoordsToFloat(j,i);
      float multiplier = scrambleCoordsToFloat(i,j)/20;
      int finalHue = baseHue+(multiplier*micInput);
      colorBlobs[i][j] = CHSV(finalHue,255,200);
    }
  }

  sendToLeds(colorBlobs,leds);

  debugShow(leds);
  //FastLED.show();
}

void loop() {
  
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
