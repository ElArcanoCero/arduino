// Proyecto Bola y Barra

//Librerías servo y sensor láser
#include <Servo.h>
#include "Adafruit_VL53L0X.h"


// Ganancias PID;
double Kp = 0, Ki = 0, Kd = 0;

// Variable posición y posición deseada
int pos = 0;
int setPoint = 12;

// Variables PID
unsigned long currentTime, previousTime;
double elapsedTime;
double error, lastError, cumError, rateError;
double outPut;

// Distacias medidas
float dis;
float dis_cm;

// Se define el servo y el sensor
Servo myservo;
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200); // Inicio comunicación serial

// Se inicia el sensor láser
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }
// Pin donde está conectado el servo
  myservo.attach(13);

}

void loop() {
// Se obtiene la distancia del sensor
  dis = distancia();
// Se asigna la posición del servomotor en grados 
  pos = PID(dis) + 95;
// Se limita el valor de la posición del servo para
// que no exceda los límites
  limite();
//Se manda la posición al servomotor
  myservo.write(pos);

// Se imprimen los valores para graficar en el serial plotter
  Serial.print(setPoint);
  Serial.print(" ");
  Serial.println(dis);
  delay(10);
}

float distancia()
{
  // Se crea un objeto measure
  VL53L0X_RangingMeasurementData_t measure;
 // Test de rango
  lox.rangingTest(&measure, false);
 // Se crea una condición para el rango del sensor
  if (measure.RangeStatus != 4) {
    // Cuando se esté en el rango medible se obtiene la distancia
    // del sensor en milímetros
    float dis_mm = measure.RangeMilliMeter;
    // Se convierte la distancia a cm
    dis_cm = dis_mm / 10;
  } else {
    // Si está fuera de rango que se imprima un mensaje
    Serial.println(" Fuera de rango ");
  }
  // Se regresa la distancia en centímetros
  return dis_cm;
}

void limite(void)
{ 
  // Si la posición se pasa de 130 que se mantenga en 130
  if (pos > 130)
  {
    pos = 130;
  }
  // Si la posición es menos de 60 que se mandenga en 60
  if (pos < 60)
  {
    pos = 60;
  }
}
double PID(float input)
{ 
  // Se guarda el tempo actual 
  currentTime = millis();
  // Se calcula el tiempo transcurrido
  elapsedTime = currentTime - previousTime;

  // Se obtiene el error de posición
  error = setPoint - input;
  // Se calcula la integral del error
  cumError += error * elapsedTime;
  // Se calcula la derivada del error
  rateError = (error - lastError) / elapsedTime;
  // Se calcula la salida del controlador
  outPut = Kp * error + Ki * cumError + Kd * rateError;

  // El error actual se convierte en el error pasado
  lastError = error;
  // El tiempo actual se convierte en el tiempo pasado
  previousTime = currentTime;

  // Se regresa la salida del controlador
  return outPut;
}
