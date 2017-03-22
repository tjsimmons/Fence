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

using namespace std;

void startServer();
void handleRoot();
void handleSave();

Esp8266Configuration configuration;
ESP8266WebServer     server(80);

int  numNetworks = 0;
bool configured;

void setup() {
    Serial.begin(115200);
    Serial.println();

    // check Configuration for details
    configuration.read();

    // if none exist, startServer
    if (!configuration.isWifiStationConfigurationValid()) {
        Serial.println("Wifi configuration is invalid; starting server to prompt for details");
        configured = false;
        startServer();
    } else {
        Serial.printf("Connecting to %s\n", configuration.getWifiStationSsid());

        // else join the network
        WiFi.mode(WIFI_STA);
        WiFi.enableSTA(true);
        WiFi.begin(configuration.getWifiStationSsid(), configuration.getWifiStationPassword());

        while (WiFi.status() != WL_CONNECTED) {
            delay(500);

            Serial.print(".");
        }

        Serial.println("");
        Serial.println("WiFi connected");
        Serial.print("IP address: ");
        Serial.print(WiFi.localIP());
        Serial.println();
    }
}

void loop() {
    if (!configured) {
        server.handleClient();
    } else {}
}

void startServer() {
    WiFi.mode(WIFI_AP);

    delay(500);

    Serial.print("Starting up softAP...");
    Serial.println(WiFi.softAP("ESP8266") ? "Ready" : "Not Ready");

    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    server.on("/",     handleRoot);
    server.on("/save", HTTP_POST, handleSave);
    server.begin();
    Serial.println("HTTP server started");
}

/* Just a little test message.Go to http:   //192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
    // scan for networks
    numNetworks = WiFi.scanNetworks(false, true);
    Serial.printf("%d networks found\n", numNetworks);

    String form1 = "<!DOCTYPE html>"
                   "<html>"
                   "<head>"
                   "<title>Pikaboo Network Connection</title>"
                   "</head>"
                   "<body>"
                   "<form action='/save' method='post'>"
                   "<select name='ssid'>";

    String form2 = "</select>"
                   "<br />"
                   "<input type='text' name='password'>"
                   "<br />"
                   "<input type='submit' />"
                   "</form>"
                   "</body>"
                   "</html>";

    for (int i = 0; i < numNetworks; i++) {
        String ssid = "<option value='" + WiFi.SSID(i) + "'>" + WiFi.SSID(i) + "</option>";

        form1 = form1 + ssid;
    }

    server.send(200, "text/html", form1 + form2);
}

void handleSave() {
    if (server.hasArg("ssid") && server.hasArg("password")) {
        String pSSID     = server.arg("ssid");
        String pPassword = server.arg("password");

        Serial.println(pSSID);
        Serial.println(pPassword);

        char *ssid = new char[pSSID.length()];
        strcpy(ssid, pSSID.c_str());

        Serial.println(ssid);

        char *password = new char[pPassword.length()];
        strcpy(password, pPassword.c_str());

        Serial.println(password);

        configuration.setWifiStationSsid(ssid);
        configuration.setWifiStationPassword(password);
        configuration.write();

        Serial.println("Configuration set");

        server.send(200, "text/html", "OK");
    }
}
