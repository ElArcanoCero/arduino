int ledPins[] = {2, 3, 4, 5}; // Pines de los 4 LEDs
int currentLed = 0; // LED actual que está encendido

int ledPin = 9; // Pin de la cinta LED
int brightness = 0; // Variable para almacenar el brillo actual

void setup() {
 
  Serial.begin(9600);

  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT); // Configura los pines de los LEDs como salidas digitales
    digitalWrite(ledPins[i], LOW); // Apaga todos los LEDs
  }
   
  pinMode(ledPin, OUTPUT); // Configura el pin de la cinta LED como salida digital
  analogWrite(ledPin, brightness); // Establece el brillo inicial en 0
  
  Serial.println("listo para conectar");
}

void loop() {
  if (Serial.available()) {
      char x = (char)Serial.read();
      if ( x == 'a')
      {
        Led_n = 0
        Serial.print(x);
        Serial.print("\n");
        }
      
      if ( x == 'b')
      {
        Led_n = 1
        Serial.print(x);
        Serial.print("\n");
        }
      
      if ( x == 'c')
      {
        Led_n = 2
        Serial.print(x);
        Serial.print("\n");
        }
  
      if ( x == 'd')
      {
        Led_n = 3
        Serial.print(x);
        Serial.print("\n");
        }
   }
    digitalWrite(ledPins[Led_n], HIGH); // Enciende el LED actual
  }
