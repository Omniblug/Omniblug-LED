/*
     ---------------------------------------------
      OMNIBLUG - Control 
      WWW.OMNIBLUG.COM - info@omniblug.com
      V02R00
      Juan Manuel Hernández Ramírez
     ---------------------------------------------
    */
     
    //library
  #include <EEPROM.h>
  #include "DHT.h"
  
  //RGB1
    const byte RGB_R1 = 10; 
    const byte RGB_G1 = 11; 
    const byte RGB_B1 = 9; 
  
  //RGB2
    const byte RGB_R2 = 5; 
    const byte RGB_G2 = 6; 
    const byte RGB_B2 = 3;  
  
  //Switch
    byte sw[4] = {4, 7, 8, 12}; //pins

  //Sensor
    #define DHTPIN 13
    #define DHTTYPE DHT11 
    DHT dht(DHTPIN, DHTTYPE);
    long previousMillis = 0;        
    long intervalOff = 60000;      
  
  //Bluetooth
	  byte bluetooth = 2; //pin
	  int pinDefecto = 1234;
	
    byte red;
    byte green;
    byte blue;
    byte RGB1_red;
    byte RGB1_green;
    byte RGB1_blue;
    byte RGB2_red;
    byte RGB2_green;
    byte RGB2_blue;
    byte accion=0;
    byte puerto=0;
    
     
    void setup() 
    {
      pinMode(bluetooth,OUTPUT); 
      digitalWrite(bluetooth,HIGH);
      
      Serial.begin(9600);
      dht.begin();

      for(byte i=0;i<4;i++){
        byte indice = sw[i];
        pinMode(indice,OUTPUT);
        digitalWrite(indice, EEPROM.read(i+7));
      }

      puerto=1;
      color(EEPROM.read(1),EEPROM.read(2),EEPROM.read(3));
      puerto=2;
      color(EEPROM.read(4),EEPROM.read(5),EEPROM.read(6));

      //primera vez
      if(EEPROM.read(0)!=1){
        color(0,255,255);
        programer(pinDefecto);
        EEPROM.write(0,1);
        color(255,0,255);
      }
     delay(100);
    }
     
    void loop() 
    {      
          unsigned long currentMillis = millis();
              
          while (Serial.available() > 0) {
            accion = Serial.parseInt();
            
            if(accion == 1){
              puerto = Serial.parseInt();
              red = Serial.parseInt();
              green = Serial.parseInt();
              blue = Serial.parseInt();
              if (Serial.read() == '\n') {
                color(red,green,blue);
              }
            } else if(accion == 2){      
            				  byte option = Serial.parseInt();
            				  byte status = Serial.parseInt();
            				  if (Serial.read() == '\n') {
            					  changeSW(option,status);
            				  }
          				 } else if(accion == 4){
                						  if (Serial.read() == '\n') {
                  							EEPROM.write(1,RGB1_red);
                  							EEPROM.write(2,RGB1_green);
                  							EEPROM.write(3,RGB1_blue);
                  							EEPROM.write(4,RGB2_red);
                  							EEPROM.write(5,RGB2_green);
                  							EEPROM.write(6,RGB2_blue);
                						  }					
                					 } else if(accion==5){
                      								if(Serial.read() == '\n'){
                      									  sendStatus();
                      								}
                    							} else if(accion == 3){
                        									  byte pin = Serial.parseInt();
                        									  if (Serial.read() == '\n') {
                          										color(255,0,0);
                          										programer(pin);
                          										accion=0;
                          										color(0,255,0);
                        									  }     
                    									  }
          }
                 
        if(currentMillis - previousMillis > intervalOff) {
            previousMillis = currentMillis;   
            sendDataSensor();
        } 
    }
    
    void programer(int pin){
        digitalWrite(bluetooth,LOW);
        delay(250);
        digitalWrite(bluetooth,HIGH);
        delay(5000);
        Serial.print("AT");
        delay(1000);
        Serial.print("AT+NAMEOMNIBLUG");
        delay(1000);
        Serial.print("AT+PIN"+pin);
        delay(1000);
        digitalWrite(bluetooth,LOW);
        delay(250);
        digitalWrite(bluetooth,HIGH);
    } 
     
    void color(byte rojo, byte verde, byte azul){    
        if(puerto==1){
          analogWrite(RGB_R1, rojo);
          analogWrite(RGB_G1, verde);
          analogWrite(RGB_B1, azul);
          RGB1_red=rojo;
          RGB1_green=verde;
          RGB1_blue=azul;
        }
        if(puerto==2){
          analogWrite(RGB_R2, rojo);
          analogWrite(RGB_G2, verde);
          analogWrite(RGB_B2, azul);
          RGB2_red=rojo;
          RGB2_green=verde;
          RGB2_blue=azul;
        }
    }
  
    int changeSW(int option, int status){
      if(status==HIGH){
         //off
        digitalWrite(sw[option], HIGH);  
        EEPROM.write(option+7,HIGH); 
      }else{
        //on
        digitalWrite(sw[option], LOW);
        EEPROM.write(option+7,LOW);
      }
    }

    void sendDataSensor(){
        float h = dht.readHumidity();
        float t = dht.readTemperature();
        char aux[10];
        String temperatura;
        String humedad;           
        dtostrf(t,1,2,aux);
        temperatura = String(aux);
        dtostrf(h,1,2,aux);
        humedad = String(aux);    
        String json = "{\"datos\":["+temperatura+","+humedad+"],\"type\":2}";
        Serial.println(json);
     }

      void sendStatus(){
          sendDataSensor();
          char jsonStatus[64];
          sprintf(jsonStatus,"{\"type\":%d,\"rgb1\":[%d,%d,%d],\"rgb2\":[%d,%d,%d],\"sw\":[%d,%d,%d,%d]}",1,RGB1_red,RGB1_green,RGB1_blue,RGB2_red,RGB2_green,RGB2_blue,EEPROM.read(7),EEPROM.read(8),EEPROM.read(9),EEPROM.read(10));
          Serial.println(jsonStatus);
      }
     
    //Fin

