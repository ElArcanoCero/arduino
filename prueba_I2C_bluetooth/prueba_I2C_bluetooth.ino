#include "BluetoothSerial.h" // libreria serial bluetooth
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
// sda pin 21 scl pin 22
#define ancho 128 // OLED display width, in pixels
#define alto 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G oled = Adafruit_SH1106G(ancho, alto, &Wire, OLED_RESET);


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


BluetoothSerial SerialBT; // renombremos bluetoothserial como serialbt




 //variables
String  mensaje1 = "Robot-13";
char mensaje2[5];
String  mensaje3;
int temp;
int ml;


void setup(void) {

  Serial.begin(9600);
  SerialBT.begin("pantalla I2C");                // Bluetooth device name 
//  SerialBT.setPin("1234");
//  if (!SerialBT.connect("pantalla I2C"))
//  {
//    SerialBT.print("*U");
//    SerialBT.print("pin");
//    SerialBT.print("*");
//    while(1);
//  }
  Wire.begin();                               // inicializa bus I2C para la OLED
  oled.begin(i2c_Address, true);              // Inicia la pantalla con la direeción en el bus I2C: 0X3D(Proteus)0X3C(Arduino) 
  oled.clearDisplay();                        // Borra pantalla
  oled.setTextColor(SH110X_WHITE);            // establece color al unico disponible (pantalla monocromo)
  oled.setTextSize(2);                        // establece tamano de texto 
  oled.setCursor(4,26); 
  oled.print(mensaje1);                       // escribe en pantalla la variable
  oled.display();
}

void loop() {

   if (SerialBT.available()) { 
    mensaje3 = (String)SerialBT.readString();
    ml = mensaje3.length() + 1; 
    mensaje3.toCharArray(mensaje2, 5);
    temp = atoi(mensaje2);
    Serial.print(mensaje1);
    Serial.print('\n');
    if(temp == 5555){
        mensaje1 = mensaje3.substring(4,ml);
        Serial.print(mensaje1);
        Serial.print('\n');
        Serial.print(mensaje2);
        Serial.print('\n');
        }
      }
    SerialBT.print("*U");
    SerialBT.print(mensaje1);
    SerialBT.print("*");
    oled.clearDisplay();                           // Borra pantalla
    oled.setTextColor(SH110X_WHITE);               // establece color al unico disponible (pantalla monocromo)
    oled.setTextSize(2);                           // establece tamano de texto 
    oled.setCursor(4,26); 
    oled.print(mensaje1);                          // escribe en pantalla la variable
    oled.display();
    delay(500);
        
}
