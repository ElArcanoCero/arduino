#include <ESP32Servo.h>               // libreria servo


// the number of the LED pin
const int ledPin = 16;  // 16 corresponds to GPIO16
const int PWM = 18;               // pin 18 velicidad giro motor

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
 
void setup(){
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, ledChannel);

  pinMode(PWM, OUTPUT);                       // pin 18 salida controla el motor
}
 
void loop(){
  // increase the LED brightness
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);
    analogWrite(PWM, dutyCycle);
    delay(150);
  }

  // decrease the LED brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);
    analogWrite(PWM, dutyCycle);   
    delay(150);
  }
}
