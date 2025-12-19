#include <LiquidCrystal.h>
#include <Stepper.h>

LiquidCrystal lcd(8, 9, 13, 12, 11, 10);

const int stepsPerRevolution = 2048;
// Pinler: IN1->4, IN2->3, IN3->2, IN4->A5
Stepper myStepper(stepsPerRevolution, 5, 4, 3, 2);

#define STEP 6
#define DIR 7

void setup()
{
    lcd.begin(16, 2);

    pinMode(STEP, OUTPUT);
    pinMode(DIR, OUTPUT);
    pinMode(A5, OUTPUT);

    digitalWrite(DIR, HIGH);

    myStepper.setSpeed(10);
}

void loop()
{
    static unsigned long lastTime = 0;

    if (millis() - lastTime >= 1000)
    {
        lastTime = millis();
        float voltage = analogRead(A0) * (5.0 / 1023.0);
        float Rntc = 100000 * ((5.0 / voltage) - 1.0);
        float temperatureC = 1.0 / ((1.0 / (25.0 + 273.15)) + (1.0 / 3950) * log(Rntc / 100000)) - 273.15;

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Sicaklik:");
        lcd.setCursor(0, 1);
        lcd.print(temperatureC);
        lcd.print(" C");
    }

    static unsigned long lastStepperTime = 0;
    if (millis() - lastStepperTime >= 5)
    {
        lastStepperTime = millis();
        myStepper.step(1);
    }
    /*
        digitalWrite(STEP, HIGH);
        delayMicroseconds(3000);
        digitalWrite(STEP, LOW);
        delayMicroseconds(3000);

        */

    static unsigned long lastA5Toggle = 0;
    static bool a5State = false;
    if (millis() - lastA5Toggle >= 2000)
    {
        lastA5Toggle = millis();
        a5State = !a5State;
        digitalWrite(A5, a5State ? HIGH : LOW);
    }

    
}
