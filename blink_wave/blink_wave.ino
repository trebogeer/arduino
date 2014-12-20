#define DEL 500

void setup() {
   for(byte i=2;i<7;i++) {
     pinMode(i, OUTPUT);
   }
}

void loop() {
  digitalWrite(2, HIGH);
  delay(DEL);
  byte i = 3;  
  for (;i<7;i++) {
     digitalWrite(i-1, LOW);
     digitalWrite(i, HIGH);
     delay(DEL);    
  }
  
  for (;i>2;i--) {
     digitalWrite(i, LOW);
     digitalWrite(i-1, HIGH);
     delay(DEL);
  }
  digitalWrite(i, LOW);
}
