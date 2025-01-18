#include <LiquidCrystal.h>
LiquidCrystal lcd(A5, A4, A3, A2, A1, A0);void setup() { pinMode(pin_eoc,INPUT);

const int Q0=0;
const int Q1=1;
const int Q2=2;
const int Q3=3;
const int Q4=4;
const int Q5=5;
const int Q6=6;
const int UltracSonic=7;
const int distancia=13;
const int TRIGGER=12;
const int num = 0;
float num2 = 0;const int pin_direccion=8;
const int pin_pwm=9;
const int pin_start=10;
const int pin_eoc=11;
unsigned long ultimo_tiempo=0;
int periodo=3000;char senal='p';
float valor;

pinMode(UltracSonic, INPUT);
pinMode(pin_pwm,OUTPUT);
pinMode(pin_direccion,OUTPUT);
pinMode(pin_start,OUTPUT);
pinMode(TRIGGER,OUTPUT);
digitalWrite(pin_direccion,LOW);
digitalWrite(pin_start,LOW);
Reloj();
lcd.begin(16,2);
}
void loop() { if ((millis()-ultimo_tiempo)>=periodo)
{
ultimo_tiempo=millis();
lcd.clear(); if (senal=='p')
{
senal='t';
digitalWrite(pin_direccion,HIGH);
}
else
{
senal='p';
digitalWrite(pin_direccion,LOW);
}
}
else
{
if (senal=='t')
{
Lectura();
MostrarTemp();
delay(600);
}
else
{
Lectura();
Mostrardistancia();
delay(600);
}
}
}void Lectura()
{
digitalWrite(pin_start,HIGH);
delayMicroseconds(5);
digitalWrite(pin_start,LOW);
delayMicroseconds(100);
while(!digitalRead(pin_eoc)){}
valor=Numero();
}float Numero(){
float n0=digitalRead(Q0); float n1=digitalRead(Q1);
float n2=digitalRead(Q2); float n3=digitalRead(Q3);
float n4=digitalRead(Q4); float n5=digitalRead(Q5);
float n6=digitalRead(Q6);
return n0+n1*2+n2*4+n3*8+n4*16+n5*32+n6*64;
}void MostrarTemp()
{
lcd.setCursor(0,0);
lcd.print("Temperatura:");
lcd.print(valor,1);
float temp=(150*valor/77);
lcd.setCursor(0,1);
lcd.print(temp,2);
lcd.print("\xDF" "C");
}
void Mostrardistancia()
{
num2 = num;
lcd.setCursor(0,0);
lcd.print("Distancia");
lcd.setCursor(0,1);
lcd.print(num2,2);
lcd.print(" cm");
}
void Reloj()
{
TCCR2A = B00000000;
TCCR2B = B00000001;
TCNT2 = 0;
OCR2A = 15;
TIMSK2 = B00000010;
sei();
}
ISR(TIMER2_COMPA_vect)
{
PORTB=PORTB^0B00000010;
}
