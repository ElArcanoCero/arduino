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

int ban1 = 0;



                        
BluetoothSerial SerialBT;                          // objeto bluetooth


void contador() { 

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
       ban1 = 1;
     }
     
  }
} 
