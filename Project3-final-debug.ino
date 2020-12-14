#include "MIDIUSB.h"
// Variables:
byte note0 = 0;
byte note1 = 1;            // The MIDI note value to be played
byte note2 = 2;
byte note3 = 3;
byte note4 = 4;

const int photocell1Pin = A0; 
const int photocell2Pin = A1; 
const int photocell3Pin = A2; 
const int photocell4Pin = A3; 

const int led1Pin = 5;
const int led2Pin = 4;
const int led3Pin = 3;
const int led4Pin = 2;
const int buttonPin = 6;

const int vid1time = 67000;
const int vid2time = 66000;
const int vid3time = 70000;
const int vid4time = 66000;
 
int led1Brightness;
int led2Brightness;
int led3Brightness;
int led4Brightness;

int photocell1Reading;
int photocell2Reading;
int photocell3Reading;
int photocell4Reading;
int button;

const int pcThreshold = 1005;
unsigned long switchoff = 0;

bool playing = false;

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void setup() {
  Serial.begin(9600);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT); 
  pinMode(led3Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);
  pinMode(photocell1Pin, INPUT);
  pinMode(photocell2Pin, INPUT);
  pinMode(photocell3Pin, INPUT);
  pinMode(photocell4Pin, INPUT);
  pinMode(buttonPin, INPUT);
}
 
void loop() {
  photocell1Reading = analogRead(photocell1Pin);
  photocell2Reading = analogRead(photocell2Pin);
  photocell3Reading = analogRead(photocell3Pin);
  photocell4Reading = analogRead(photocell4Pin);
//  button =  digitalRead(photocell4Pin);
 
  Serial.print("pc1: ");
  Serial.print(photocell1Reading);
  Serial.print("pc2: ");
  Serial.print(photocell2Reading);
  Serial.print("pc3: ");
  Serial.print(photocell3Reading);
  Serial.print("pc4: ");
  Serial.println(photocell4Reading);
  Serial.println(playing);

  //led

  //midi
  //room 1
  if (photocell1Reading > pcThreshold) {
    if (playing == false) {
    digitalWrite(led1Pin, HIGH); 
    noteOn(0, 1, 64); 
    switchoff = millis()+vid1time;
    playing = true;
    Serial.println("open 1");
    }
//    Serial.print("switch 1     ");
//    Serial.print(switchoff);
//    Serial.print("millis 1    ");
//    Serial.println(millis());
  }

    if (millis() > switchoff) {
      digitalWrite(led1Pin, LOW);
      if   (switchoff > 0 ) {
        noteOn(0, 0, 64); 
        switchoff = 0;
        playing = false;
      }
    }
     
  delay(10);

    //room2
    if (photocell2Reading > 970) {
        if (playing == false) {
        digitalWrite(led2Pin, HIGH); 
        noteOn(0, 2, 64); 
        switchoff = millis()+vid2time;
        playing = true;
        Serial.println("open 2");
        }
//        Serial.print("switch 2     ");
//        Serial.print(switchoff);
//        Serial.print("millis 2    ");
//        Serial.println(millis());
      }
    
        if (millis() > switchoff) {
          digitalWrite(led2Pin, LOW);
            if   (switchoff > 0 ) {
          noteOn(0, 0, 64); 
          switchoff = 0;
          playing = false;
          }
        }
      
  delay(10);

  //room3
  if (photocell3Reading > 930) {
      if (playing == false) {
      digitalWrite(led3Pin, HIGH); 
      noteOn(0, 3, 64); 
      switchoff = millis()+vid3time;
      playing = true;
      Serial.println("open 3");
      }
//      Serial.print("switch 3     ");
//      Serial.print(switchoff);
//      Serial.print("millis 3    ");
//      Serial.println(millis());
    }
  
      if (millis() > switchoff) {
        digitalWrite(led3Pin, LOW);
          if   (switchoff > 0 ) {
        noteOn(0, 0, 64); 
        switchoff = 0;
        playing = false;
          }
        }
    
    delay(10);

  //room4
  if (photocell4Reading > 960) {
    if (playing == false) {
      digitalWrite(led4Pin, HIGH); 
      noteOn(0, 4, 64); 
      switchoff = millis()+vid4time;  
      playing == true;  
      }
     } 
      
   if (millis() > switchoff) {
      digitalWrite(led4Pin, LOW);
        if   (switchoff > 0 ) {
      noteOn(0, 0, 64); 
      switchoff = 0;
      playing = false;
      }
   }
         
  delay(10);

//  //reset threshold
//  if (button) 
//  const int pcThreshold = 980;
//  
}
// psudo-code:
// mark photocell reading every 10 second
// if photocell > threshold && photocell reading > previou photo cell reading 
//    play


// while loop didn't work //

//  while(play){
//      if (photocellReading > 900
//      ){
//        noteOn(0, 50, 64);
//        delay(300);
//      } else {
//        play = false;
//        break;
//      }
//  }
//}

  
