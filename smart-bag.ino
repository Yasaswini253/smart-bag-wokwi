#include <Servo.h>
#include <DHT.h>

#define DHTPIN 2      // DHT22 data pin
#define DHTTYPE DHT22 // Define sensor type

DHT dht(DHTPIN, DHTTYPE);
Servo servo1;
Servo servo2;

const int rainPin = A0;
const int rainThreshold = 500;

void setup() {
  Serial.begin(9600);
  dht.begin();
  servo1.attach(9);
  servo2.attach(10);
}

void loop() {
  int rainValue = analogRead(rainPin);
  float temperature = dht.readTemperature(); // Celsius
  float humidity = dht.readHumidity();

  // Display values
  Serial.print("Rain: ");
  Serial.print(rainValue);
  Serial.print(" | Temp: ");
  Serial.print(temperature);
  Serial.print(" °C | Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Umbrella control
  if (rainValue < rainThreshold) {
    servo1.write(90);  // Open
    servo2.write(90);
  } else {
    servo1.write(0);   // Close
    servo2.write(0);
  }

  delay(1000); // 1-second delay
}
