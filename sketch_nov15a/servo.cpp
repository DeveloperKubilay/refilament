#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(9);
}

void loop() {
  // 0'dan 180'e tek tek art
  for (int i = 0; i <= 180; i++) {
    myServo.write(i);
    delay(20); // 20 ms bekle, hızı buradan ayarlayabilirsin
  }

  // 180'den 0'a geri
  for (int i = 180; i >= 0; i--) {
    myServo.write(i);
    delay(20);
  }
}
