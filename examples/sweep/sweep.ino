/*
  sweep.ino - Basic example of moving the needle across its range

  Created by Tate Mazer, 2025.

  Released under the MIT license.

  https://github.com/tatemazer/IoT_PanelMeter

*/

#define LED_RED     46
#define LED_BLUE    45
#define LED_GREEN   47
#define OUT         38


int val = 0;  // current position
int fadeAmount = 5;  // position step
int currentColor[3] = {0,0,0};

// the setup routine runs once when you press reset:
void setup() {

  // initialize the GPIO hardware
  pinMode(OUT, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

}

// the loop routine runs over and over again forever:
void loop() {
  // set the val of pin 9:
  analogWrite(OUT, val);

  currentColor[0] = val;
  currentColor[1] = val;
  currentColor[2] = val;
  setColor(currentColor);
  

  // change the val for next time through the loop:
  val = val + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (val <= 0 || val >= 255) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}

void setColor(int rgb[3]){
  analogWrite(LED_RED,   255-rgb[0] );
  analogWrite(LED_GREEN, 255-rgb[1] );
  analogWrite(LED_BLUE,  255-rgb[2] );
}