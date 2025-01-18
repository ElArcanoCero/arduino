#include "BluetoothSerial.h"          // libreria bluethooth
#include <ESP32Servo.h>               // libreria servo y señal pwm


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


const int PWM1 = 16;                                // pin 16 velicidad giro motor
const int PWM2 = 17;                                // pin 17 velicidad giro motor
int encoder1 = 27;                                  // Pin 12 del Arduino para leer el sensor
int encoder2 = 14;                                  // Pin 14 del Arduino para leer el sensor

int vel = 0;
int vel2 = 0;

int ban1 = 0;
int ban2 = 0;
int ban3 = 1;
                        
BluetoothSerial SerialBT;                          // objeto bluetooth

void IRAM_ATTR contador1(){  
  if (ban2 == 22){
    Serial.print("vuelta1 :");
    Serial.print(ban3);
    Serial.print("\n");
    vel = 0;
    analogWrite(PWM1,vel);
    ban3++;
    ban2 = 0;
    } 
  Serial.print("A");
  Serial.print(ban2);
  Serial.print("\n");
  ban2++;
}
void IRAM_ATTR contador2(){  
  if (ban2 == 22){
    Serial.print("vuelta2 :");
    Serial.print(ban3);
    Serial.print("\n");
    vel = 0;
    analogWrite(PWM1,vel);
    ban3++;
    ban2 = 0;
    } 
  Serial.print("B");
  Serial.print(ban2);
  Serial.print("\n");
  ban2++;
}

void setup() {
  
  Serial.begin(115200);

  pinMode(encoder1, INPUT);                        // Pin 12 como entrada
  pinMode(encoder2, INPUT);                        // Pin 14 como entrada
  pinMode(PWM2, OUTPUT);                           // pin 17 salida controla el motor
  pinMode(PWM1, OUTPUT);                           // pin 18 salida controla el motor
  
  SerialBT.begin("scara");                         // Bluetooth device name
  Serial.println("listo para conectar");
}

void loop() {
  
  if (SerialBT.available()) { 
     if (ban1 == 0){
        attachInterrupt(digitalPinToInterrupt(encoder1), contador1, CHANGE);  
        attachInterrupt(digitalPinToInterrupt(encoder2), contador2, CHANGE);      
        ban1 = 1;
     }
     char x = (char)SerialBT.read();
     if ( x == 'V')
      {
       if (vel == 0){
        Serial.print("en linea");
        Serial.print("\n");
        vel = 100;
        vel2 = vel * 1.91;
        analogWrite(PWM1, vel2);
        analogWrite(PWM2, 0);
        }    
      }
    }
} 
