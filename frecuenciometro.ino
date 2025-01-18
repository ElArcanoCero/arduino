#include <Wire.h>      // libreria para bus I2C
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>   // libreria para controlador SSD1306
#define ANCHO 128       // 128 columnas
#define ALTO 64         // 64 filas
#define OLED_RESET 4    // necesario por la libreria pero no usado
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);  // crea objeto para la OLED SSD1306

// Definición de variables
//************************
unsigned long p1 = 0;
unsigned long p2 = 0;
const int sensor = 8;   // Pin 8 del Arduino para leer el sensor
int Frec = 0;
int RPM = 0;
//************************

void setup() 
{
    Wire.begin();                      // inicializa bus I2C para la OLED
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3D); // Inicia la pantalla con la direeción en el bus I2C: 0X3D(Proteus)0X3C(Arduino)
    oled.clearDisplay();               // Borra la pantalla
    oled.setTextColor(SSD1306_WHITE);  // Pantalla a un solo color
    pinMode(sensor, INPUT);            // Pin 8 como entrada
    mostrar_frec();                    // Llama función para mostrar el valores iniciales en la OLED
}

void loop() 
{
     p1 = pulseIn(sensor, HIGH); // Lee la duración del pulso alto en microsegundos
     p2 = pulseIn(sensor, LOW);  // Lee la duración del pulso bajo en microsegundos
     Frec = 1000000/(p1+p2);     // Calcula la frecuencia en Hertz, inverso del período 
     mostrar_frec();             // Llama función para mostrar en la OLED la frecuencia
     delay(500);
}

void mostrar_frec()            // Función para mostrar en la pantalla OLED las varibles
  {
      oled.clearDisplay();       // Borra pantalla
      oled.setTextColor(WHITE);  // establece color al unico disponible (pantalla monocromo)
      oled.setTextSize(2);       // establece tamano de texto en 2
      oled.setCursor(10,10);     // ubica cursor en coordenadas 10,10 
      oled.print("FREC=");       // escribe en pantalla el texto FREC=
      oled.setTextSize(2);       // establece tamano de texto en 2
      oled.setCursor(10,30);     // ubica cursor en coordenadas 10,30 
      oled.print(Frec);          // Muestra la variable Frec
      oled.display();            // Actualiza pantalla (sin este comando la pantalla no meustra nada)      
  }
