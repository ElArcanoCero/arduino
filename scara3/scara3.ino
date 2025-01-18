#include "BluetoothSerial.h"          // libreria bluethooth
#include <ESP32Servo.h>               // libreria servo y señal pwm
#include "ArduPID.h"



#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


const int PWM1 = 16;                                // pin 16 velicidad giro motor
//const int PWM2 = 17;                              // pin 17 velicidad giro motor
int encoder1 = 27;                                  // Pin 12 del Arduino para leer el sensor
int encoder2 = 14;                                  // Pin 14 del Arduino para leer el sensor
ArduPID myController;

int temp = 0;
short ang = 10;
int pulso = 0;
int giro = 0;
int ga = 0;
int Frec = 0;
int ban = 0;
unsigned long p1 = 0;
unsigned long p2 = 0;
int periodom = 5000;

double input;
double output;

double setpoint;
double p = 0.00000024704;
double i = 0.0000021065;
double d = 0;
                        
BluetoothSerial SerialBT;                          // objeto bluetooth

hw_timer_t * timer = NULL;

void contador1(){
  pulso = pulso + 1;
  } 
void IRAM_ATTR contador() { 
  if (p1 != 0 or p2 != 0){
      Frec = (1000000/(p1+p2))/11;                    // Calcula la frecuencia en Hertz, inverso del período 
      input = Frec/0.01667;                            //calcula velocidad en el eje del motor    
      
    }else{
        input = 0;
        
      } 
}

void setup() {
  
  Serial.begin(115200);
 
  

  pinMode(encoder1, INPUT);                        // Pin 12 como entrada
  pinMode(encoder2, INPUT);                        // Pin 14 como entrada
  pinMode(PWM1, OUTPUT);                           // pin 18 salida controla el motor
  
  SerialBT.begin("scara");                         // Bluetooth device name
  Serial.println("listo para conectar");
}

void loop() {
  attachInterrupt(encoder2, contador1, CHANGE);
  
  if (SerialBT.available()) { 
     
     char x = (char)SerialBT.read();
     if ( x == 'V')
      { 
         p1 = pulseIn(encoder1, HIGH);                   // Lee la duración del pulso alto en microsegundos
         p2 = pulseIn(encoder1, LOW);                    // Lee la duración del pulso bajo en microsegundos
        if(setpoint <= 1000)
        {
          setpoint = 10000;
          myController.compute();
          analogWrite(PWM1, output);  
          delay(10); 
          setpoint = 1000;
          }
        timer = timerBegin(0, 40, true);
        timerAttachInterrupt(timer, &contador, true);
        timerAlarmWrite(timer, periodom, true);           // poner el tiempo en millonesimas de segundo
        timerAlarmEnable(timer);

        myController.begin(&input, &output, &setpoint, p, i, d);
        myController.setOutputLimits(0, 191);
        myController.setBias(191.0 / 10.0);
        myController.setWindUpLimits(-10, 1000);
        myController.start();  
        
        ban = 1;
        
        myController.compute();
        analogWrite(PWM1, output);       
      }
     if ( x == 'D')
      { 
        setpoint = setpoint+1000;
        if(setpoint >= 10000)
        {
            setpoint = 10000;
            }           
      }
     if ( x == 'I')
      {
          setpoint = setpoint-1000;
          if(setpoint <= 900)
          {
            setpoint = 0;
            x = 'v';
            }
      }
      if ( x == 'v')
      {
          setpoint = 0; 
          output = 0;
          input = 0;
          timerAlarmDisable(timer);
          myController.stop(); 
//          analogWrite(PWM1, output);
          ban = 0;
          pulso = 0;
       }    
        if ( x == 'R')
      {
          ang = ang + 10;
          if(ang >= 360)
          {
            ang = 360;
            }
      } 
       if ( x == 'W')
      {
          ang = ang - 10;
          if(ang <= 10)
          {
            ang = 10;
            }
      }    
  }
    ga = ang*16.7291;
    if ( pulso >= ga)
    {
       setpoint = 0; 
       output = 0;
       input = 0;
       timerAlarmDisable(timer);
       myController.stop(); 
//       analogWrite(PWM1, output);
       ban = 0;
       pulso = 0; 
      }
   
    if ( ban == 1)
    {
      p1 = pulseIn(encoder1, HIGH);                   // Lee la duración del pulso alto en microsegundos
      p2 = pulseIn(encoder1, LOW);                    // Lee la duración del pulso bajo en microsegundos
      myController.compute();
//      analogWrite(PWM1, output);
      }
    SerialBT.print("*T");
    SerialBT.print(setpoint);
    SerialBT.print("*");
    SerialBT.print("*G");
    SerialBT.print(ang);
    SerialBT.print("*");
    if (temp != pulso){
    Serial.println("numero pulsos : ");
    Serial.println(pulso);
    Serial.println("limite requerido : ");
    Serial.println(ga);
    }
    temp = pulso;
} 
