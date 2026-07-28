#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Stepper.h>
#include <math.h>

LiquidCrystal lcd(8, 9, A2, 12, 11, 10);

// myStepper (28BYJ-48) Pin Bağlantıları:
// IN1 -> 5, IN2 -> 4, IN3 -> 3, IN4 -> 2
// (Eski kodda IN4 -> A5 yazılmıştı ancak A5 mosfet için kullanılıyor, o yüzden IN4'ü 2'ye bağlamalısın)
Stepper myStepper(2048, 5, 3, 4, 2);

#define STEP 6
#define DIR 7

// İstenilen hedef sıcaklık (Santigrat / Celsius cinsinden buraya yazabilirsin)
int hedefSicaklik = 100;

// Mosfetin açık olup olmadığını takip etmek için bir değişken
bool isHeaterOn = false;

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
    unsigned long currentTime = millis();
    bool btnPressed = (digitalRead(A4) == LOW);

    if (currentTime - lastTime >= 1000)
    {
        lastTime = currentTime;

        int rawValue = analogRead(A0);
        int rawValue2 = analogRead(A1);
        float voltage = rawValue2 * (5.0 / 1023.0);

        // NTC Sıcaklık Ölçümü (5V dalgalanmasından bağımsız, doğrudan ADC oranıyla)
        if (rawValue > 0 && rawValue < 1023)
        {
            float Rntc = 100000.0 * (1023.0 - rawValue) / (float)rawValue;
            // 25 derece = 298.15 Kelvin
            lastTemperatureC = 1.0 / ((1.0 / 298.15) + (log(Rntc / 100000.0) / 3950.0)) - 273.15;
        }

        // Isıtıcı (Mosfet) Kontrolü:
        // Sıcaklık ayarladığın "hedefSicaklik" değerinden KÜÇÜKSE mosfet açılır ve ısıtır.
        isHeaterOn = (!isnan(lastTemperatureC) && lastTemperatureC < hedefSicaklik);
        digitalWrite(A5, isHeaterOn ? LOW : HIGH);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Sicaklik:");
        lcd.print(lastTemperatureC, 1);
        lcd.print(" C");

        lcd.setCursor(0, 1);
        lcd.print(btnPressed ? "Buton: Acik " : "Buton: Kapali ");
        lcd.print(voltage, 2);
        lcd.print("V");

        myStepper.step(10); // Motoru çalıştırmak için bu satırı açabilirsin (Şu an yorum satırında)
    }

    // 2. Step Motor (NEMA) Kontrolü
    // Butona basılmışsa VE Isıtıcı (Mosfet) KAPALIYSA çalışır (Amper yetmeme sorununu çözer)
    if (btnPressed && !isHeaterOn)
    {
        digitalWrite(STEP, HIGH);
        delayMicroseconds(5);
        digitalWrite(STEP, LOW);
        delayMicroseconds(1000);
    }
    else
    {
        digitalWrite(STEP, LOW);
    }
}
