#include <Arduino.h>

// Definimos la tarea
TaskHandle_t Tarea1;

void setup() {
  Serial.begin(115200);
  
  xTaskCreatePinnedToCore(
    loop1,    // Función de la tarea
    "Tarea1", // Nombre de la tarea
    2000,     // Tamaño de la pila en bytes (ram) valor maximo de la ram para ambas tareas 32kb
    NULL,     // Parámetro de entrada
    1,        // Prioridad
    &Tarea1,  // Manejador de la tarea
    0         // Núcleo donde se ejecutará (0 o 1)
  );
}

void loop() {
  Serial.print("Ejecutando tarea 1 en núcleo: ");
  Serial.println(xPortGetCoreID()); // pide el id del nucleo en que se ejecuta
  Serial.print("Memoria libre en pila 1: ");//pide la memoria restante de la pila para esta tarea se asignaron 8192 bytes por defecto
  Serial.println(uxTaskGetStackHighWaterMark(NULL)); 
  delay(3000);
}

void loop1(void* parameter) {
  while (true) {
    Serial.print("ejecutando tarea 2 en núcleo: ");
    Serial.println(xPortGetCoreID());// pide el id del nucleo en que se ejecuta
    Serial.print("Memoria libre en pila 2: ");
    Serial.println(uxTaskGetStackHighWaterMark(Tarea1));//pide la memoria restante de la pila para esta tarea se asignaron 2000 bytes
    vTaskDelay(5000 / portTICK_PERIOD_MS); // Pequeña pausa para evitar sobrecarga
  }
}
