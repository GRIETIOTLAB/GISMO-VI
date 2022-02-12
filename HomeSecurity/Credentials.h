#define FIREBASE_HOST "xxxxxxxxxxx" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "xxxxxxxxxxxx"
#define WIFI_SSID "xxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxxxxx"
#include <Wire.h>
#include "SSD1306.h" 
#include "FirebaseESP32.h"
FirebaseData firebaseData;
SSD1306  display(0x3c, 21, 22);
