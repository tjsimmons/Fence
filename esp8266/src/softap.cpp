#include <ESP8266WiFi.h>

void bsetup() {
        Serial.begin(115200);
        Serial.println();

        Serial.print("Starting up softAP...");
        Serial.println(WiFi.softAP("ESP8266") ? "Ready" : "Not Ready");
}

void lboop() {
        Serial.printf("Clients connected: %d\n", WiFi.softAPgetStationNum());
        delay(5000);
}
