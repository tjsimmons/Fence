#include <Arduino.h>
#include <ESP8266WiFi.h>

/*
TODO:
  On device initialization, run as a AP with web server
  Connect to device from a computer, and from a dropdown
  choose the SSID and enter the password of network ESP82666
  should connect to.

  Once configuration is complete, should be written to the device
  so that on subsequent boots, the device starts up in client mode
  and calls home to our web service for commands.
*/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(115200);
  Serial.println();

  WiFi.begin("SSID", "PASSWORD");
  Serial.print("Connecting");

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();

  digitalWrite(LED_BUILTIN, HIGH);
  Serial.print("Connected, IP address: " );
  Serial.println(WiFi.localIP());
}

void loop() { }
