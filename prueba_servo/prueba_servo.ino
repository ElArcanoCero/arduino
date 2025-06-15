#include <ESP32Servo.h>               // libreria servo
int PINSERVO = 26;                    // pin control servo
int PULSOMIN = 550;                   // pulso minimo en milisegundos
int PULSOMAX = 2500;                  // pulso maximo en milisegundos
Servo servo1;                         // creo objeto servo
 


void setup(){
 servo1.attach(PINSERVO, PULSOMIN, PULSOMAX); // inicializa el servo
}

void loop()
{
servo1.write(0);
delay(5000);
servo1.write(90);              // ubica el servo en la dirección
delay(200);
servo1.write(0);
delay(5000);
servo1.write(90);              // ubica el servo en la dirección
delay(200);
servo1.write(0);              // ubica el servo en la dirección
delay(200);


}
