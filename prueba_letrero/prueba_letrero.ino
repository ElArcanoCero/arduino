#include <DMD32.h> //library pamtalla dmd
#include "fonts/SystemFont5x7.h" // tamaño letra
#include "fonts/Arial_black_16.h"
//#include "fonts/Arial_Black_16_ISO_8859_1.h" // tipo de letra
#include "BluetoothSerial.h" // libreria serial bluetooth

//datos de la pantalla DMD library as dmd
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

#define PIN_DMD_nOE       5     // D22 active low Output Enable, setting this low lights all the LEDs in the selected rows. Can pwm it at very high frequency for brightness control.
#define PIN_DMD_B         21     // D21
#define PIN_DMD_SCLK      2      // D02

#define PIN_DMD_R_DATA    23     // D23_MOSI is SPI Master Out if SPI is used
#define PIN_DMD_A         19     // D19
#define PIN_DMD_CLK       18     // D18_SCK  is SPI Clock if SPI is used




#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT; // renombremos bluetoothserial como serialbt


hw_timer_t * timer = NULL; //timer para  ESP32

 //variables
String  mensaje1 = "Robot-13";
char  mensaje2[50];
String  mensaje3;
char mensaje4[5];
int temp;


void IRAM_ATTR triggerScan()
{
  dmd.scanDisplayBySPI();
}

void setup(void) {
  Serial.begin(19200);
  SerialBT.begin("letrero prueba 1");                        // Bluetooth device name  
  Serial.println("listo para conectar");
  uint8_t cpuClock = ESP.getCpuFreqMHz();
  timer = timerBegin(0, cpuClock, true);
  timerAttachInterrupt(timer, &triggerScan, true);
  timerAlarmWrite(timer, 600, true); 
  //cambian el tiempo de alarma deacuerdo al modelo de la esp 300 para lolin y 500 para la devkit
  timerAlarmEnable(timer);
  dmd.clearScreen( true );                          //limpia la pantalla

 
}

void loop() {
  
  if (SerialBT.available()) { 
    mensaje3 = (String)SerialBT.readString();
    int ml = mensaje3.length() + 1; 
    mensaje3.toCharArray(mensaje4, 5);
    temp = atoi(mensaje4);
    if(temp == 5555){
       mensaje1 = mensaje3.substring(4,ml);
       }   
  }   
      SerialBT.print("*U");
      SerialBT.print(mensaje1);
      SerialBT.print("*");
      byte b;
      dmd.clearScreen( true );
      dmd.selectFont(Arial_Black_16);
      int lon = mensaje1.length();
      mensaje1.toCharArray(mensaje2, 50);
      dmd.drawMarquee(mensaje2, lon, (32*DISPLAYS_ACROSS)-1, 0);
      long start = millis();
      long timer = start;
      boolean ret=false;
      while(!ret){
          if ((timer+30) < millis()) {
              ret=dmd.stepMarquee(-1,0);
              timer=millis();
             }   
      } 
}
