

ICACHE_RAM_ATTR void detectsMovement() {
  Serial.println("MOTION DETECTED!!!");
  startTimer = true;
  lastTrigger = millis();
  // for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {         // for each pixel
  //   WS2812B.setPixelColor(pixel, WS2812B.Color(0, 255, 0));  // it only takes effect if pixels.show() is called
  // }
  // WS2812B.show();
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

ICACHE_RAM_ATTR void secondButton() {
  WS2812B.clear();
  WS2812B.show();
}