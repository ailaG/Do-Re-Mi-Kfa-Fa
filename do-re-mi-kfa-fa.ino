#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
/* 
 * ########################################
 * ### Do Re Mi Kfa-Fa                  ###
 * ### Musical glove by ailaG           ###
 * ### github.com/ailaG/do-re-mi-kfa-fa ###
 * ### Made & won in hack2wear 2014     ###
 * ########################################
 */


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
