#define FIREBASE_HOST "radsproject.firebaseio.com" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "4niCZOkFw4C2WVZf04gk9PrQx9isMG7NbCva9CmU"
#define WIFI_SSID "IOTLAB"
#define WIFI_PASSWORD "Rabindranath@Tagore1234#"
#include <Wire.h>
#include "SSD1306.h" 
#include "FirebaseESP32.h"
FirebaseData firebaseData;
SSD1306  display(0x3c, 21, 22);
