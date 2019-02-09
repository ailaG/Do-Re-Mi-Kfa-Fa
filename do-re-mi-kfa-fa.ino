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

int SPEAKER_PIN = 9;
int FINGER_PINS[] = {A0, A1, A2, A3};
int LED_PINS[] = {13, 12, 11, 10};
int DISTANCE_PIN = A5; // optional, currently disabled in code!

float notes_regular[] = {NOTE_C3, NOTE_D3, NOTE_E3, NOTE_G3, NOTE_A4}; // Major pentatonic
float notes_special[] = {NOTE_C3, NOTE_DS3, NOTE_F3, NOTE_G4, NOTE_AS4}; // Minor pentatonic?

int num_fingers = 4;
int inputPiezoThreshold = 50;
int interval = 100;


void setup() {
  for (int i=0; i<num_fingers; i++) {
    pinMode(FINGER_PINS[i], INPUT);
    pinMode(LED_PINS[i], OUTPUT);
  }
  pinMode(SPEAKER_PIN, OUTPUT);
  pinMode(DISTANCE_PIN, INPUT);  // optional
    
  if (DEBUG) {
   Serial.begin(9600); 
  }
} // setup

int fingerReading; // What's the value we read for a finger?
int fingersCount; // How many fingers are down?
int accumulatingTone; // Accumulating output from all fingers (to calculate average)

void loop() {
  fingersCount = 0;
  accumulatingTone = 0;

  // Read fingers
  for (int i=0; i<num_fingers; i++) {
    fingerReading = analogRead(FINGER_PINS[i]);
    if (DEBUG) {
      Serial.print(" (");
      Serial.print(i);
      Serial.print(") value: ");
      Serial.print(fingerReading);
    }
    
    if (fingerReading < inputPiezoThreshold) {
      // Finger #i pressed!
      
      //if (digitalRead(DISTANCE_PIN) == HIGH) {   // optional
        accumulatingTone += notes_regular[i];
      //} else {
      //  accumulatingTone += notes_special[i];
      //}
      
      fingersCount++;
      digitalWrite(LED_PINS[i], HIGH);
      
      if (DEBUG) {
        Serial.print(" Pressed! ");
      }
    } else {
      // Not pressed hard enough
      digitalWrite(LED_PINS[i], LOW);
      if (DEBUG) {
        Serial.print(" --------- "); 
      }
    }
        
  } // per-finger loop


  // Play music!
  if (accumulatingTone > 0) {
    tone(SPEAKER_PIN, accumulatingTone / fingersCount);
  } else {
    noTone(SPEAKER_PIN);
  }
  delay(interval);

  
  if (DEBUG) {
    Serial.println("");
  }
} // loop
