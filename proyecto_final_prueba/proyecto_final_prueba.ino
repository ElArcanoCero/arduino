#include <WiFi.h>
#include <Ubidots.h>

const int led = 2;                                       // brillo led

#define DEVICE  "esp32-1"                                // nombre dispositivo en ubidots
#define TOKEN  "BBFF-9K4rFJ4V24mFwJilEYTGHkYQbicJat"     // token BBFF-9K4rFJ4V24mFwJilEYTGHkYQbicJat
#define WIFISSID "ARKANO2020"                            // nombre red wifi
#define PASSWORD "Motoso201611"                          // clave del wifi
//Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);
Ubidots client(TOKEN);                                   //conecta a la direncion del token ubidots del cliente



void setup(void) {
client.wifiConnect(WIFISSID, PASSWORD);                  //inicia cliente ubidots
Serial.begin(115200);
Serial.print(" hola mundo \n");
pinMode(led, OUTPUT);
}
 
void loop(void) {
  int power = client.get(DEVICE, "led");
  digitalWrite(led, power);   // lleva a led el valor recogido en power de ubidots
  Serial.print(power);
  delay(1000);                       // espera 1 segundo
  digitalWrite(led, power);    // lleva a led el valor recogido en power de ubidots
  Serial.print(power);
  Serial.print("\n");
  delay(1000);      
 
}
