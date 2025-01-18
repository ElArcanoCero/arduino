#include <WiFi.h>
#include <Ubidots.h>
#include <analogWrite.h>
#include <DHT.h>

#define PIN 32
#define DEVICE  "esp32"                                  // nombre dispositivo en ubidots
#define TOKEN  "BBFF-9K4rFJ4V24mFwJilEYTGHkYQbicJat"     // token BBFF-9K4rFJ4V24mFwJilEYTGHkYQbicJat
#define WIFISSID "ARKANO2020"                            // nombre red wifi
#define PASSWORD "Motoso201611"                          // clave del wifi

Ubidots client(TOKEN);                                   //conecta a la direncion del token ubidots del cliente

DHT dht(PIN, DHT11);                                     // crea objeto dht
                                         
const int trig = 19;                                     // pin 19 enviar señal utrasonic
const int eco = 23;                                      // pin 23 resive señal utrasonic
const int led = 2;                                       // brillo led
float temp = 0;                                          // variable temperatura
float hum = 0;                                           // variable humadad
float dist = 0;                                          // variable distancia
unsigned long tiem = 0;                                  // variable tiempo

 
void setup() {
    Serial.begin(115200);
    client.wifiConnect(WIFISSID, PASSWORD);              //inicia cliente ubidots
    dht.begin();                                         // inicializa el dht
    pinMode(trig, OUTPUT);                               // pin 19 dispara el sensor
    pinMode(eco, INPUT);                                 // pin 23 resibe pulso del sensonsor
  
}

void loop() 
{
    int  power = 2.55*(client.get(DEVICE, "led-1"));     // recoge el valor dispositivo esp32-1 variable led-1 asignado
    Serial.print(power);
    analogWrite(led, power);
    temp = dht.readTemperature();                        // leer temperatura en el sensor dht
    hum = dht.readHumidity();                            // leer humedad en el sensor dht
    digitalWrite(trig,HIGH);                             // inicia pulso alto en el sensor sonic
    delay(1);
    digitalWrite(trig,LOW);                              // detiene el pulso alto en el sensor sonic
    tiem = pulseIn(eco, HIGH);                           // mide la duracion del puso eco
    dist = tiem/(58.2);                                  // calcula distancia
    client.add("temperatura", temp);                     // envia datos a ubidots donde temperatura es el api lable de la variable y temp es un dato
    Serial.print(temp);
    Serial.print("/n");
    client.add("humedad", hum);                          // envia datos a ubidots donde humedad es el api lable de la variable y hum es un dato
    Serial.print(hum);
    Serial.print("/n");
    client.add("distancia", dist);                       // envia datos a ubidots donde distancia es el api lable de la variable y dist es un dato
    Serial.print("/n");
    client.send(DEVICE);                                 // agregar nobre del dispositivo en ubidots para que todo sea enviado a ese  
}
