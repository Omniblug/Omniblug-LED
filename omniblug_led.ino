/*
     ---------------------------------------------
      OMNIBLUG - Control LED RGB 
      WWW.OMNIBLUG.COM - info@omniblug.com
      V01R00
     ---------------------------------------------
    */
     
    //librerias
   #include <EEPROM.h>
 
    int ledRojo = 10; 
    int ledVerde=11; 
    int ledAzul=9;  
    int ledRojo2 = 5; 
    int ledVerde2=6; 
    int ledAzul2=3;  
    int red;
    int green;
    int blue;
    int accion=0;
    int bluetooth=2;
    int puerto=0;
    int primeraVez;
    int pinDefecto=1234;
    
     
    void setup() 
    {
      pinMode(bluetooth,OUTPUT); 
      digitalWrite(bluetooth,HIGH);
      
      Serial.begin(9600);
      
      primeraVez=EEPROM.read(0);
      
      if(primeraVez!=1){
        color(0,255,255);
        programer(pinDefecto);
        EEPROM.write(0,1);
        color(255,0,255);
      }
    }
     
    void loop() 
    {          
      
      while (Serial.available() > 0) {
        
        accion = Serial.parseInt();

           if(accion==1){
              puerto=Serial.parseInt();
              red = Serial.parseInt();
              green = Serial.parseInt();
              blue = Serial.parseInt();
           }
           if (Serial.read() == '\n') {
               color(red,green,blue);
           }
      }
      if(accion==2){
              color(0,255,255);
              delay(500);
              color(255,0,255);
              delay(500);
              color(255,255,0);
              delay(500);
      }
      if(accion==3){
        int pin = Serial.parseInt();
        
        if (Serial.read() == '\n') {
          color(255,0,0);
          programer(pin);
          accion=0;
          color(0,255,0);
        }  
        
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
    
    
     
    void color(int rojo, int verde, int azul){
        
        if(puerto==1){
          analogWrite(ledRojo, rojo);
          analogWrite(ledVerde, verde);
          analogWrite(ledAzul, azul);
        }
        if(puerto==2){
          analogWrite(ledRojo2, rojo);
          analogWrite(ledVerde2, verde);
          analogWrite(ledAzul2, azul);
        }
        if(puerto==3){
          analogWrite(ledRojo, rojo);
          analogWrite(ledRojo2, rojo);
          analogWrite(ledVerde, verde);
          analogWrite(ledVerde2, verde);
          analogWrite(ledAzul, azul);
          analogWrite(ledAzul2, azul);
        
        }
        
    }
     
    //Fin
