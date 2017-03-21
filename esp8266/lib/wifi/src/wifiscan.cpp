#include <ESP8266WiFi.h>
#include "wifiscan.h"


bool firstScan = true;

void displayNetworks(int numNetworks) {
        for (int i=0; i < numNetworks; i++) {
                Serial.println(WiFi.SSID(i));
        }

        Serial.println();
}

void runInLoop() {
        if (firstScan) {
                Serial.println("Beginning scan");
                WiFi.scanNetworks(true, true);
                firstScan = false;
        }

        int networksFound = WiFi.scanComplete();

        switch (networksFound) {
        case -2:
                Serial.println("Scan has not been started");
                break;
        case -1:
                Serial.println("Scan has not yet completed");
                break;
        default:
                Serial.printf("%d networks found\n", networksFound);
                displayNetworks(networksFound);
                WiFi.scanNetworks(true, true);
                break;
        }

        delay(5000);
}
