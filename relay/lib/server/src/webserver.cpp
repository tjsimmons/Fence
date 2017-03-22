#include <ESP8266WebServer.h>
#include "webserver.h"

#include "softap.h"
#include "wifiscan.h"

ESP8266WebServer server(80);

void startServer() {
        delay(500);

        startSoftAP();

        IPAddress myIP = WiFi.softAPIP();
        Serial.print("AP IP address: ");
        Serial.println(myIP);
        server.on("/", handleRoot);
        server.begin();
        Serial.println("HTTP server started");
}

/* Just a little test message.Go to http:   //192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
        server.send(200, "text/html", "<h1>You are connected</h1>");
}

void handleClient() {
        server.handleClient();
}
