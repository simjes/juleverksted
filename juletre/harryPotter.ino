// Harry potter music and lights.


// Lighting sequence. Called inside harryPotter() after each note.
void hogwarts() {
  int evenBlue = 0;
  int oddBlue = 0;

  if (justReverse) {
    evenBlue = 150;
    oddBlue = 0;
  }
  else {
    evenBlue = 0;
    oddBlue = 150;
  }

  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
    if (pixel % 2 == 0){
      WS2812B.setPixelColor(pixel, WS2812B.Color(255, evenBlue, 0));
    }
    else{
      WS2812B.setPixelColor(pixel, WS2812B.Color(255, oddBlue, 0));
    }
  }
  WS2812B.show();

  justReverse = !justReverse;
}


// Playing music with buzzer.
void harryPotter(){
  int melody[] = {
    REST, NOTE_D4,
    NOTE_G4, NOTE_AS4, NOTE_A4,
    NOTE_G4, NOTE_D5,
    NOTE_C5, 
    NOTE_A4,
    NOTE_G4, NOTE_AS4, NOTE_A4,
    NOTE_F4, NOTE_GS4,
    NOTE_D4, 
    NOTE_D4,
    
    NOTE_G4, NOTE_AS4, NOTE_A4,
    NOTE_G4, NOTE_D5,
    NOTE_F5, NOTE_E5,
    NOTE_DS5, NOTE_B4,
    NOTE_DS5, NOTE_D5, NOTE_CS5,
    NOTE_CS4, NOTE_B4,
    NOTE_G4,
    NOTE_AS4,
    
    NOTE_D5, NOTE_AS4,
    NOTE_D5, NOTE_AS4,
    NOTE_DS5, NOTE_D5,
    NOTE_CS5, NOTE_A4,
    NOTE_AS4, NOTE_D5, NOTE_CS5,
    NOTE_CS4, NOTE_D4,
    NOTE_D5, 
    REST, NOTE_AS4,  
    
    NOTE_D5, NOTE_AS4,
    NOTE_D5, NOTE_AS4,
    NOTE_F5, NOTE_E5,
    NOTE_DS5, NOTE_B4,
    NOTE_DS5, NOTE_D5, NOTE_CS5,
    NOTE_CS4, NOTE_AS4,
    NOTE_G4
  };

  int durations[] = {
    2, 4,
    4, 8, 4,
    2, 4,
    2, 
    2,
    4, 8, 4,
    2, 4,
    1, 
    4,
    
    4, 8, 4,
    2, 4,
    2, 4,
    2, 4,
    4, 8, 4,
    2, 4,
    1,
    4,
    
    2, 4,
    2, 4,
    2, 4,
    2, 4,
    4, 8, 4,
    2, 4,
    1, 
    4, 4,  
    
    2, 4,
    2, 4,
    2, 4,
    2, 4,
    4, 8, 4,
    2, 4,
    1
  };

  int size = sizeof(durations) / sizeof(int);
  int pixel = 0;

  hogwarts();

  for (int note = 0; note < size; note++) {
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 1000 / durations[note];
    tone(BUZZER_PIN, melody[note], duration);

    // WS2812B.setPixelColor(pixel, WS2812B.Color(0, 255, 0));
    // WS2812B.show();
    // pixel += 1;
    
    hogwarts();
    
    //to distinguish the notes, set a minimum time between them.
    //the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    
    //stop the tone playing:
    noTone(BUZZER_PIN);
  }
}
