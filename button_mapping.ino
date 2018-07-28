#include "Keyboard.h"

//DIGITAL PINOUT
#define UP        2
#define LEFT      3
#define DOWN      4
#define RIGHT     5
#define BUTTON_BLUE 6
#define BUTTON_RED 7
#define BACKSPACE 8
#define SPACE     9
#define LED_BLUE 10
#define LED_RED  11

const uint8_t key_up =  119;
const uint8_t key_left =  97;
const uint8_t  key_down =  115;
const uint8_t key_right=  100;
const uint8_t key_blue =  32;
const uint8_t key_red  =  99;

uint8_t up, left, down, right, button_blue, button_red, backspace, space;
unsigned long sysTime = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Keyboard.begin();
  for(uint8_t i = 2; i<=9; i++){
    pinMode(i, INPUT_PULLUP);
    Serial.print(i);
  }
  pinMode(BUTTON_BLUE, OUTPUT);
  pinMode(BUTTON_RED, OUTPUT);
}

void loop() {
  input();
  //buttonLights();
  if(!up)
    Keyboard.press(key_up);
  else
    Keyboard.release(key_up);
   
  if(!left)
    Keyboard.press(key_left);
  else
    Keyboard.release(key_left);
    
  if(!down)
    Keyboard.press(key_down);
  else
    Keyboard.release(key_down);
    
  if(!right)
    Keyboard.press(key_right);
  else
    Keyboard.release(key_right);
   
  if(!button_blue){
    Keyboard.press(key_blue);   //ESC
    digitalWrite(LED_BLUE, HIGH);
  }
  else{
    Keyboard.release(key_blue);
    digitalWrite(LED_BLUE, LOW);
  }
    
  if(!button_red){
    Keyboard.press(key_red);   //ENTER
    digitalWrite(LED_RED, HIGH);
  }
  else{
    Keyboard.release(key_red);
    digitalWrite(LED_RED, LOW);
  }
  
  if(!backspace)
    Keyboard.press(8);    //BACKSPACE
  else
    Keyboard.release(8);

  if(!space)
    Keyboard.press(32);   //SPACE
  else
    Keyboard.release(32);
}

void input(){
  up =        digitalRead(UP);
  left =      digitalRead(LEFT);
  down =      digitalRead(DOWN);
  right =     digitalRead(RIGHT);
  button_blue=digitalRead(BUTTON_BLUE);
  button_red =digitalRead(BUTTON_RED);
  backspace = digitalRead(BACKSPACE);
  space =     digitalRead(SPACE); 
}

void buttonLights(){
  if(!sysTime)
    sysTime = millis();
  
  if((millis() - sysTime) >= 500){
    digitalWrite(BUTTON_BLUE, HIGH);
    digitalWrite(BUTTON_RED, LOW);
    if(millis() - sysTime >= 1000){
      sysTime = 0;
    }
  }
  else{
    digitalWrite(BUTTON_BLUE, LOW);
    digitalWrite(BUTTON_RED, HIGH);
  }
}
