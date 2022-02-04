#define FIREBASE_HOST "xxxxxxxxx" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "xxxxxxxxx"
#define WIFI_SSID "xxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxx"
#include <Wire.h>
#include "SSD1306.h" 
#include "FirebaseESP32.h"
FirebaseData firebaseData;
SSD1306  display(0x3c, 21, 22);