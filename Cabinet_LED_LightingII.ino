#include "Notes.h"

int ledPin = 9;
int ledState = 0;
long ledPreviousTime = 0;
unsigned long ledCurrentTime;
long ledInterval = 5000;

int speakerPin=6;
int speakerState = 0;
long speakerPreviousTime = 0;
unsigned long speakerCurrentTime;
long speakerInterval = 100;
int currentNote=0;           

int melody[] = {F5,0,F5,0,F5,0,D5,F5,0,F5,0,D5,F5,D5,F5,0,E5,0,E5,0,E5,0,C5,E5,0,E5,0,C5,E5,C5,E5,0};

void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(6,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  randomSeed(analogRead(A3));
}

void loop()
{

  Serial.println(analogRead(A0));
  if(  analogRead(A0) < 515 &&  analogRead(A1) > 1011)
  {
    LightAndSoundOn();
  }
  else
  {
    LightAndSoundOff();
  }

}

void LightAndSoundOn()
{

  ledCurrentTime = millis();
  speakerCurrentTime = millis();
  
  if(ledCurrentTime - ledPreviousTime > ledInterval) 
  {
    ledPreviousTime = ledCurrentTime;   
    ledState = !ledState;  
    digitalWrite(ledPin, ledState);
    ledPin++;
    if (ledPin==12){ledPin=9;}
  }

  if (speakerCurrentTime - speakerPreviousTime >= speakerInterval) 
  {
  speakerPreviousTime = speakerCurrentTime;    
  noTone(speakerPin);
  if (melody[currentNote]>0) {tone(speakerPin, melody[currentNote]);}
  currentNote++;
  if (currentNote==32) {currentNote=0;}
  }

}

void LightAndSoundOff()
{
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  noTone(speakerPin);  
}

