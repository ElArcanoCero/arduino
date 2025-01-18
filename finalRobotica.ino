#include "BluetoothSerial.h"          // libreria bluethooth
#include <ESP32Servo.h>               // libreria servo

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

int PINSERVO1 = 26;                    // pin control servo 1
int PULSOMIN = 550;                    // pulso minimo en milisegundos
int PULSOMAX = 2500;                   // pulso maximo en milisegundos
int PINSERVO2 = 23;                    // pin control servo 2
Servo servo1, servo2;                  // crea objetos servo1 y servo2

const int PWM = 21;                // pin 21 velicidad giro motor
const int freq = 5000;             // setting PWM properties
const int cana = 2;
const int reso = 8;

const int car = 16;

int g1 = 90;
int g2 = 90;
int vel = 0;
int vel2 = 0;
                        
BluetoothSerial SerialBT;                         // objeto bluetooth

void setup() {
  servo1.attach(PINSERVO1, PULSOMIN, PULSOMAX);   // configuro el servo
  servo2.attach(PINSERVO2, PULSOMIN, PULSOMAX); 
  servo1.write(g1);                               // ubica el servo en la dirección
  servo2.write(g2);                               // ubica el servo en la dirección
  
  Serial.begin(115200);
  
  ledcSetup(cana, freq, reso);                    // configuracion pwm
  ledcAttachPin(PWM, cana);                       // GPIO a controlar

  pinMode(car, OUTPUT);
  
  SerialBT.begin("ESP32");                        // Bluetooth device name
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
        vel = vel+5;
        if (vel >= 100){
          vel = 100;
          }
          vel2 = vel * 2.55;
          Serial.print(vel2);
          Serial.print("\n");
        }
     if ( x == 'v')
      {
        vel = vel-5;
        if (vel <= 0){
          vel = 0;
          }
          vel2 = vel * 2.55;
          Serial.print(vel2);
          Serial.print("\n");
        }
      
     if ( x == 'L')
      { 
        digitalWrite(car, HIGH);
        delay(500);
        digitalWrite(car, LOW);
        Serial.print("cargado"); // velocidad del motor que lanzara
        Serial.print("\n"); 
        }

       SerialBT.print("*U");
       SerialBT.print(vel);
       SerialBT.print("*");
       ledcWrite(cana, vel2);
  }
}
