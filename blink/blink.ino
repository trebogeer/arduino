// Blink LED Sketch

void setup() {
   pinMode(13, OUTPUT); //set digital output to 13
}

void loop() {
   digitalWrite(13, HIGH);
   delay(100);
   digitalWrite(13, LOW);
   delay(100);
   for (byte i = 0;i < 2;i++) { 
      digitalWrite(13, HIGH);
      delay(1000);
      digitalWrite(13, LOW);
      delay(1000); 
   }
}
