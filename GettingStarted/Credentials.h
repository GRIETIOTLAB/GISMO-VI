#define FIREBASE_HOST "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" 
#define FIREBASE_AUTH "xxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define WIFI_SSID "xxxxxxxxxxxx"
#define WIFI_PASSWORD "xxxxxxxxxx"
#include <Wire.h>
#include "SSD1306.h" 
#include "FirebaseESP32.h"
FirebaseData firebaseData;
SSD1306  display(0x3c, 21, 22);