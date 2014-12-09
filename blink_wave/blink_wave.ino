void setup() {
   for(byte i=2;i<7;i++) {
     pinMode(i, OUTPUT);
   }
}

void loop() {
  int del = 500;
  digitalWrite(2, HIGH);
  delay(del);
  byte i = 3;  
  for (;i<7;i++) {
     digitalWrite(i-1, LOW);
     digitalWrite(i, HIGH);
     delay(del);    
  }
  
  for (;i>2;i--) {
     digitalWrite(i, LOW);
     digitalWrite(i-1, HIGH);
     delay(del);
  }
  digitalWrite(i, LOW);
}
