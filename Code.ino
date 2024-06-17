#include <DHT.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

#define DHT11_PIN 5

// Soil Sensor input at Analog PIN A0
int sensor_pin = A0; 
int output_value;
int relayPin = 6;
// Temperature threshold in degrees Celsius
const int TEMP_THRESHOLD = 10; 
// Humidity threshold in percentage
const int HUMIDITY_THRESHOLD = 30; 
DHT dht(DHT11_PIN, DHT11);

float temperature; // Declare variable for temperature
float humidity;    // Declare variable for humidity

void setup() {
  lcd.begin(16, 2);
  pinMode(sensor_pin, INPUT);
  pinMode(relayPin, OUTPUT);
  dht.begin();
}

void loop() 
{
  // Read temperature from DHT11 sensor
  temperature = dht.readTemperature(); 
  // Read humidity from DHT11 sensor
  humidity = dht.readHumidity();       
  
  // Printing Temperature on display
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print((char)223);
  lcd.print("C / ");
  lcd.print(TEMP_THRESHOLD);
  lcd.print((char)223);
  lcd.print("C");

  // Printing humidity on display
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("% / ");
  lcd.print(HUMIDITY_THRESHOLD);
  lcd.print("%");
  delay(2000);

  lcd.setCursor(23, 0);
  lcd.autoscroll();
  output_value = analogRead(sensor_pin);
  output_value = map(output_value, 550, 10, 0, 100);
  lcd.print("Moisture: ");
  lcd.print(output_value);
  lcd.print("%");

  lcd.setCursor(23, 1);
  if (output_value < 30 && temperature > TEMP_THRESHOLD && humidity > HUMIDITY_THRESHOLD) 
  {
    // Set motor pump to high flow
    digitalWrite(relayPin, LOW);
    lcd.print("Motor ON");
  }
  else {
    digitalWrite(relayPin, HIGH);
    lcd.print("Motor OFF");
  }

  delay(2500);
  lcd.noAutoscroll();
  lcd.clear();
}
