#include "SD.h"
#define SD_ChipSelectPin 4
#include "TMRpcm.h"
#include "SPI.h"

char mychar;

/***************** PIR SENSOR *****************/
int led = 3;                // the pin that the LED is atteched to
int sensor = 2;              // the pin that the sensor is atteched to

/***************** Sound SENSOR *****************/
int SoundSensor = A0;
int clap = 0;
long detection_range_start = 0;
long detection_range = 0;
boolean status_lights = false;

TMRpcm tmrpcm;

void setup(){
    tmrpcm.speakerPin = 9;
    Serial.begin(9600);
    if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
    return;
    }

    tmrpcm.setVolume(5);

  ////////////////////////////
    pinMode(led, OUTPUT);      // initalize LED as an output
    pinMode(sensor, INPUT);    // initialize sensor as an input
    pinMode(SoundSensor, INPUT);
  ////////////////////////////

}
void blinke(int x)
    {
      for (int i = 0; i <= x; i++) {
        digitalWrite(led, HIGH);
        delay(120);
        digitalWrite(led, LOW);
        delay(120);
    }
  }
  
void Tone(){
tmrpcm.play("13.wav");
blinke(5); 
}

void loop(){

   if(Serial.available()){   
    mychar = Serial.read();

  if(mychar == 'a'){ 
      tmrpcm.play("1.wav");
      Serial.println("play wav.");
      
    }else if(mychar == 'b'){ 
      tmrpcm.play("2.wav"); 
    }
    else if(mychar == 'c'){ 
      tmrpcm.play("3.wav");
   }
   else if(mychar == 'd'){ 
      tmrpcm.play("4.wav");
blinke(4);
   }

////////////////////////////
int sensorValue = digitalRead(sensor);
  if (sensorValue == 1) {
    //Serial.println("human");
  }
////////////////////////////
int status_sensor = digitalRead(SoundSensor);
if (status_sensor == 0)
{
if (clap == 0)
{
detection_range_start = detection_range = millis();
clap++;
}
else if (clap > 0 && millis()-detection_range >= 50)
{
detection_range = millis();
clap++;
}
}
if (millis()-detection_range_start >= 400)
{
if (clap == 2)
{
if (!status_lights)
{
status_lights = true;
Tone();
}
else if (status_lights)
{
status_lights = false;
Tone2();
}
}
clap = 0;
}
////////////////////////////
}
