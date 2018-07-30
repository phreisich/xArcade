/**
   This code maps digital inputs to keyboard keys and emulates a keyboard to the connected device.

   Created 28 07 2018
   By Philipp Reisich

   Modified 30 07 2018
   By Vincent Jeltsch

   Following https://www.arduino.cc/en/Reference/StyleGuide
*/

#include "Keyboard.h"

//DIGITAL PINOUT
const int PIN_UP = 2;
const int PIN_LEFT = 3;
const int PIN_DOWN = 4;
const int PIN_RIGHT = 5;
const int PIN_BUTTON_BLUE = 6;
const int PIN_BUTTON_RED = 7;
const int PIN_BACKSPACE = 8;
const int PIN_SPACE = 9;
const int PIN_BUTTON_BLUE_LED = 10;
const int PIN_BUTTON_RED_LED = 11;

const int KEY_UP =  119;
const int KEY_LEFT =  97;
const int  KEY_DOWN =  115;
const int KEY_RIGHT =  100;
const int KEY_ESC =  32;
const int KEY_ENTER  =  99;
const int KEY_BACKSPACE  =  8;
const int KEY_SPACE  =  32;

/**
 * State variables
 */
int up, left, down, right, button_blue, button_red, backspace, space;

unsigned long sysTime = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Keyboard.begin();
  for (int i = 2; i <= 9; i++) {
    pinMode(i, INPUT_PULLUP);
    Serial.print(i);
  }
  pinMode(PIN_BUTTON_BLUE, OUTPUT);
  pinMode(PIN_BUTTON_RED, OUTPUT);
}

void loop() {
  //Reading the input pins
  input();
  //buttonLights();
  if (!up)
    Keyboard.press(KEY_UP);
  else
    Keyboard.release(KEY_UP);

  if (!left)
    Keyboard.press(KEY_LEFT);
  else
    Keyboard.release(KEY_LEFT);

  if (!down)
    Keyboard.press(KEY_DOWN);
  else
    Keyboard.release(KEY_DOWN);

  if (!right)
    Keyboard.press(KEY_RIGHT);
  else
    Keyboard.release(KEY_RIGHT);

  if (!button_blue) {
    Keyboard.press(KEY_ESC);   //ESC
    digitalWrite(PIN_BUTTON_BLUE_LED, HIGH);
  }
  else {
    Keyboard.release(KEY_ESC);
    digitalWrite(PIN_BUTTON_BLUE_LED, LOW);
  }

  if (!button_red) {
    Keyboard.press(KEY_ENTER);   //ENTER
    digitalWrite(PIN_BUTTON_RED_LED, HIGH);
  }
  else {
    Keyboard.release(KEY_ENTER);
    digitalWrite(PIN_BUTTON_RED_LED, LOW);
  }

  if (!backspace)
    Keyboard.press(KEY_BACKSPACE);    //BACKSPACE
  else
    Keyboard.release(KEY_BACKSPACE);

  if (!space)
    Keyboard.press(KEY_SPACE);   //SPACE
  else
    Keyboard.release(KEY_SPACE);
}

void input() {
  up =        digitalRead(UP);
  left =      digitalRead(PIN_LEFT);
  down =      digitalRead(PIN_DOWN);
  right =     digitalRead(PIN_RIGHT);
  button_blue = digitalRead(PIN_BUTTON_BLUE);
  button_red = digitalRead(PIN_BUTTON_RED);
  backspace = digitalRead(PIN_BACKSPACE);
  space =     digitalRead(PIN_SPACE);
}

void buttonLights() {
  if (!sysTime)
    sysTime = millis();

  if ((millis() - sysTime) >= 500) {
    digitalWrite(PIN_BUTTON_BLUE, HIGH);
    digitalWrite(PIN_BUTTON_RED, LOW);
    if (millis() - sysTime >= 1000) {
      sysTime = 0;
    }
  }
  else {
    digitalWrite(PIN_BUTTON_BLUE, LOW);
    digitalWrite(PIN_BUTTON_RED, HIGH);
  }
}
