#include <DMD32.h> //library pamtalla dmd
#include "fonts/SystemFont5x7.h" // tamaño letra
#include "fonts/Arial_black_16.h"
#include <SPI.h>

//datos de la pantalla DMD library as dmd

#define PIN_DMD_nOE 22          // D22 active low Output Enable, setting this low lights all the LEDs in the selected rows. Can pwm it at very high frequency for brightness control.
#define PIN_DMD_A 4             // D19 MISO
#define PIN_DMD_B 21            // D21
#define PIN_DMD_CLK 18          // 18_SCK  is SPI Clock if SPI is used
#define PIN_DMD_SCLK 2          // D2_CLKD
#define PIN_DMD_R_DATA 23       // D23_MOSI is SPI Master Out if SPI is used
#define PIN_OTHER_SPI_nCS SS 5

#define ancho 1
#define alto 1
DMD dmd(ancho, alto);

hw_timer_t * timer = NULL;

void IRAM_ATTR triggerScan()
{
  dmd.scanDisplayBySPI();
}

void setup(void) {
  Serial.begin(115200);
  dmd.clearScreen(false);                          //limpia la pantalla
  
}

void loop() {
    
  dmd.drawFilledBox( 0, 0, 16, 64, GRAPHICS_NORMAL );
  Serial.print("hola");
  Serial.print('\n');
  delay( 10000 );  
  
  dmd.drawTestPattern( PATTERN_ALT_0 );
  Serial.print("hola1");
  Serial.print('\n');
  delay( 10000 );

  dmd.drawTestPattern( PATTERN_ALT_1 );
  Serial.print("hola2");
  Serial.print('\n');
  delay( 10000 );
}
