
#include <Wire.h> 

 

int puls = 2;
int led = 13;
int ban = 0;

void setup() {
pinMode(puls, INPUT);
pinMode(led, OUTPUT);

}

void loop() {
  while(digitalRead(puls) == HIGH){
   while(ban != 5){
    digitalWrite(led ,HIGH); 
    delay(500);
    digitalWrite(led ,LOW);
    delay(500);
    ban++;
   }
    ban = 0; 
  }
}
