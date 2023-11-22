#include <FastLED.h>
#include "templates.h"

#define LED_PIN 2
#define NUM_LEDS 60

CRGB leds[NUM_LEDS];
void sendToLeds(const CRGB (&inArray)[10][6], CRGB (&outArray)[60]);
void debugShow(const CRGB* array);

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

// fills outArray with the contents of inArray, reordered for zigzag output
void sendToLeds(const CRGB (&inArray)[10][6], CRGB (&outArray)[60]){
  for (int i = 0; i<10; i++){
    outArray[i] = inArray[i][0];
    outArray[19-i] = inArray[i][1];
    outArray[20+i] = inArray[i][2];
    outArray[39-i] = inArray[i][3];
    outArray[40+i] = inArray[i][4];
    outArray[59-i] = inArray[i][5];
  }
}

// prints the output array into the serial monitor instead of displaying it on the LEDs
void debugShow(const CRGB* array){
  Serial.println("-----------");
  for (int i = 0; i<10; i++){
    char hexStr[9];
    sprintf(hexStr,"0x%02X%02X%02X ",array[i].r,array[i].g,array[i].b);
    Serial.print(hexStr);
    sprintf(hexStr,"0x%02X%02X%02X ",array[19-i].r,array[19-i].g,array[19-i].b);
    Serial.print(hexStr);
    sprintf(hexStr,"0x%02X%02X%02X ",array[20+i].r,array[20+i].g,array[20+i].b);
    Serial.print(hexStr);
    sprintf(hexStr,"0x%02X%02X%02X ",array[39-i].r,array[39-i].g,array[39-i].b);
    Serial.print(hexStr);
    sprintf(hexStr,"0x%02X%02X%02X ",array[40+i].r,array[40+i].g,array[40+i].b);
    Serial.print(hexStr);
    sprintf(hexStr,"0x%02X%02X%02X ",array[59-i].r,array[59-i].g,array[59-i].b);
    Serial.println(hexStr);
  }
  Serial.println("-----------");
}
