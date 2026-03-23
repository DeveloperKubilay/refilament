#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Stepper.h>

LiquidCrystal lcd(8, 9, 13, 12, 11, 10);
Stepper myStepper(2048, 5, 4, 3, 2);

void setup()
{
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("LCD Acik");
    lcd.setCursor(0, 1);
    lcd.print("Step Testi");

    myStepper.setSpeed(10);
}

void loop()
{
    myStepper.step(4);
    delay(50);
}
