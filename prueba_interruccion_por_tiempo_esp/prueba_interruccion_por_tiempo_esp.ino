int contador1;
int contador2;
 
hw_timer_t * timer = NULL;

 
void IRAM_ATTR contador() { 
  Serial.print("interruccion numero  : ");
  Serial.println(contador1);
  contador1++;
  Serial.print("blucle principal numero  : ");
  Serial.println(contador2);
}
 
void setup() {
 
  Serial.begin(115200);
 
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &contador, true);
  timerAlarmWrite(timer, 1000000, true);          // poner el tiempo en millonesimas de segundo
  timerAlarmEnable(timer);
 
}
 
void loop() {
  
  delay(10000);
  contador2++;
  contador1= 0;
  Serial.println("paso \n");
}
