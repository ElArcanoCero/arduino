#include <ESP32Servo.h>               // libreria servo
#include <Arduino.h>

// Definimos la tarea
TaskHandle_t Tarea1;

int PULSOMIN = 550;                    // pulso minimo en milisegundos
int PULSOMAX = 2500;                   // pulso maximo en milisegundos

int PINSERVO1 = 26;                    // pin control servo
Servo servo1;                          // creo objeto servo
 
int PINSERVO2 = 27;                    // pin control servo
Servo servo2;   

void setup() {
  servo1.attach(PINSERVO1, PULSOMIN, PULSOMAX); // inicializa el servo
  servo2.attach(PINSERVO2, PULSOMIN, PULSOMAX); // inicializa el servo

  Serial.begin(115200);

  xTaskCreatePinnedToCore(
    loop1,       // Función de la tarea
    "Tarea1",    // Nombre de la tarea
    2000,        // Tamaño de la pila en words (4 bytes) (ram) valor maximo de la ram para ambas tareas 32kb
    NULL,        // Parámetro de entrada
    1,           // Prioridad
    &Tarea1,     // Manejador de la tarea
    0            // Núcleo donde se ejecutará (0 o 1)
    // 📌 Comentario GPT: 2000 * 4 = 8KB, está bien para tareas simples como esta
  );
}

void loop() {
  //servo1 Core 0
  servo1.write(0);
  delay(5000);
  servo1.write(180);              // ubica el servo en la dirección
  delay(200);
  servo1.write(0);
  delay(5000);
  servo1.write(180);              // ubica el servo en la dirección
  delay(200);
  servo1.write(0);              // ubica el servo en la dirección
  delay(200);
  servo1.write(180);              // ubica el servo en la dirección
  delay(200);
  servo1.write(0);              // ubica el servo en la dirección
  delay(200);

 
}

void loop1(void* parameter) {
  while (true) {
    //servo 2 core 0
    servo2.write(0);
    vTaskDelay(8000 / portTICK_PERIOD_MS); // se debe convertir milisegundos a ticks del sistema
    servo2.write(180);              // ubica el servo en la dirección
    vTaskDelay(200 / portTICK_PERIOD_MS);
    servo2.write(0);
    vTaskDelay(4000 / portTICK_PERIOD_MS);
    servo2.write(180);              // ubica el servo en la dirección
    vTaskDelay(200 / portTICK_PERIOD_MS);
    servo2.write(0);              // ubica el servo en la dirección
    vTaskDelay(200 / portTICK_PERIOD_MS);
    servo2.write(180);              // ubica el servo en la dirección
    vTaskDelay(200 / portTICK_PERIOD_MS);
    servo2.write(0);              // ubica el servo en la dirección
    vTaskDelay(200 / portTICK_PERIOD_MS);

    
  }
}
