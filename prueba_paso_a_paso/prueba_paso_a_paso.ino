#include <Wire.h>                                       // libreria para bus I2C
#include <Adafruit_GFX.h>                               // control graficas
#include <Adafruit_SSD1306.h>                           // libreria para controlador SSD1306
#define ANCHO 128                                       // 128 columnas
#define ALTO 64                                         // 64 filas
#define OLED_RESET 4                                    // necesario por la libreria pero no usado
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);  // creo objeto oled

int IN1 = 8;      // pin 8 de Arduino a IN1 de modulo controlador
int IN2 = 9;      // pin 9 de Arduino a IN2 de modulo controlador
int IN3 = 10;     // pin 10 de Arduino a IN3 de modulo controlador
int IN4 = 11;     // pin 11 de Arduino a IN4 de modulo controlador


// paso completo con maximo torque
int paso [4][4] =   // matriz (4x4) con la secuencia de pasos
{
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}
};

void setup() 
{
  Wire.begin();                               // inicializa bus I2C para la OLED
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3D);     // Inicia la pantalla con la direeción en el bus I2C: 0X3D(Proteus)0X3C(Arduino)
  oled.clearDisplay();                        // Borra la pantalla
  pinMode(IN1, OUTPUT);   
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() 
{
 int i = 0;
 int j = 0;
// GIRO EN SENTIDO HORARIO ; 15° GRADOS POR PASO
  for (int j = 0; j < 6; j++) // 6*4 = 24 pasos       
  {
    for (int i = 0; i < 4; i++)   // bucle recorre la matriz de a una fila por vez
    { 
      digitalWrite(IN1, paso[i][0]); 
      digitalWrite(IN2, paso[i][1]);
      digitalWrite(IN3, paso[i][2]);
      digitalWrite(IN4, paso[i][3]);
      oled.clearDisplay();                         // Borra pantalla
      oled.setTextColor(WHITE);                    // establece color al unico disponible (pantalla monocromo)
      oled.drawPixel(i, j, WHITE);                 // dibuja dibuja un punto
      oled.display();                              // Actualiza pantalla (sin este comando la pantalla no meustra nada) 
 
      delay(1000);
    }
  }
 
  delay(2000); // Retardo para cambio de giro

// GIRO EN SENTIDO ANTI-HORARIO; 15° GRADOS POR PASO
/*   for (int j = 0; j < 6; j++) // 6*4 = 24 pasos
  {
    for (int i = 4; i > 0; i--) // Recorre cada fila
    {        
      digitalWrite(IN1, paso[i][0]);  
      digitalWrite(IN2, paso[i][1]);
      digitalWrite(IN3, paso[i][2]);
      digitalWrite(IN4, paso[i][3]);
      delay(demora);
    }
  }
  
      digitalWrite(IN1, 0); // Motor apagado
      digitalWrite(IN2, 0);
      digitalWrite(IN3, 0);
      digitalWrite(IN4, 0);
      delay(2000);  // Retardo para cambio de giro*/

}
