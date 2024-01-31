#include "library.h"  
#include <BlynkSimpleEsp32.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

#define BLYNK_TEMPLATE_ID "TMPL6Q8GUk2xe"
#define BLYNK_TEMPLATE_NAME "Asgard"
#define BLYNK_AUTH_TOKEN "UKZukFePCRHhxyYHWsFg4z9CEbYVtC5Q"
#define BLYNK_PRINT Serial
char auth[] = BLYNK_AUTH_TOKEN;
BlynkTimer timer;

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, "admin1", "12345678", "blynk.cloud", 80);
  dht.begin();
  ntpBegin();

  lcd.init();
  lcd.backlight();

  //pinMode
  pinMode(moisture, INPUT);
  pinMode(pAuto, OUTPUT);
  pinMode(pManual1, OUTPUT);
  pinMode(pManual2, OUTPUT);

  //interval Blynk
  timer.setInterval(1000L, sensorDHT11);
  timer.setInterval(1000L, sensorMoisture);
}

void loop() {
  Blynk.run();
  timer.run();
  NTP_Server();
  lcdVisual();
}
