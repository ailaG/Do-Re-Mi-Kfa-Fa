/* 
 * ########################################
 * ### Do Re Mi Kfa-Fa                  ###
 * ### Musical glove by ailaG           ###
 * ### github.com/ailaG/do-re-mi-kfa-fa ###
 * ### Made & won in hack2wear 2014     ###
 * ########################################
 */

#include "pitches.h"

bool DEBUG = true;

int FINGER_PINS[] = {A0, A1, A2, A3};
int LED_PINS[] = {13, 12, 11, 10};
int DISTANCE_PIN = A5;
int SPEAKER_PIN = 9;

float notes_regular[] = {NOTE_C3, NOTE_E3, NOTE_G3, NOTE_C4};
float notes_special[] = {NOTE_D3, NOTE_G3, NOTE_AS3, NOTE_D4};

int num_fingers = 4;
int inputPiezoThreshold = 500;
int interval = 100;


void setup() {
  for (int i=0; i<num_fingers; i++) {
    pinMode(FINGER_PINS[i], INPUT);
    pinMode(LED_PINS[i], OUTPUT);
  }
  pinMode(DISTANCE_PIN, INPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  
  if (DEBUG) {
   Serial.begin(9600); 
  }
} // setup

int tmpOut;
int tmpCount, outTone;

void loop() {
  tmpCount =0;
  tmpOut = 0;
  outTone = 0;

  // Read fingers
  for (int i=0; i<num_fingers; i++) {
    tmpOut = analogRead(FINGER_PINS[i]);
    if (DEBUG) {
      Serial.print(i);
      Serial.print(": ");
      Serial.print(tmpOut);
    }
    
    if (tmpOut > inputPiezoThreshold) {
      // Finger #i pressed!
      
      if (digitalRead(DISTANCE_PIN) == 1) {
        outTone += notes_regular[i];
      } else {
        outTone += notes_special[i];
      }
      
      tmpCount++;
      digitalWrite(LED_PINS[i], HIGH);
      
      if (DEBUG) {
        Serial.print(" Pressed! ");
        Serial.print(" outTone: ");
        Serial.print(outTone);
      }
    } else {
      // Not pressed hard enough
      digitalWrite(LED_PINS[i], LOW);
      if (DEBUG) {
        Serial.print(" --------- "); 
        Serial.print(" outTone: ");
        Serial.print(outTone);
      }
    }
        
  } // per-finger loop


  // Play music!
  if (outTone > 0) {
    tone(SPEAKER_PIN, outTone / tmpCount);
    delay(interval);
    if (DEBUG) {
      Serial.print(" TOTAL OUT : ");
      Serial.print(outTone);
    }
  } else {
    noTone(SPEAKER_PIN);
  }
  if (DEBUG) {
    Serial.println("");
  }
} // loop
