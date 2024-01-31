void NTP_Server() {
  struct tm timeinfo;

  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  lcd.setCursor(0, 0);
  lcd.print(&timeinfo, "--- %H:%M:%S ---");

  //Control auto pompa active HIGH
  if ((timeinfo.tm_hour == 7) && (timeinfo.tm_min == 0) && (timeinfo.tm_sec == 0)) {
    Serial.println("Pompa Menyala Otomatis");
    digitalWrite(pAuto, LOW);

  } else if ((timeinfo.tm_hour == 7) && (timeinfo.tm_min == 0) && (timeinfo.tm_sec == 10)) {
    Serial.println("Pompa Mati Otomatis");
    digitalWrite(pAuto, HIGH);

  } else if ((timeinfo.tm_hour == 16) && (timeinfo.tm_min == 0) && (timeinfo.tm_sec == 0)) {
    Serial.println("Pompa Menyala Otomatis");
    digitalWrite(pAuto, LOW);

  } else if ((timeinfo.tm_hour == 16) && (timeinfo.tm_min == 0) && (timeinfo.tm_sec == 10)) {
    Serial.println("Pompa Mati Otomatis");
    digitalWrite(pAuto, HIGH);
  }
  Serial.println();
}

void ntpBegin() {
  Serial.printf("Connecting to %s ", ssid);
  // WiFi.begin(ssid, password);
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  // }
  // Serial.println(" CONNECTED");

  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  NTP_Server();

  //disconnect WiFi as it's no longer needed
  // WiFi.disconnect(true);
  // WiFi.mode(WIFI_OFF);
}

void sensorDHT11() {
  int hum = dht.readHumidity();
  int temp = dht.readTemperature();

  if (isnan(hum) || isnan(temp)) {
    Serial.println("Gagal Membaca DHT sensor!");
    return;
  }
  Serial.println("Humidity: " + (String)hum + " %");
  Serial.println("Temperature: " + (String)temp + " " + (char)223 + "C");

  Blynk.virtualWrite(V0, hum);
  Blynk.virtualWrite(V1, temp);

  temperatur = temp;
  kelembapan = hum;

}

void sensorMoisture() {
  int moistureValue = analogRead(moisture);
  Serial.print("Moisture value: ");
  Serial.println(moistureValue);

  Blynk.virtualWrite(V2, moistureValue);
}

BLYNK_WRITE(V3) {
  int btn = param.asInt();
  Serial.print("BUTTON POMPA 1:");
  Serial.println(btn);
  if (btn == 1) digitalWrite(pManual1, LOW);
  if (btn == 0) digitalWrite(pManual1, HIGH);
}

BLYNK_WRITE(V4) {
  int btn = param.asInt();
  Serial.print("BUTTON POMPA 2:");
  Serial.println(btn);
  if (btn == 1) digitalWrite(pManual2, LOW);
  if (btn == 0) digitalWrite(pManual2, HIGH);
}

BLYNK_WRITE(V5) {
  int btn = param.asInt();
  Serial.print("BUTTON AUTO :");
  Serial.println(btn);
  if (btn == 1) digitalWrite(pAuto, LOW);
  if (btn == 0) digitalWrite(pAuto, HIGH);
}

void lcdVisual(){
  lcd.setCursor(0, 1);
  lcd.print("t: " + (String)temperatur +(char)223 + "C");

  lcd.setCursor(9, 1);
  lcd.print("h: " + (String)kelembapan + "%");
  delay(1000);

  lcd.setCursor(3, 1);
  lcd.print("      ");

  lcd.setCursor(11, 1);
  lcd.print("      ");
}
