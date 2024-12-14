/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-ws2812b-led-strip
 */

#include <Adafruit_NeoPixel.h>
#include "pitches.h"
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif

#define PIN_LED_SIGNAL 4                // Board D2 physical pin
#define NUM_PIXELS 20                   // The number of LEDs (pixels) on WS2812B
#define PIN_CYCLE_INTERRUPT 13          // Board D5 physical pin
#define PIN_MOTION_INTERRUPT 14         // Board D7 physical pin
#define PIN_SECOND_BUTTON_INTERRUPT 15  // Board D8 physical pin
#define BUZZER_PIN 12                   // Board D6 physical pin

#define timeSeconds 1

bool motionDetected = false;
unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;
bool justReverse = true;

Adafruit_NeoPixel WS2812B(NUM_PIXELS, PIN_LED_SIGNAL, NEO_GRB + NEO_KHZ800);

enum XmasMode {
  OFF = 0,
  BLINK = 1,
  MOTION = 2
};

XmasMode xmasMode = MOTION;

void setup() {
  // Serial port for debugging purposes
  Serial.begin(9600);

  WS2812B.begin();  // INITIALIZE WS2812B strip object (REQUIRED)

  initXmas();
  attachInterrupt(digitalPinToInterrupt(PIN_CYCLE_INTERRUPT), cycleMode, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_SECOND_BUTTON_INTERRUPT), secondButton, FALLING);

  // PIR Motion Sensor mode INPUT_PULLUP
  pinMode(PIN_MOTION_INTERRUPT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_MOTION_INTERRUPT), detectsMovement, RISING);

  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  Serial.println("Looping...");

  // Current time
  now = millis();
  // Turn off the LED after the number of seconds defined in the timeSeconds variable
  if (startTimer && (now - lastTrigger > (timeSeconds * 1000))) {
    Serial.println("Motion stopped...");
    startTimer = false;
    for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {         // for each pixel
      WS2812B.setPixelColor(pixel, WS2812B.Color(255, 0, 0));  // it only takes effect if pixels.show() is called
    }

    WS2812B.show();
  }
  
  christmasBlink();
  

  // switch (xmasMode) {
  //   case BLINK:
  //     Serial.println("In blink mode");
  //     // runBlink();
  //     break;
  //   case MOTION:
  //     Serial.println("In motion mode");
  //     // Current time
  //     // now = millis();
  //     // Turn off the LED after the number of seconds defined in the timeSeconds variable
  //     // if (startTimer && (now - lastTrigger > (timeSeconds * 1000))) {
  //     //   Serial.println("Motion stopped...");
  //     //   digitalWrite(led, LOW);
  //     //   startTimer = false;
  //     // }
  //     // TODO
  //     break;
  //   case OFF:
  //   default:
  //     Serial.println("off mode");
  //     // WS2812B.clear();
  //     break;
  // }

  // delay(1000);
}









