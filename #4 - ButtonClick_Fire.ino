#include <M5StickC.h>

// constants (won't change):
const int buttonPin = 37;     // the number of the pushbutton pin
const int ledPin =  10;       // the number of the LED pin
const int screenWidth = 80;   // LCD screen width
const int screenHeight = 160; // LCD screen height
int colour[128];              // Array to hold the colour palette

// variables (will change):
int buttonState = 0;          // variable for reading the pushbutton status
int fire[screenHeight][screenWidth]; //Array to hold the screen buffer

// setup code (to run once):
void setup() {
  // initialize the M5StickC object:  
  M5.begin();
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the button(A) pin as an input:
  pinMode(buttonPin, INPUT);

  // for loop that creates color palettes (black -> red then red -> yellow):
  for (int i = 0; i < 128; i++) {
    if (i < 64) {
      colour[i] = (int(i/2) * 0x001F);
    }
    else {
      colour[i] = 0xf800 + ((i - 64) * 0x20);
    }
  }
  // Clear the screen buffer
  for (int y = 0; y < screenHeight; y++) {
    for (int x = 0; x < screenWidth; x++) {
        fire[y][x] = 0;
    }
  }
}

// main code (runs repeatedly):
void loop() {
  // Randomise the bottom line of the screen buffer
  for (int x = 0; x < screenWidth; x++) {
    fire[screenHeight - 1][x] = (64 + random(64));
  }
  // Calculate the flame algorithm from the top down
  for (int y =0; y < (screenHeight - 1); y++) {
    for (int x = 0; x < screenWidth; x++) {
      fire[y][x] =
      ((fire[(y + 1) % screenHeight][(x - 1) % screenWidth]
      + fire[(y + 1) % screenHeight][(x) % screenWidth]
      + fire[(y + 1) % screenHeight][(x + 1) % screenWidth]
      + fire[(y + 2) % screenHeight][(x) % screenWidth])
      * 32) / 129;  // change values for different effects
    }               // second number must be just over 4x the first
  }
  // Update the screen
  for (int y =0; y < screenHeight; y++) {
    for (int x = 0; x < screenWidth; x++) {
      M5.Lcd.drawPixel(x, y, colour[(fire[y][x])]);
    }
  }
  
  // read the state of the button(A) value:
  buttonState = digitalRead(buttonPin);

  // check if button(A) is pressed (if it is, the buttonState is HIGH):
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    // turn the LCD screen black (no button press-default state):
    M5.Axp.ScreenBreath(0);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
    // turn the LCD screen red (on button press):
    M5.Axp.ScreenBreath(100);
  }
}
