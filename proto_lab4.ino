#include <LiquidCrystal.h>

#include <Wire.h>
#include<TimerOne.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f ,16,2);
//LiquidCrystal_I2C lcd(0x27 ,16,2);

int num = 0;
float num2 = 0;
unsigned long tiem = 0;
int metro = 0;
int bit0 = 0;
int bit1 = 1;
int bit2 = 2;
int bit3 = 3;
int bit4 = 4;
int bit5 = 5;
int bit6 = 6;
int reloj3 = 10;
int UltracSonic = 7;
const int TRIGGER = 12;
int Reloj1 = 9;
int Reloj2 = 8;
const int distancia = 11;
volatile int ban1 = 0;
volatile int ban2 = 0;
volatile int ban3 = 0;





void setup() {
lcd.init();
lcd.backlight();
lcd.print("Holi Profeee");
delay(2000);
lcd.clear();

pinMode(distancia, OUTPUT);
pinMode(bit0, INPUT);
pinMode(bit1, INPUT);
pinMode(bit2, INPUT);
pinMode(bit3, INPUT);
pinMode(bit4, INPUT);
pinMode(bit5, INPUT);
pinMode(bit6, INPUT);
pinMode(reloj3, INPUT);
pinMode(TRIGGER, OUTPUT);
pinMode(UltracSonic, INPUT);
pinMode(Reloj1, OUTPUT);
pinMode(Reloj2, OUTPUT);
Timer1.initialize(2000);
Timer1.attachInterrupt(reloj1);
}
void reloj1(void)
{
ban3++;
if(ban1 == 0){
digitalWrite(Reloj1,LOW);
ban1 = 1;
}else{
digitalWrite(Reloj1,HIGH);
ban1 = 0;
}
if(ban3 == 1500){
if(ban2 == 0){
digitalWrite(Reloj2,LOW);
ban2 = 1;
}else{
digitalWrite(Reloj2,HIGH);
ban2 = 0;
}
ban3 = 0;
}
}



void loop() {

lcd.clear();
num = 0;
digitalWrite(TRIGGER,HIGH);
delay(1);
digitalWrite(TRIGGER,LOW);
tiem = pulseIn(UltracSonic, HIGH);
metro = (tiem/58.2);
analogWrite(distancia,metro);
if (digitalRead(bit0) == HIGH) {
num = num + pow(2,0);
}
if (digitalRead(bit1) == HIGH) {
num = num + pow(2,1);
}
if (digitalRead(bit2) == HIGH) {
num = num + pow(2,2);
}
if (digitalRead(bit3) == HIGH) {
num = num + pow(2,3);
}
if (digitalRead(bit4) == HIGH) {
num = num + pow(2,4);
}
if (digitalRead(bit5) == HIGH) {
num = num + pow(2,5);
}
if (digitalRead(bit6) == HIGH) {
num = num + pow(2,6);
}
if(digitalRead(reloj3) == LOW){

num2 = num;
mostrarDatos1();
}
if(digitalRead(reloj3) == HIGH){
  
  if(num >= 15){
    num2 = (num-1) * 2;
  } 
  else{
  num2 = num * 2;}
mostrarDatos2();
}
}
void mostrarDatos1()
{
  lcd.setCursor(0,0);
  lcd.print("Distancia :");
  lcd.print(num,1);
  lcd.setCursor(0,1);
  lcd.print(metro,1);
  lcd.print(" cm");
  delay(500);
}
void mostrarDatos2()
{

  lcd.setCursor(0,0);
  lcd.print("Temperatura :");
  lcd.print(num,1);
  lcd.setCursor(0,1);
  lcd.print(num2,1);
  lcd.print(" \xDF" "C");
  delay(500);
}
