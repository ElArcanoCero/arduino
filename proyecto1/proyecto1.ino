#include<TimerOne.h>            // libreria para la funcion attachInterrupt
#include <Wire.h>               // libreria para bus I2C
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>   // libreria para controlador SSD1306
#define ANCHO 128               // 128 columnas
#define ALTO 64                 // 64 filas
#define OLED_RESET 4            // necesario por la libreria pero no usado
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);  // crea objeto para la OLED SSD1306


float frec = 0;                  // variable global frecuencia
int rpm = 0;                     // variable global rpm
int vel = 0;                     // variable global velocidad
float dist = 0;                  // variable global distancia
unsigned long seg = 0;           // variable global segundos
float numr = 0;                  // variable de respaldo para calculo de distancia
int band = 0;                    // bandera
int reset = 4;                   // pin 4
const int PWM = 5;               // pin 5 velicidad giro motor
const int encoder = 8;           // Pin 8 del Arduino para leer el encoder
const int led = 10;              // pin 10 enciende led
int acein = 0;                   // variable entera
int aceout = 0;                  // variable entera
unsigned long p1 = 0;            // variable entera larga
unsigned long p2 = 0;            // variable entera larga


void setup() {
    Wire.begin();                            // inicializa bus I2C para la OLED
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // Inicia la pantalla con la direción en el bus I2C: 0X3D(Proteus)0X3C(Arduino)
    oled.clearDisplay();                     // Borra la pantalla
    oled.setTextColor(SSD1306_WHITE);        // Pantalla a un solo color
    pinMode(PWM, OUTPUT);                    // pin 5 salida controla el motor
    pinMode(encoder, INPUT);                 // Pin 8 como entrada giros del motor
    pinMode(led, OUTPUT);                    // pin 10 salida led parpadea
    Timer1.initialize(1000000);              // activa el attach interrupt cada  segundo
    Timer1.attachInterrupt(reloj1);          // llama a la funcion reloj1
    mostrarDatos();                          // Llama función para mostrar el valores iniciales en la OLED
}

void loop() {
 acein = analogRead(A0);                     // leer entrada analoga A0
 aceout = map(acein,0,1023,0,255);           // cambia la escala de 10 bits a 8 bits
 analogWrite(PWM, aceout);                   // salida pin 5
 p1 = pulseIn(encoder, HIGH);                // Lee la duración del pulso alto en microsegundos
 p2 = pulseIn(encoder, LOW);                 // Lee la duración del pulso bajo en microsegundos
 frec = 1000000/(p1+p2);                     // Calcula la frecuencia en Hertz, inverso del período 
 rpm = 60*frec;                              // calcula las rpm
 vel = (rpm*60*1.57)/1000;                   // calcula la velocidad
 if( vel >= 30 ){                            // enciende y apaga led
  if (band == 1){
    digitalWrite(led, LOW);
    band = 0;
  }else{
    digitalWrite(led, HIGH);
    band = 1;
  }
 }else {
  digitalWrite(led, LOW);
  }
 mostrarDatos(); 
}
 void reloj1(void){
  numr = (frec*1.57)+ dist;                  // calcula la distancia recorrida cada segundo
  dist = numr ;
  if ( dist >= 10000){
    dist = 0;                                // limpia la variable dist encaso de overflow
  }
  seg++;
}
void mostrarDatos()                          // Función para mostrar en la pantalla OLED las varibles
  {
      oled.clearDisplay();                   // Borra pantalla
      oled.setTextColor(WHITE);              // establece color al unico disponible (pantalla monocromo)
      oled.setTextSize(1);                   // establece tamano de texto 
      oled.setCursor(31,1);                  // ubica cursor en coordenadas
      oled.print("velocimetro");             // escribe en pantalla el texto
      oled.setTextSize(1);                   // establece tamano de texto
      oled.setCursor(1,16);                  // ubica cursor en coordenadas
      oled.print("Frec   :");                // escribe texto en pantalla
      oled.setTextSize(1);                   // establece tamano de texto
      oled.setCursor(55,16);                 // ubica cursor en coordenadas
      oled.print(frec);                      // Muestra una variable 
      oled.setTextSize(1);                   // establece tamano de texto
      oled.setCursor(100,16);                // ubica cursor en coordenadas
      oled.print("Hz");                      // escribe texto en pantalla
      oled.setTextSize(1);                   // establece tamano de texto
      oled.setCursor(1,26);                  // ubica cursor en coordenadas
      oled.print("Rpm    :");                // escribe texto en pantalla
      oled.setTextSize(1);                   // establece tamano de texto
      oled.setCursor(55,26);                 // ubica cursor en coordenadas
      oled.print(rpm);                       // Muestra una variable 
      oled.setTextSize(1);                   // establece tamano de texto
      oled.setCursor(100,26);                // ubica cursor en coordenadas
      oled.print("Rpm");                     // escribe texto en pantalla
      oled.setTextSize(1);                   // establece tamano de texto
      oled.setCursor(1,36);                  // ubica cursor en coordenadas
      oled.print("Vel    :");                // escribe texto en pantalla
      oled.setTextSize(1);                   // establece tamano de texto
      oled.setCursor(55,36);                 // ubica cursor en coordenadas
      oled.print(vel);                       // Muestra una variable 
      oled.setTextSize(1);                   // establece tamano de texto
      oled.setCursor(100,36);                // ubica cursor en coordenadas
      oled.print("K/h");                     // escribe texto en pantalla
      oled.setTextSize(1);                   // establece tamano de texto
      oled.setCursor(1,46);                  // ubica cursor en coordenadas
      oled.print("Dist   :");                // escribe texto en pantalla
      oled.setTextSize(1);                   // establece tamano de texto
      oled.setCursor(55,46);                 // ubica cursor en coordenadas
      oled.print(dist);                      // Muestra una variable 
      oled.setTextSize(1);                   // establece tamano de texto
      oled.setCursor(100,46);                // ubica cursor en coordenadas
      oled.print("Mts");                     // escribe texto en pantalla 
      oled.setTextSize(1);                   // establece tamano de texto
      oled.setCursor(1,56);                  // ubica cursor en coordenadas
      oled.print("Tiemp  :");                // escribe texto en pantalla
      oled.setTextSize(1);                   // establece tamano de texto
      oled.setCursor(55,56);                 // ubica cursor en coordenadas
      oled.print(seg);                       // Muestra una variable 
      oled.setTextSize(1);                   // establece tamano de texto
      oled.setCursor(100,56);                // ubica cursor en coordenadas
      oled.print("seg");                     // escribe texto en pantalla
      oled.display();                        // Actualiza pantalla (sin este comando la pantalla no meustra nada)      
  }
