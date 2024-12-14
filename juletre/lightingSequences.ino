// Colors in hex
int blue = 0x0000FF;
int green = 0x00FF00;
int yellow = 0xFF9600;
int orange = 0xCC5500;
int red = 0xFF0000;
int violet = 0x7F00FF;


void initXmas() {
  int red = 240;
  int green = 0;
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {                    // for each pixel
    WS2812B.setPixelColor(pixel, WS2812B.Color(red, green, 0));         // it only takes effect if pixels.show() is called

    for (int copyPixel = pixel; copyPixel >= 0; copyPixel--){           // changes the color on the previous pixels
      WS2812B.setPixelColor(copyPixel, WS2812B.Color(red, green, 0));
    }

    WS2812B.show();                                                     // send the updated pixel colors to the WS2812B hardware.

    red -= 12;
    green += 12;

    delay(250);       // pause between each pixel
  }

  delay(2000);

  WS2812B.clear();
  WS2812B.show();     // send the updated pixel colors to the WS2812B hardware.
  delay(2000);        // off time
}

void christmasBlink(){
  int colorArray[] = { blue, green, yellow, orange, red, violet };

  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
    WS2812B.setPixelColor(pixel, colorArray[random(6)]);
  }
  WS2812B.show();

  for (int pixel = 0; pixel < 100; pixel++) {
    for(int i=0; i<6; i++){
      WS2812B.setPixelColor(random(0, 20), colorArray[random(6)]);
    }
    
    WS2812B.show();
    delay(650);
  }
}

void randomBlueAndRed() {
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
    WS2812B.setPixelColor(pixel, WS2812B.Color(random(0, 256), random(0, 256), 0));
  }
  WS2812B.show();

  for (int pixel = 0; pixel < 100; pixel++) {
    for(int i=0; i<6; i++){
      WS2812B.setPixelColor(random(0, 20), WS2812B.Color(random(0, 256), random(0, 256), 0));
    }
    
    WS2812B.show();
    delay(650);
  }
}