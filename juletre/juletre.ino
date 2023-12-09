/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-ws2812b-led-strip
 */

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif

#define PIN_LED_SIGNAL 4
#define NUM_PIXELS 20            // The number of LEDs (pixels) on WS2812B
#define PIN_CYCLE_INTERRUPT 13   // TODO: what pin?
#define PIN_MOTION_INTERRUPT 14  // TODO: what pin?

#define timeSeconds 1

bool motionDetected = false;
unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;

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

  // initXmas();
  attachInterrupt(digitalPinToInterrupt(PIN_CYCLE_INTERRUPT), cycleMode, FALLING);

  // PIR Motion Sensor mode INPUT_PULLUP
  pinMode(PIN_MOTION_INTERRUPT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_MOTION_INTERRUPT), detectsMovement, RISING);
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

ICACHE_RAM_ATTR void detectsMovement() {
  Serial.println("MOTION DETECTED!!!");
  startTimer = true;
  lastTrigger = millis();
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {         // for each pixel
    WS2812B.setPixelColor(pixel, WS2812B.Color(0, 255, 0));  // it only takes effect if pixels.show() is called
  }
  WS2812B.show();
  // if (xmasMode == MOTION) {
  //   Serial.println("MOTION DETECTED!!!");
  //   //digitalWrite(led, HIGH);
  //   // for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {         // for each pixel
  //   //   WS2812B.setPixelColor(pixel, WS2812B.Color(0, 255, 0));  // it only takes effect if pixels.show() is called
  //   // }
  //   // WS2812B.show();
  //   // startTimer = true;
  //   // lastTrigger = millis();
  // } else {
  //   Serial.println("No motion...");
  // }
}

ICACHE_RAM_ATTR void cycleMode() {
  Serial.println("Changing mode");
  xmasMode = (XmasMode)((xmasMode + 1) % 3);
  WS2812B.clear();
  WS2812B.show();

  // TODO: instantly run next thingy
}

void initXmas() {
  WS2812B.clear();  // set all pixel colors to 'off'. It only takes effect if pixels.show() is called

  // turn pixels to red one by one with delay between each pixel
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {         // for each pixel
    WS2812B.setPixelColor(pixel, WS2812B.Color(255, 0, 0));  // it only takes effect if pixels.show() is called
    WS2812B.show();                                          // send the updated pixel colors to the WS2812B hardware.

    delay(250);  // pause between each pixel
  }

  // turn off all pixels for two seconds
  WS2812B.clear();
  WS2812B.show();  // send the updated pixel colors to the WS2812B hardware.
  delay(2000);     // off time

  // turn on all pixels to green at the same time for two seconds
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {         // for each pixel
    WS2812B.setPixelColor(pixel, WS2812B.Color(0, 255, 0));  // it only takes effect if pixels.show() is called
  }
  WS2812B.show();  // send the updated pixel colors to the WS2812B hardware.
  delay(2000);     // on time

  // turn off all pixels for one seconds
  WS2812B.clear();
  WS2812B.show();  // send the updated pixel colors to the WS2812B hardware.
  delay(2000);     // off time
}