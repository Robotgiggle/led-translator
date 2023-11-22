#include <FastLED.h>

#define LED_PIN 2
#define NUM_LEDS 60

CRGB leds[NUM_LEDS];
void sendToLeds(const CRGB* inArray, CRGB* outArray);
void debugLedShow(const CRGB* array);

void setup() {
  //FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(9600);

  CRGB drawArray[60] = {
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x123456, 0x444444, 0x000000, 0x000000,
    0x000000, 0x444444, 0x000000, 0x000000, 0x444444, 0x000000,
    0x444444, 0x000000, 0x000000, 0x000000, 0x000000, 0x444444,
    0x444444, 0x000000, 0x000000, 0x000000, 0x000000, 0x444444,
    0x000000, 0x444444, 0x000000, 0x000000, 0x444444, 0x000000,
    0x000000, 0x444444, 0x000000, 0x000000, 0x444444, 0x000000,
    0x000000, 0x000000, 0x444444, 0x444444, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
  };

  sendToLeds(drawArray,leds);

  debugLedShow(leds);
  //FastLED.show();
}

void loop() {
  
}

// -------- < Additional Functions > --------

// fills outArray with the contents of inArray, reordered for zigzag output
void sendToLeds(const CRGB* inArray, CRGB* outArray){
  for (int i = 0; i<10; i++){
    outArray[i] = inArray[6*i];
    outArray[19-i] = inArray[6*i + 1];
    outArray[20+i] = inArray[6*i + 2];
    outArray[39-i] = inArray[6*i + 3];
    outArray[40+i] = inArray[6*i + 4];
    outArray[59-i] = inArray[6*i + 5];
  }
}

// prints the output array into the serial monitor instead of displaying it on the LEDs
void debugLedShow(const CRGB* array){
  Serial.println("-----------");
  for (int i = 0; i<10; i++){
    char hexStr[9];
    sprintf(hexStr,"0x%02x%02x%02x ",array[i].r,array[i].g,array[i].b);
    Serial.print(hexStr);
    sprintf(hexStr,"0x%02x%02x%02x ",array[19-i].r,array[19-i].g,array[19-i].b);
    Serial.print(hexStr);
    sprintf(hexStr,"0x%02x%02x%02x ",array[20+i].r,array[20+i].g,array[20+i].b);
    Serial.print(hexStr);
    sprintf(hexStr,"0x%02x%02x%02x ",array[39-i].r,array[39-i].g,array[39-i].b);
    Serial.print(hexStr);
    sprintf(hexStr,"0x%02x%02x%02x ",array[40+i].r,array[40+i].g,array[40+i].b);
    Serial.print(hexStr);
    sprintf(hexStr,"0x%02x%02x%02x ",array[59-i].r,array[59-i].g,array[59-i].b);
    Serial.println(hexStr);
  }
  Serial.println("-----------");
}
