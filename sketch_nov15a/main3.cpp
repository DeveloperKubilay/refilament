#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 13, 12, 11, 10);

#define STEP_PIN 6
#define DIR_PIN 7

void setup()
{
    lcd.begin(16, 2);
    pinMode(STEP_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);
    digitalWrite(DIR_PIN, HIGH);
}

void loop()
{
    float voltage = analogRead(A0) * (5.0 / 1023.0);
    float temperatureC = 0;
    float Rntc = 100000 * ((5.0 / voltage) - 1.0);
    temperatureC = 1.0 / ((1.0 / (25.0 + 273.15)) + (1.0 / 3950) * log(Rntc / 100000)) - 273.15;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sicaklik:");
    lcd.setCursor(0, 1);
    lcd.print(temperatureC);
    lcd.print(" C");

    digitalWrite(DIR_PIN, HIGH);
    for (int i = 0; i < 2000; i++)
    { // adım sayısı
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(800); // hız (küçük = hızlı)
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(800);
    }

    delay(1000);
}
