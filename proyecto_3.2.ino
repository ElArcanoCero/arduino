#include <Wire.h>                                       // libreria para bus I2C
#include <Adafruit_GFX.h>                               // control graficas
#include "Adafruit_SH1106.h"                            // libreria para controlador sh1106
#define ANCHO 128                                       // 128 columnas
#define ALTO 64                                         // 64 filas
#define OLED_RESET 4                                    // necesario por la libreria pero no usado
Adafruit_SH1106 oled(OLED_RESET);                       // creo objeto oled

#include <Servo.h>                                      // libreria servo
int PINSERVO = 5;                                       // pin control servo
int PULSOMIN = 550;                                     // pulso minimo en milisegundos
int PULSOMAX = 2500;                                    // pulso maximo en milisegundos
Servo servo;                                            // creo objeto servo

int in1 = 8;                                            // pin 1 modulo de control 2003
int in2 = 9;                                            // pin 2 modulo de control 2003
int in3 = 10;                                           // pin 3 modulo de control 2003
int in4 = 11;                                           // pin 4 modulo de control 2003
int ang = 0;                                            // angulo
int ang2 = 0;                                           // angulo 2
float rad = 0;                                          // angulo en radianes
float rad2 = 0;                                         // angulo en radianes 2
float x = 0;                                            // cordenada x
float y = 0;                                            // cordenada y 
float cont = 0;                                         // contador
int cont2 = 0;                                          // contador 2
int band = 0;                                           // bandera control ciclo motor paso a paso




int matriz [4][4] =                                     // matriz (4x4) con la secuencia de pasos
{
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}
};


void setup() {
    Wire.begin();                                        // inicializa bus I2C para la OLED
    oled.begin(SH1106_SWITCHCAPVCC, 0x3C);               // initialize with the I2C addr 0x3C (for the 128x64)
    oled.clearDisplay();                                 // Borra la pantalla 
    servo.attach(PINSERVO, PULSOMIN, PULSOMAX);          // inicializa el servo
    pinMode(in1, OUTPUT);                                // pin 8 a in 1 controladora 2003
    pinMode(in2, OUTPUT);                                // pin 9 a in 2 controladora 2003
    pinMode(in3, OUTPUT);                                // pin 10 a in 3 controladora 2003 
    pinMode(in4, OUTPUT);                                // pin 11 a in 4 controladora 2003

    
}

void loop() {
    
     oled.clearDisplay();                                 // Borra pantalla
     for( ang = 5; ang<=90; ang = ang+5){                 // ciclo servomotor
     servo.write(ang);                                    // gira el servo al angulo
     if (band == 0){                                      // control giro motor paso a paso
     funcion();                                          
     for (int j = 0; j < 256; j++)                        // 256*4 = 1024 pasos ciclo 1 motor paso a paso   
    { 
     for (int i = 0; i < 4; i++)                          // bucle recorre la matriz de a una fila por vez
    { 
     digitalWrite(in1, matriz[i][0]);                     // lleva lo que tiene la matriz en la posisicon i,0 a in 1      
     digitalWrite(in2, matriz[i][1]);                     // lleva lo que tiene la matriz en la posisicon i,1 a in 2      
     digitalWrite(in3, matriz[i][2]);                     // lleva lo que tiene la matriz en la posisicon i,2 a in 3
     digitalWrite(in4, matriz[i][3]);                     // lleva lo que tiene la matriz en la posisicon i,3 a in 4
     funcion1();                                          // llamado funcion 1
     } 
     }
     band = 1;                                             // cambio de ciclo motor paso a paso
     cont2 = 18;                                           // seguro para extremo superior
     funcion();                                            // llamado a funcion
     }else{
     funcion();
     for (int j = 0; j < 256; j++)                          // 256*4 = 1024 pasos ciclo 2 motor paso a paso 
    { 
     for (int i = 3; i > -1; i--)                           // bucle recorre la matriz de a una fila por vez
    { 
     digitalWrite(in1, matriz[i][0]);                       // lleva lo que tiene la matriz en la posisicon i,0 a in 1       
     digitalWrite(in2, matriz[i][1]);                       // lleva lo que tiene la matriz en la posisicon i,1 a in 2       
     digitalWrite(in3, matriz[i][2]);                       // lleva lo que tiene la matriz en la posisicon i,2 a in 3                                           
     digitalWrite(in4, matriz[i][3]);                       // lleva lo que tiene la matriz en la posisicon i,3 a in 4
     funcion2();                                            // llamado funcion 2
     }  
     }
     band = 0;                                              // cambio de ciclo motor paso a paso
     cont2 = 0;                                             // seguro para extremo inferior 
     funcion();                                             // llama a funcion
      }
     }   
}
void funcion()
{  
     ang2 = cont2*10;                                        // crea angulos base 10
     rad2 = (ang2)*(3.1415927/180);                          // convierte a radianes
     rad = (ang)*(3.1415927/180);                            // convierte a radianes
     x = 64 - ((60*sin(rad))*(cos(rad2)));                   // cancula cordenada x
     y = 63 - ((60*sin(rad))*(sin(rad2)));                   // cancula cordenada y
     mostrarDatos();                                         // llama funcion  
     }
void funcion1()                                              // funcion que cuenta cada vez que avaza 10 grados
   {  
    cont = cont + 0.17578125;                                // calcula 10 grados sumando el avance por ciclo 
     if (cont >= 10){
        cont2++;                                             // calcula el numero de veces que avanzo 10 grados
        funcion();                                           // llama a funcion
        cont = 0;                                            // reinicia contador cont 
      } 
     delay(5);
     }
void funcion2()                                              // funcion que cuenta cada vez que retrocede 10 grados
   { 
    cont = cont + 0.17578125;                                // calcula 10 grados sumando el avance por ciclo                             
     if (cont >= 10){
        cont2--;                                             // calcula el numero de veces que retrocede 10 grados
        funcion();                                           // llama a funcion
        cont = 0;                                            // reinicia contador cont 
      }
     delay(5);
     }
void mostrarDatos()                                          // Función para mostrar en la pantalla OLED las varibles
  {
      oled.setTextColor(WHITE);                              // establece color al unico disponible (pantalla monocromo)
      oled.drawCircle(64, 63, 1, WHITE);                     // dibuja circulo cordenadas 64 x, 60 y, 4 radio & white color 
      oled.drawCircle(64, 63, 61, WHITE);                    // dibuja circulo
      oled.drawPixel(x, y, WHITE);                           // dibuja dibuja un punto
      oled.display();                                        // Actualiza pantalla (sin este comando la pantalla no meustra nada) 
   }
