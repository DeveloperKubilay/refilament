#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Stepper.h>
#include <math.h>

LiquidCrystal lcd(8, 9, 13, 12, 11, 10);
// Pinler: IN1->4, IN2->3, IN3->2, IN4->A5
Stepper myStepper(2048, 5, 4, 3, 2);

#define STEP 6
#define DIR 7

bool running = false;

void setup()
{
    lcd.begin(16, 2);

    pinMode(STEP, OUTPUT);
    pinMode(DIR, OUTPUT);
    pinMode(A5, OUTPUT);
    pinMode(A4, INPUT_PULLUP);

    digitalWrite(DIR, HIGH);
    digitalWrite(A5, HIGH);

    myStepper.setSpeed(10);
}

void loop()
{
    static unsigned long lastTime = 0;
    static float lastTemperatureC = NAN;

    if (millis() - lastTime >= 1000)
    {
        lastTime = millis();
        int rawValue = analogRead(A0);
        float voltage = rawValue * (5.0 / 1023.0);

        // NTC GND'ye, 100k Direnç 5V'a bağlı (Standart)
        if (voltage > 4.9)
            voltage = 4.9;
        if (voltage < 0.1)
            voltage = 0.1;

        float Rntc = 100000.0 * (5.0 - voltage) / voltage;
        lastTemperatureC = 1.0 / ((1.0 / (25.0 + 273.15)) + (log(Rntc / 100000.0) / 3950.0)) - 273.15;

        digitalWrite(A5, (!isnan(lastTemperatureC) && lastTemperatureC >= 100.0) ? LOW : HIGH);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Sicaklik:");
        lcd.setCursor(0, 1);
        lcd.print(lastTemperatureC);
        lcd.print(" C");
        myStepper.step(4);
    }

    if ((digitalRead(A4) == LOW) && !isnan(lastTemperatureC) && (lastTemperatureC > 60))
    {
        // gerekirse 200ms yapılabilir
        digitalWrite(STEP, HIGH);
        delayMicroseconds(500);
        digitalWrite(STEP, LOW);
        delayMicroseconds(500);
    }
    else
    {
        digitalWrite(STEP, LOW);
    }
}
