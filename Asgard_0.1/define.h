//pin
#define DHTPIN 4
#define moisture 26
#define pAuto 25
#define pManual1 32
#define pManual2 27

//config
#define DHTTYPE DHT11

//Blynk Firmware Config
#define BLYNK_TEMPLATE_ID "TMPL6Q8GUk2xe"
#define BLYNK_TEMPLATE_NAME "Asgard"
#define BLYNK_AUTH_TOKEN "UKZukFePCRHhxyYHWsFg4z9CEbYVtC5Q"
#define BLYNK_PRINT Serial

///Wifi ESP32 & NTP Config
const char* ssid                  = "admin1";
const char* password              = "12345678";

const char* ntpServer             = "pool.ntp.org";
const long  gmtOffset_sec         = 6 * 3600;
const int   daylightOffset_sec    = 3600;

int temperatur;
int kelembapan;

