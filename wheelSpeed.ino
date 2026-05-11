/**
Start of code for checking how fast a wheel is turning, using a magnetic sensor. 
*/
#include <Adafruit_NeoPixel.h>

#define DATA_PIN 3
#define NUM_LEDS 60
#define SENSOR_OUT 6  // SENSOR_OUT hooked up to the sensor output

unsigned long lastRotationTime = 0;
Adafruit_NeoPixel strip(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
  pinMode(SENSOR_OUT, INPUT_PULLUP);
  Serial.begin(9600);  // ← YOU NEED THIS LINE
}

void loop() {
  int sensorStatus = digitalRead(SENSOR_OUT);
  unsigned long currentTime = millis();
  if (sensorStatus == LOW) {
    unsigned long rotationTime = currentTime - lastRotationTime;  // get duration of last wheel rotation
    lastRotationTime = currentTime;                               // write current time to lastRotationTime
    /**
      5 mph = 5 miles/3600000 milliseconds = 316800 inches/3600000 milliseconds = 0.088 in/ms = 11.363 ms/in
      24.5*2*pi = ~ 153.938 inches circumference on a 700c tire  

      5 mph = 11.363 ms/in * 153.938 in = 1749.197 ms per rotation
      10 mph =  874.598 ms per rotations
      15 mph = 437.299 ms per rotation
      */

    if (rotationTime > 1749){ // 5 mph
      for (int i = 0; i < NUM_LEDS; i++) {
        strip.setPixelColor(i, strip.Color(0, 255, 0));  // Green
        }
      strip.show();
    }  
    else if (rotationTime > 875){ // 10 mph
      for (int i = 0; i < NUM_LEDS; i++) {
        strip.setPixelColor(i, strip.Color(255, 255, 0));  // Green
        }
      strip.show();
    }
    else { // faster than 10 mph
      for (int i = 0; i < NUM_LEDS; i++) {
        strip.setPixelColor(i, strip.Color(255, 0, 0));  // Green
        }
      strip.show();
    }
                        
  }
}
