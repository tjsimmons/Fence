#include <ESP8266WiFi.h>

/*
   https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/readme.md#quick-start
   https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/soft-access-point-examples.md
   https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/WiFiAccessPoint/WiFiAccessPoint.ino
   https://github.com/esp8266/Arduino/blob/master/doc/filesystem.md
   TODO:
   On device initialization, run as a softAP with web server
   Connect to device from a computer, and from a dropdown
   choose the SSID and enter the password of network ESP82666
   should connect to.

   Once configuration is complete, should be written to the device
   so that on subsequent boots, the device starts up in client mode
   and calls home to our web service for commands.
 */

void displayNetworks(int numNetworks);

bool firstScan = true;

void setup() {
        Serial.begin(115200);
        Serial.println();
}

void loop() {
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

void displayNetworks(int numNetworks) {
        for (int i=0; i < numNetworks; i++) {
                Serial.println(WiFi.SSID(i));

        }
}
