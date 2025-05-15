#define dhttype DHT11
#define pinDHT 7
#define trigger 6
#define echo 5
#include <DHT.h>
#include <ArduinoJson.h>

int dist = 0;

DHT dht(pinDHT, dhttype);
StaticJsonDocument<100> json;


void setup() {
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  dht.begin();

}

void loop() {
  digitalWrite(trigger, HIGH);
  delayMicroseconds(2000);
  digitalWrite(trigger, LOW);

  dist = pulseIn(echo, HIGH);
  dist = dist / 58;

  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();

  json["DistanciaAtual"] = dist;
  json["Temperatura"] = temperatura;
  json["Umidade"] = umidade;

  serializeJson(json, Serial);
  Serial.println();
  delay(500);
}
