/*
  bluetoothScaleDisplay.ino - display weight or time from a bluetooth scale.

  Created by Tate Mazer, 2025.

  Released under the MIT license.

  https://github.com/tatemazer/IoT_PanelMeter

*/

#include <AcaiaArduinoBLE.h>
#include <math.h>

#define LED_RED     46
#define LED_BLUE    45
#define LED_GREEN   47
#define OUT         38
#define DEBUG       false
#define MAX_NEEDLE_PWM      255
#define MAX_WEIGHT_G 100

int RED[3] = {255, 0, 0};
int GREEN[3] = {0, 255, 0};
int BLUE[3] = {0, 0, 255};
int MAGENTA[3] = {255, 0, 255};
int CYAN[3] = {0, 255, 255};
int YELLOW[3] = {255, 255, 0};
int WHITE[3] = {255, 255, 255};
int OFF[3] = {0,0,0};

int needleVal = 0;  // current position
int currentColor[3] = {0,0,0};
AcaiaArduinoBLE scale(DEBUG);
float currentWeight = 0;

// the setup routine runs once when you press reset:
void setup() {

  Serial.begin(9600);


  // initialize the GPIO hardware
  pinMode(OUT, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  // initialize the BLE hardware
  BLE.begin();
}

// the loop routine runs over and over again forever:
void loop() {
   // Connect to scale
  while(!scale.isConnected()){

    setColor(RED);
    scale.init(); 
    if(scale.isConnected()){
      setColor(YELLOW);
    }
  }

  // Check for setpoint updates
  BLE.poll();

  // Send a heartbeat message to the scale periodically to maintain connection
  if(scale.heartbeatRequired()){
    scale.heartbeat();
  }

  // always call newWeightAvailable to actually receive the datapoint from the scale,
  // otherwise getWeight() will return stale data
  if(scale.newWeightAvailable()){
    currentWeight = scale.getWeight();
    Serial.println(currentWeight);
  }


  needleVal = constrain(currentWeight/MAX_WEIGHT_G * MAX_NEEDLE_PWM,0,MAX_NEEDLE_PWM);

  // set the val of pin 9:
  analogWrite(OUT, needleVal);

  currentColor[0] = max(int(needleVal),0);
  currentColor[1] = max(int(needleVal),0);
  currentColor[2] = max(int(needleVal),0);
  setColor(currentColor);


}

void setColor(int rgb[3]){
  analogWrite(LED_RED,   255-rgb[0] );
  analogWrite(LED_GREEN, 255-rgb[1] );
  analogWrite(LED_BLUE,  255-rgb[2] );
}