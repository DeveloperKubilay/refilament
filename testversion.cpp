#define STEP 6
#define DIR 7

void setup()
{
   /* pinMode(STEP, OUTPUT);
    pinMode(DIR, OUTPUT);
    digitalWrite(DIR, HIGH);  // yön belirle
    */
    pinMode(A5, OUTPUT);
    digitalWrite(A5, HIGH);

}

void loop()
{
    /*
    digitalWrite(STEP, HIGH);
    delayMicroseconds(3000);  // daha hızlı (1000 adım/saniye)
    digitalWrite(STEP, LOW);
    delayMicroseconds(3000);
    */
}