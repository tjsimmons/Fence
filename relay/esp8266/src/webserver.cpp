#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <string.h>
#include "webserver.h"

using namespace std;

ESP8266WebServer server(80);
int numNetworks = 0;

void startServer() {
    delay(500);

    Serial.print("Starting up softAP...");
    Serial.println(WiFi.softAP("ESP8266") ? "Ready" : "Not Ready");

    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    server.on("/", handleRoot);
    server.on("/", HTTP_POST, handleSave);
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

void handleSave() {}

void handleClient() {
    server.handleClient();
}
