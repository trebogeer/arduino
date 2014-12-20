// PWM

int d = 5;

void setup() {
  pinMode(3, OUTPUT);
}

void loop() {
  int i = 0;
  for (;i<256;i++) {
     analogWrite(3, i);
     delay(d);
  }
  for (;i>0;i--) {
      analogWrite(3, i);
      delay(d);
  }
}
