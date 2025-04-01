#include <Arduino.h>

// Definimos la tarea
TaskHandle_t Tarea1;

void setup() {
  Serial.begin(115200);
  
  xTaskCreatePinnedToCore(
    loop1,    // Función de la tarea
    "Tarea1", // Nombre de la tarea
    1000,     // Tamaño de la pila en bytes
    NULL,     // Parámetro de entrada
    1,        // Prioridad
    &Tarea1,  // Manejador de la tarea
    0         // Núcleo donde se ejecutará (0 o 1)
  );
}

void loop() {
  Serial.print("Ejecutando tarea 1 en núcleo: ");
  Serial.println(xPortGetCoreID()); // pide el id del nucleo en que se ejecuta
  delay(3000);
}

void loop1(void* parameter) {
  while (true) {
    Serial.print("ejecutando tarea 2 en núcleo: ");
    Serial.println(xPortGetCoreID());
    vTaskDelay(5000 / portTICK_PERIOD_MS); // Pequeña pausa para evitar sobrecarga
  }
}
