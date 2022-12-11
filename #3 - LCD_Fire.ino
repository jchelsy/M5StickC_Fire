#include <M5StickC.h>

const int screenWidth = 80;
const int screenHeight = 160;
int colour[128]; // Array to hold the colour palette
int fire[screenHeight][screenWidth]; //Array to hold the screen buffer

// setup code (to run once):
void setup() {
  M5.begin();

  // for loop that creates color palettes (black -> red then red -> yellow):
  for (int i = 0; i < 128; i++) {
    if (i < 64) {
      colour[i] = (int(i/2) * 0x800);
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
      * 64) / 257; // play with these values for different effects, second number must be just over 4 x the first
    }
  }
  
  // Update the screen
  for (int y =0; y < screenHeight; y++) {
    for (int x = 0; x < screenWidth; x++) {
      M5.Lcd.drawPixel(x, y, colour[(fire[y][x])]);
    }
  }
}
