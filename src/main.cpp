#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>

const char *ssid = "ESP32S3";
const char *password = "11111111";

IPAddress IP;

const byte DNS_PORT = 53;
DNSServer dnsServer;

AsyncWebServer server(80);

const char *homepageHTML = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}</style></head><body><h1>Hello World</h1></body></html>";

void setup()
{
    Serial.begin(9600);

    WiFi.softAP(ssid, password);

    IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    dnsServer.start(DNS_PORT, "*", IP);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/html", homepageHTML); });

    server.onNotFound([](AsyncWebServerRequest *request)
                      { request->send(404); });

    server.begin();
}

void loop()
{
    dnsServer.processNextRequest();
}