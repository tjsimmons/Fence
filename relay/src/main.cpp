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
#include <ESP8266WiFi.h>
// #include <FS.h>
#include <Esp8266Configuration.h>
#include <ESP8266WebServer.h>

#include "softap.h"
#include "wifiscan.h"
#include "webserver.h"

void setup() {
        Serial.begin(115200);
        Serial.println();

// check Configuration for details
// if none exist, startServer
        startServer();
        // else join the network
}

void loop() {
        handleClient();
}
