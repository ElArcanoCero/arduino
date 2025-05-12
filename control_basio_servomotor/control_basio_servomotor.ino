#include <Servo.h>
Servo miServo; // libreria del servo motor

int angulo = 0; //variable de control para el angulo

void setup() {
  miServo.attach(9); // Conectado al pin D9 del Nano
}

void loop() {
  for (int angulo = 0; angulo <= 180; angulo++) { //primer ciclo for para mover el servo de 0 a 180
    miServo.write(angulo); // controla la posicion del servo moviendolo un grado cada vez
    delay(15);
  }

  delay(1000);

  for (int angulo = 180; angulo >= 0; angulo--) { // segundo ciclo for para mover de 180 a 0
    miServo.write(angulo);
    delay(15);
  }

  delay(1000);
}
