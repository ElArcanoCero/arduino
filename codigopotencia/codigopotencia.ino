#include <avr/io.h> // AVR Device specific I/O definitions

const float F_pwm=100e3;// Frecuencia del PWM
const float F_ard=16e6;// Frecuencia del clock del arduino uno

const int P=1;// Preescaler

const int Canal_A=9;// Para arduino Mega usar el puerto 11 (Cambiar 9 por 11)


const float D1=0.5 ; // Duty del canal A


int frec;
int d1;


void setup() {
 pinMode(Canal_A, OUTPUT);
 //Clear Timer 1 Control Register to ensure the timer is properly configured
 TCCR1A = 0;
 TCCR1B = 0;
 frec=(F_ard/(P*F_pwm))-1; // Dato para registro ICR1 a frecuencia de PWM
 d1=frec*D1; // Valor correspondiente al D del canal A
 ICR1 = frec; //Set TOP value for Timer 1. 
 OCR1A = d1; 
 
//Set channel A to non-invert mode
 TCCR1A |= (1 << COM1A1); 
 TCCR1A |= (0 << COM1A0); 
//Set channel B to non-invert mode
 TCCR1A |= (1 << COM1B1); 
 TCCR1A |= (0 << COM1B0); 
//Enables Fast PWM with ICR1 as TOP 
 TCCR1A |= (1 << WGM11);
 TCCR1B |= (1 << WGM12);
 TCCR1B |= (1 << WGM13);
//Starts timer with prescaler of 1 
 TCCR1B |= (1 << CS10); 
 TCCR1B |= (0 << CS11); 
 TCCR1B |= (0 << CS21); 
}

void loop() {
}
