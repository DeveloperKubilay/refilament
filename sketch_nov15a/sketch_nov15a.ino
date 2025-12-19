int analogPin = A0;
int analogValue = 0;
float voltage = 0;
float temperatureC = 0;

// 100k NTC ve 100k sabit direnç
float R1 = 100000; // sabit direnç
float B = 3950;    // NTC B katsayısı
float R0 = 100000; // 25°C'deki NTC direnci

void setup() {
  Serial.begin(9600);
}

void loop() {
  analogValue = analogRead(analogPin);
  voltage = analogValue * (5.0 / 1023.0);

  // NTC direnci
  float Rntc = R1 * ((5.0 / voltage) - 1.0);
  
  // Sıcaklık hesaplama (Kelvin -> Celsius)
  temperatureC = 1.0 / ( (1.0 / (25.0 + 273.15)) + (1.0 / B) * log(Rntc / R0) ) - 273.15;

  Serial.print("Sicaklik: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  delay(1000);
}
