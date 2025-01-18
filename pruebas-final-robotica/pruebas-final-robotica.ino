#include "BluetoothSerial.h"          // libreria bluethooth
#include <ESP32Servo.h>               // libreria servo


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

int PINSERVO1 = 26;                    // pin control servo 1
int PULSOMIN = 550;                    // pulso minimo en milisegundos
int PULSOMAX = 2500;                   // pulso maximo en milisegundos
int PINSERVO2 = 33;                    // pin control servo 2
Servo servo1, servo2;                  // crea objetos servo1 y servo2

const int car = 22;                    // pin 19 relay de control municion
const int PWM = 18;                    // pin 18 velicidad giro motor

int g1 = 90;
int g2 = 90;
int vel = 0;
int vel2 = 0;
int vel3 = 0;
                        
BluetoothSerial SerialBT;                         // objeto bluetooth

void setup() {
  servo1.attach(PINSERVO1, PULSOMIN, PULSOMAX);   // configuro el servo
  servo2.attach(PINSERVO2, PULSOMIN, PULSOMAX); 
  servo1.write(g1);                               // ubica el servo en la dirección
  servo2.write(g2);                               // ubica el servo en la dirección
  
  Serial.begin(115200);
  
  pinMode(car, OUTPUT);                           // pin 19 relay de control municion
  pinMode(PWM, OUTPUT);                           // pin 18 salida controla el motor
  
  SerialBT.begin("cañon");                        // Bluetooth device name
  Serial.println("listo para conectar");
 
}

void loop() {
  if (SerialBT.available()) {
      char x = (char)SerialBT.read();
      if ( x == 'I')
      {
        g1 = g1+3;
        if (g1 >= 180){
          g1 = 180;
        }
        servo1.write(g1);              // ubica el servo en la dirección
        Serial.print(g1);
        Serial.print("\n");
        }
      if ( x == 'D')
      {
        g1 = g1-3;
        if (g1 <= 0){
          g1 = 0;
        }
        servo1.write(g1);              // ubica el servo en la dirección
        Serial.print(g1);
        Serial.print("\n");
        }
       if ( x == 'A')
      {
        g2 = g2+3;
        if (g2 >= 180){
          g2 = 180;
        }
        servo2.write(g2);              // ubica el servo en la dirección
        Serial.print(g2);
        Serial.print("\n");
        }
     if ( x == 'B')
      {
        g2 = g2-3;
        if (g2 <= 0){
          g2 = 0;
        }
        servo2.write(g2);              // ubica el servo en la dirección
        Serial.print(g2);
        Serial.print("\n");
        }
     if ( x == 'V')
      {
       if (vel == 0){
          vel = 100;
          vel2 = vel * 2.55;
          analogWrite(PWM, vel2);
          vel = 35;
          delay(500);
          }
        vel = vel+1;
        if (vel >= 100){
          vel = 100;
          }
          vel2 = vel * 2.55;
          Serial.print(vel);
          Serial.print("\n");
        }
     if ( x == 'v')
      {
        if (vel <= 36 ){
          vel = 1;
          }
        vel = vel-1;
        if (vel <= 0){
          vel = 0;
          }
          vel2 = vel * 2.55;
          Serial.print(vel);
          Serial.print("\n");
        }
      
     if ( x == 'L')
      { 
        digitalWrite(car, LOW);
        delay(500);
        digitalWrite(car, HIGH);
        Serial.print("cargado"); // velocidad del motor que lanzara
        Serial.print("\n"); 
        }
     if ( vel <= 36)
      { 
         vel3 = 0;
        }else{
          vel3 = (vel - 36) * 1.6; 
          }

       SerialBT.print("*U");
       SerialBT.print(vel3);
       SerialBT.print("*");
       analogWrite(PWM, vel2);
       
      
  }
}
