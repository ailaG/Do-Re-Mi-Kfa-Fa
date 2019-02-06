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

int num_fingers = 4;
int FINGER_PINS[] = {A0, A1, A2, A3};
int inputPiezoThreshold = 10;
int DISTANCE_PIN = A5;
int SPEAKER_PIN = 9;
float outs1[] = {NOTE_C3, NOTE_E3, NOTE_G3, NOTE_C4};
float outs2[] = {NOTE_D3, NOTE_G3, NOTE_AS3, NOTE_D4};

int interval = 100;


void setup() {
  if (DEBUG) {
   Serial.begin(9600); 
  }
} // setup

int tmpOut;
int tmpCount, outTone;

void loop() {
  tmpCount =0;
  outTone = 0;

  // Read fingers
  for (int i=0; i<num_fingers; i++) {
    tmpOut = analogRead(FINGER_PINS[i]);
    if (DEBUG) {
      Serial.print(tmpOut);
      Serial.print(" dist=" );
      Serial.print(digitalRead(DISTANCE_PIN));
      Serial.print(" ");
    }
    if (tmpOut < inputPiezoThreshold) {
      if (digitalRead(DISTANCE_PIN) == 1) {
        outTone += outs1[i];
      } else {
        outTone += outs2[i];
      }
      tmpCount++;
      if (DEBUG) {
        Serial.print(outTone);
      }
    } else {
      if (DEBUG) {
        Serial.print("--.--"); 
      }
    }
        
    if (DEBUG) {
      Serial.print(" OUT : ");
      Serial.print(outTone);
      Serial.print(" | ");
    }
  } // finger checking loop

  // Play music
  if (outTone > 0) {
    tone(SPEAKER_PIN, outTone / tmpCount);
    delay(interval);
  } else {
    noTone(SPEAKER_PIN);
  }
  if (DEBUG) {
    Serial.println("");
  }
} // loop
