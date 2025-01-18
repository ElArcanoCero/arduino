#include <TinyDHT.h>             // libreria sensor HDT
#define DHTPIN 7                 // enstrada de datos del sensor dht
#define DHTTYPE DHT11            // serie del sensor especifico
DHT dht(DHTPIN, DHTTYPE);        // crea objeto para el DHT11

#include <Wire.h>                   // libreria para bus I2C
#include <Adafruit_GFX.h>           // control graficas
#include "Adafruit_SH1106.h"        // libreria para controlador sh1106
#define ANCHO 128                   // 128 columnas
#define ALTO 64                     // 64 filas
#define OLED_RESET 4                // necesario por la libreria pero no usado
Adafruit_SH1106 oled(OLED_RESET);   // creo objeto oled

#include <Servo.h>               // libreria servo
int PINSERVO = 6;                // pin control servo
int PULSOMIN = 550;              // pulso minimo en milisegundos
int PULSOMAX = 2500;             // pulso maximo en milisegundos
Servo servo;                     // creo objeto servo


const int TRIG = 2;              // pin 2 enviar señal utrasonic
const int PWM = 6;               // pin 6 velicidad giro motor
const int DHT = 7;               // pin 7 aun no se que hace
const int ECO = 10;              // pin 10 resive señal utrasonic
const int alar = 11;             // pin 11 aun no se que hace
const int dest = 13;             // pin 13 aun no se que hace
unsigned long tiem = 0;          // variable tiempo
float dist = 0;                  // variable distancia
int hum = 0;                     // variable global humedad
int tem = 0;                     // variable global temperatura
int ang = 0;                     // variable global angulo en grados 
float rad = 0;                   // variable global angulo en radianes
float x = 0;                     //cordenada x superor de la aguja
float y = 0;                     //cordenada y superiodr de la aguja
float x2 = 0;                    //cordenada x superor del misil
float y2 = 0;                    //cordenada y superiodr del misil
int band = 0;                    // bandeara para detectar objetos
int band2 = 0;                   // bandera parpadeo del objeto
int band3 = 0;                   // bandera ya se uso la alarma


void setup() {
    Wire.begin();                               // inicializa bus I2C para la OLED
    oled.begin(SH1106_SWITCHCAPVCC, 0x3C);      // initialize with the I2C addr 0x3C (for the 128x64)
    oled.clearDisplay();                        // Borra la pantalla
    dht.begin();                                // inicializa el dht
    servo.attach(PINSERVO, PULSOMIN, PULSOMAX); // inicializa el servo
    pinMode(TRIG, OUTPUT);                      // pin 2 dispara el sensor
    pinMode(PWM, OUTPUT);                       // pin 6 salida controla el motor
    pinMode(DHT, INPUT);                        // Pin 7 entrada sensor dht
    pinMode(ECO, INPUT);                        // pin 10 resibe pulso del sensonsor  
    pinMode(alar, INPUT);                       // pin 11 boton de alarma
    pinMode(dest, INPUT);                       // pin 13 misil
    
}

void loop() {
 
 for( ang = 0; ang<=180; ang = ang+10){
  funcion();
  }
  for( ang = 180; ang >= 0; ang = ang-10){
 funcion();
}
}
void funcion()
{
    digitalWrite(TRIG,HIGH);                        // inicia pulso alto en el sensor sonic
    delay(1);
    digitalWrite(TRIG,LOW);                         // detiene el pulso alto en el sensor sonic
    tiem = pulseIn(ECO, HIGH);                      // mide la duracion del puso eco
    dist = tiem/(58.2);                             // calcula distancia
      while(dist <= 60 && dist >= 4){
         digitalWrite(TRIG,HIGH);                   // inicia pulso alto en el sensor sonic
         delay(1);
         digitalWrite(TRIG,LOW);                    // detiene el pulso alto en el sensor sonic
         tiem = pulseIn(ECO, HIGH);                 // mide la duracion del puso eco
         dist = tiem/(58.2);                        // calcula distancia
         hum = dht.readHumidity();                  // leer humedad en el sensor dht
         tem = dht.readTemperature();               // leer temperatura en el sensor dht
         x = dist*cos(rad)+64;                      // cancula cordenada x
         y = dist*sin(rad)+60;                      // cancula cordenada y
         if (digitalRead(alar) == HIGH)
            { 
              for( band = 0; band<=dist+2; band++){
                 mostrarDatos3();
                }
                band = 0;
                band3 = 1;
              }
           if (digitalRead(dest) == HIGH)
            { 
              if (band3 == 1)
            { 
              for( band = 1; band<=dist; band++){
                  x2 = band*cos(rad)+64;                      // cancula cordenada x
                  y2 = band*sin(rad)+60;                      // cancula cordenada y
                 mostrarDatos4();
                }
                oled.clearDisplay();                           // Borra pantalla
                oled.setTextColor(WHITE);                      // establece color al unico disponible (pantalla monocromo)
                oled.setTextSize(1);                           // establece tamano de texto 
                oled.setCursor(22,29);                         // ubica cursor en coordenadas
                oled.print("target removed");                  // escribe en pantalla la variable
                oled.display();                                // Actualiza pantalla (sin este comando la pantalla no meustra nada)
                delay(500);
                band = 0;
                band3 = 0;
              }else{
                oled.clearDisplay();                           // Borra pantalla
                oled.setTextColor(WHITE);                      // establece color al unico disponible (pantalla monocromo)
                oled.setTextSize(1);                           // establece tamano de texto 
                oled.setCursor(28,29);                         // ubica cursor en coordenadas
                oled.print("alarm before");                     // escribe en pantalla la variable
                oled.display();                                // Actualiza pantalla (sin este comando la pantalla no meustra nada)
                delay(500);
                  }
              }
         mostrarDatos2();  
            }
         band = 0;
         band3 = 0;
          if (dist < 4){
          oled.clearDisplay();                             // Borra pantalla
          for( int a = 0; a <= 60; a=a+3){ 
              oled.setTextColor(WHITE);                    // establece color al unico disponible (pantalla monocromo)
              oled.drawCircle(64, 60, a, WHITE);           // dibuja onda
              oled.display();                              // Actualiza pantalla (sin este comando la pantalla no meustra nada)
              delay(100);
            }
            oled.clearDisplay();                           // Borra pantalla
            oled.setTextColor(WHITE);                      // establece color al unico disponible (pantalla monocromo)
            oled.setTextSize(2);                           // establece tamano de texto 
            oled.setCursor(4,26);                          // ubica cursor en coordenadas
            oled.print("you`r dead");                      // escribe en pantalla la variable
            oled.display();                                // Actualiza pantalla (sin este comando la pantalla no meustra nada)
            delay(500);
            }else{
             hum = dht.readHumidity();                      // leer humedad en el sensor dht
             tem = dht.readTemperature();                   // leer temperatura en el sensor dht
             servo.write(ang);                              // gira el servo al angulo    
             rad = (ang-180)*(3.1415927/180);               // convierte a radianes
             x = 60*cos(rad)+64;                            // cancula cordenada x
             y = 60*sin(rad)+60;                            // cancula cordenada y
             mostrarDatos();}
  }
void mostrarDatos()                                // Función para mostrar en la pantalla OLED las varibles
  {
      oled.clearDisplay();                         // Borra pantalla
      oled.setTextColor(WHITE);                    // establece color al unico disponible (pantalla monocromo)
      oled.setTextSize(1);                         // establece tamano de texto 
      oled.setCursor(0,0);                         // ubica cursor en coordenadas
      oled.print("H ");                            // escribe en pantalla el texto   
      oled.setTextSize(1);                         // establece tamano de texto 
      oled.setCursor(7,0);                         // ubica cursor en coordenadas
      oled.print(hum);                             // escribe en pantalla la variable
      oled.setTextSize(1);                         // establece tamano de texto 
      oled.setCursor(92,0);                        // ubica cursor en coordenadas
      oled.print("T ");                            // escribe en pantalla el texto   
      oled.setTextSize(1);                         // establece tamano de texto 
      oled.setCursor(98,0);                        // ubica cursor en coordenadas
      oled.print(tem);                             // escribe en pantalla la variable
      oled.drawCircle(64, 60, 2, WHITE);           // dibuja circulo cordenadas 64 x, 60 y, 4 radio & white color 
      oled.drawCircle(64, 60, 60, WHITE);          // dibuja circulo
      oled.drawLine(x, y, 64, 60, WHITE);          // dibuja linea
      oled.display();                              // Actualiza pantalla (sin este comando la pantalla no meustra nada) 
  }

void mostrarDatos2()                               // Función para mostrar en la pantalla OLED las varibles
  {
      oled.clearDisplay();                         // Borra pantalla
      oled.setTextColor(WHITE);                    // establece color al unico disponible (pantalla monocromo)
      oled.setTextSize(1);                         // establece tamano de texto 
      oled.setCursor(0,0);                         // ubica cursor en coordenadas
      oled.print("D ");                            // escribe en pantalla el texto   
      oled.setTextSize(1);                         // establece tamano de texto 
      oled.setCursor(6,0);                         // ubica cursor en coordenadas
      oled.print(dist);                            // escribe en pantalla la variable
      oled.drawCircle(64, 60, 2, WHITE);           // dibuja circulo cordenadas 64 x, 60 y, 4 radio & white color 
      oled.drawCircle(64, 60, 60, WHITE);          // dibuja circulo
      oled.drawCircle(x, y, 3, WHITE);             // dibuja circulo 
      if(band2 == 0){
      oled.fillCircle(x, y, 2, WHITE);             // rellena circulo
      band2 = 1;
      }else{
      oled.fillCircle(x, y, 2, BLACK);             // vacia circulo  
      band2 = 0;
      }  
      oled.display();                              // Actualiza pantalla (sin este comando la pantalla no meustra nada) 
  }
  void mostrarDatos3()                             // Función para mostrar en la pantalla OLED las varibles
  {
      oled.clearDisplay();                         // Borra pantalla
      oled.setTextColor(WHITE);                    // establece color al unico disponible (pantalla monocromo)
      oled.setCursor(0,0);                         // ubica cursor en coordenadas
      oled.print("D ");                            // escribe en pantalla el texto   
      oled.setTextSize(1);                         // establece tamano de texto 
      oled.setCursor(6,0);                         // ubica cursor en coordenadas
      oled.print(dist);                            // escribe en pantalla la variable
      oled.drawCircle(64, 60, 2, WHITE);           // dibuja circulo cordenadas 64 x, 60 y, 4 radio & white color 
      oled.drawCircle(64, 60, 60, WHITE);          // dibuja circulo
      oled.drawCircle(x, y, 3, WHITE);             // dibuja circulo 
      if(band2 == 0){
      oled.fillCircle(x, y, 2, WHITE);             // rellena circulo
      band2 = 1;
      }else{
      oled.fillCircle(x, y, 2, BLACK);             // vacia circulo 
      band2 = 0;
      }  
      oled.drawCircle(64, 60, band, WHITE);        // dibuja onda
      oled.display();                              // Actualiza pantalla (sin este comando la pantalla no meustra nada)
    }
     void mostrarDatos4()                                       // Función para mostrar en la pantalla OLED las varibles
  {
      oled.clearDisplay();                                      // Borra pantalla
      oled.setTextColor(WHITE);                                 // establece color al unico disponible (pantalla monocromo)
      oled.setTextSize(1);                                      // establece tamano de texto 
      oled.setCursor(0,0);                                      // ubica cursor en coordenadas
      oled.print("D ");                                         // escribe en pantalla el texto   
      oled.setTextSize(1);                                      // establece tamano de texto 
      oled.setCursor(6,0);                                      // ubica cursor en coordenadas
      oled.print(dist);                                         // escribe en pantalla la variable
      oled.drawCircle(64, 60, 2, WHITE);                        // dibuja circulo cordenadas 64 x, 60 y, 4 radio & white color 
      oled.drawCircle(64, 60, 60, WHITE);                       // dibuja circulo
      oled.drawTriangle(x2+3, y2, x2-3, y2, x2, y2-6, WHITE);   // dibuja triangulo
      oled.drawCircle(x, y, 3, WHITE);                          // dibuja circulo 
      if(band2 == 0){
      oled.fillCircle(x, y, 2, WHITE);                          // rellena circulo
      band2 = 1;
      }else{
      oled.fillCircle(x, y, 2, BLACK);                          // vacia circulo 
      band2 = 0;
      }
      oled.display();                                           // Actualiza pantalla (sin este comando la pantalla no meustra nada)
    }
