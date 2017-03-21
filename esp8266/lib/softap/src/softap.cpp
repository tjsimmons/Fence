#include <ESP8266WiFi.h>
#include "softap.h"

void startSoftAP() {
        Serial.print("Starting up softAP...");
        Serial.println(WiFi.softAP("ESP8266") ? "Ready" : "Not Ready");
}

// void aloop() {
//         Serial.printf("Clients connected: %d\n", WiFi.softAPgetStationNum());
//         delay(5000);
// }
