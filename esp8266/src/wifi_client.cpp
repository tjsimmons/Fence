#include <ESP8266WiFi.h>

void asetup() {
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

void aloop() {
}
