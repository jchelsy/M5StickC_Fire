#include <M5StickC.h>

// constants (won't change):
const int buttonPin = 37;     // the number of the pushbutton pin
const int ledPin =  10;       // the number of the LED pin

// variables (will change):
int buttonState = 0;          // variable for reading the pushbutton status

void setup() {
  // initialize the M5StickC object:  
  M5.begin();
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the button(A) pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the state of the button(A) value:
  buttonState = digitalRead(buttonPin);

  // check if button(A) is pressed (if it is, the buttonState is HIGH):
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    // turn the LCD screen black (no button press-default state):
    M5.Lcd.fillScreen(BLACK);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
    // turn the LCD screen red (on button press):
    M5.Lcd.fillScreen(RED);
  }
}
