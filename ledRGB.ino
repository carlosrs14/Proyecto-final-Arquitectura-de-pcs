/**
  ******************************************************************************
  * @file    vr_sample_control_led.ino
  * @author  JiapengLi
  * @brief   This file provides a demostration on 
              how to control led by using VoiceRecognitionModule
  ******************************************************************************
  * @note:
        voice control led
  ******************************************************************************
  * @section  HISTORY
    
    2013/06/13    Initial version.
  */
  
#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"

/**        
  Connection
  Arduino    VoiceRecognitionModule
   2   ------->     TX
   3   ------->     RX
*/
VR myVR(2,3);    // 2:RX 3:TX, you can choose your favourite pins.

uint8_t records[7]; // save record
uint8_t buf[64];

int r = 8, g = 9, b = 10;

#define rojo     (0)
#define azul     (1) 
#define verde    (2)
#define blanco   (3)
#define morado   (4)
#define amarillo (5)
#define naranja  (6)
#define apagado  (7)
/**
  @brief   Print signature, if the character is invisible, 
           print hexible value instead.
  @param   buf     --> command length
           len     --> number of parameters
*/
void printSignature(uint8_t *buf, int len)
{
  int i;
  for(i=0; i<len; i++){
    if(buf[i]>0x19 && buf[i]<0x7F){
      Serial.write(buf[i]);
    }
    else{
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}

/**
  @brief   Print signature, if the character is invisible, 
           print hexible value instead.
  @param   buf  -->  VR module return value when voice is recognized.
             buf[0]  -->  Group mode(FF: None Group, 0x8n: User, 0x0n:System
             buf[1]  -->  number of record which is recognized. 
             buf[2]  -->  Recognizer index(position) value of the recognized record.
             buf[3]  -->  Signature length
             buf[4]~buf[n] --> Signature
*/
void printVR(uint8_t *buf)
{
  Serial.println("VR Index\tGroup\tRecordNum\tSignature");

  Serial.print(buf[2], DEC);
  Serial.print("\t\t");

  if(buf[0] == 0xFF){
    Serial.print("NONE");
  }
  else if(buf[0]&0x80){
    Serial.print("UG ");
    Serial.print(buf[0]&(~0x80), DEC);
  }
  else{
    Serial.print("SG ");
    Serial.print(buf[0], DEC);
  }
  Serial.print("\t");

  Serial.print(buf[1], DEC);
  Serial.print("\t\t");
  if(buf[3]>0){
    printSignature(buf+4, buf[3]);
  }
  else{
    Serial.print("NONE");
  }
  Serial.println("\r\n");
}

void setup()
{
  /** initialize */
  myVR.begin(9600);
  
  Serial.begin(115200);
  Serial.println("Elechouse Voice Recognition V3 Module\r\nControl LED sample");
  
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
    
  if(myVR.clear() == 0){
    Serial.println("Recognizer cleared.");
  }else{
    Serial.println("Not find VoiceRecognitionModule.");
    Serial.println("Please check connection and restart Arduino.");
    while(1);
  }
  
  if(myVR.load((uint8_t)rojo) >= 0){
    Serial.println("rojo loaded");
  }
  if(myVR.load((uint8_t)azul) >= 0){
    Serial.println("azul loaded");
  }
  if(myVR.load((uint8_t)verde) >= 0){
    Serial.println("verde loaded");
  }
  if(myVR.load((uint8_t)blanco) >= 0){
    Serial.println("blanco loaded");
  }
  if(myVR.load((uint8_t)morado) >= 0){
    Serial.println("morado loaded");
  }
  if(myVR.load((uint8_t)amarillo) >= 0){
    Serial.println("amarillo loaded");
  }
  if(myVR.load((uint8_t)naranja) >= 0){
    Serial.println("naranja loaded");
  }
  if(myVR.load((uint8_t)apagado) >= 0){
    Serial.println("apagado loaded");
  }
}

void loop()
{
   
  int ret;
  ret = myVR.recognize(buf, 50);
  if(ret>0){
    switch(buf[1]){
      case rojo:
        analogWrite(r, 0);
        analogWrite(g, 255);
        analogWrite(b, 255);
        break;
      
      case azul:
        analogWrite(r, 255);
        analogWrite(g, 255);
        analogWrite(b, 0);
        break;
      
      case verde:
        analogWrite(r, 255);
        analogWrite(g, 0);
        analogWrite(b, 255);
        break;
      
      case blanco:
        analogWrite(r, 0);
        analogWrite(g, 100);
        analogWrite(b, 10);
        break;
        
      case morado:
        analogWrite(r, 0);
        analogWrite(g, 255);
        analogWrite(b, 0);
        break;
        
      case amarillo:
        analogWrite(r, 0);
        analogWrite(g, 200);
        analogWrite(b, 255);
        break;

      case naranja:
        analogWrite(r, 0);
        analogWrite(g, 240);
        analogWrite(b, 255);
        break;
        
      case apagado:
        analogWrite(r, 255);
        analogWrite(g, 255);
        analogWrite(b, 255);
        break;
        
      default:
        Serial.println("Record function undefined");
        break;
    }
    /** voice recognized */
    printVR(buf);
  }
  
}
