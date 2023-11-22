#include <FastLED.h>
#include "templates.h"

#define LED_PIN 2
#define NUM_LEDS 60

CRGB leds[NUM_LEDS];
void sendToLeds(const CRGB (&source)[10][6], CRGB (&leds)[60]);
void debugShow(const CRGB (&leds)[60]);

void setup() {
  //FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);

  CRGB drawArray[10][6] = {
    {0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000},
    {0x000000, 0x000000, 0x111111, 0x222222, 0x000000, 0x000000},
    {0x000000, 0xEEEEEE, 0x000000, 0x000000, 0x333333, 0x000000},
    {0xDDDDDD, 0x000000, 0x000000, 0x000000, 0x000000, 0x444444},
    {0xCCCCCC, 0x000000, 0x000000, 0x000000, 0x000000, 0x555555},
    {0x000000, 0xBBBBBB, 0x000000, 0x000000, 0x666666, 0x000000},
    {0x000000, 0xAAAAAA, 0x000000, 0x000000, 0x777777, 0x000000},
    {0x000000, 0x000000, 0x999999, 0x888888, 0x000000, 0x000000},
    {0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000},
    {0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000},
  };

  sendToLeds(drawArray,leds);

  debugShow(leds);
  //FastLED.show();
}

void loop() {
  
}

// -------- < Additional Functions > --------

// updates the LED array with the content of the source array, rearranged into the proper order
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
