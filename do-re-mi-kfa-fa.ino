/* 
 * ########################################
 * ### Do Re Mi Kfa-Fa                  ###
 * ### Musical glove by ailaG           ###
 * ### github.com/ailaG/do-re-mi-kfa-fa ###
 * ### Made & won in hack2wear 2014     ###
 * ########################################
 */

#include "pitches.h"

int max_piezo_inputs = 4;
int iPIEZO_PINS[] = {A0, A1, A2, A3};
//float iPIEZO_RANGE = 100;
int iPIEZO_THRESHOLD = 10;
int iPIEZO_THRESHOLDs[] = {50, 50, 50, 5} ;
int oPIEZO_PIN = 9;
int DIST_PIN = A5;
int interval = 100;
float outs1[] = {NOTE_C3, NOTE_E3, NOTE_G3, NOTE_C4};
float outs2[] = {NOTE_D3, NOTE_G3, NOTE_AS3, NOTE_D4};
//float outs1[] = {NOTE_C3, NOTE_E3, NOTE_C4};
//float outs2[] = {NOTE_D3, NOTE_G3, NOTE_D4};

boolean do_print = 1;

void setup() {
  if (do_print) {
   Serial.begin(9600); 
  }
} // setup

int tmpOut;
int tmpCount, outTone;

void loop() {
  tmpCount =0;
  outTone = 0;  
  for (int i=0; i<max_piezo_inputs; i++) {
    tmpOut = analogRead(iPIEZO_PINS[i]);
    if (do_print) {
      Serial.print(tmpOut);
      Serial.print(" dist=" );
      Serial.print(digitalRead(DIST_PIN));
      Serial.print(" ");
    }
    if (tmpOut < iPIEZO_THRESHOLD) {
      Serial.print("AA"); 
      if (digitalRead(DIST_PIN) == 1) {
        outTone += outs1[i];
      } else {
        outTone += outs2[i];
      }
      tmpCount++;
      if (do_print) {
        Serial.print(outTone);
      }
      //noTone(oPIEZO_PIN);
    } else {
      if (do_print) {
        Serial.print("--.--"); 
      }
    }
        
    if (do_print) {
      Serial.print(" OUT : ");
      Serial.print(outTone);
      Serial.print(" | ");
    }
  } // for loop
  
  if (outTone > 0) {
    tone(oPIEZO_PIN, outTone / tmpCount);
    delay(interval);
  } else {
    noTone(oPIEZO_PIN);
  }
  if (do_print) {
    Serial.println("");
  }
} // loop
