
//#include "UbidotsMicroESP8266.h"
// Este archivo incluye una actualizacion de las librerias de Ubidots y observaras
// al conectarte a Ubidots que se crea otro dispostivo (Device) automaticamente
// tienes que configurar las etiquetas segun el nuevo dispositivo que se crea
// y adicionar la variable var_led  .... todo lo demás es identico 

#include "Ubidots.h"

#define DEVICE  "esp32_1"  // Put here your Ubidots device label
#define VARIABLE  "led_1"  // Put here your Ubidots variable label
#define ID_TEMP "61941c4998be4c38c29a7966" 
#define TOKEN  "BBFF-9K4rFJ4V24mFwJilEYTGHkYQbicJat"  // Put here your Ubidots TOKEN

#define WIFISSID "ARKANO2020" // Put here your Wi-Fi SSID
#define PASSWORD "Motoso201611" // Put here your Wi-Fi password

Ubidots client(TOKEN);
float Valor_Temperatura = 17;

void setup() {
    Serial.begin(115200); 
    
    //client.wifiConnection(WIFISSID, PASSWORD);
    
    client.wifiConnect(WIFISSID, PASSWORD);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, 23);
    //client.setDebug(true); // Uncomment this line to set DEBUG on
}

void loop() 
{
    float Valor_Led = client.get(DEVICE, VARIABLE);
    if (Valor_Led != ERROR_VALUE){
      Serial.print(F(">>>>>>>>> VALOR OBTENIDO POR EL LED: "));
      Serial.println(Valor_Led);
    }else{
      Serial.println(F("Error getting Valor_Led"));
    }

    if (Valor_Temperatura>100)Valor_Temperatura=0;
  
    Valor_Temperatura = Valor_Temperatura + 5 ;
    
    client.add(ID_TEMP, Valor_Temperatura); 
    client.send();
    delay(5000);
}
