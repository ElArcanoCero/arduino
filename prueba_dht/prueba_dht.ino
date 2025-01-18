#include <TinyDHT.h>             // libreria sensor HDT
#define DHTPIN 7                // enstrada de datos del sensor dht
#define DHTTYPE DHT11            // serie del sensor especifico
DHT dht(DHTPIN, DHTTYPE);        // crea objeto para el DHT11

#define DHT 7    
float temp = 0;
float hum = 0;

void setup() {
   Serial.begin(115200);                               //inicia monitor serial
   dht.begin();                                        // inicializa el dht
   pinMode(DHT, INPUT);                                // Pin 13 entrada sensor dht
   

}

void loop() {
    temp = dht.readTemperature();                       // leer temperatura en el sensor dht
    hum = dht.readHumidity();                           // leer humedad en el sensor dht
    Serial.print(F("humedad : "));
    Serial.println(hum);
    Serial.print(F("temperatura : "));
    Serial.println(temp);

}
