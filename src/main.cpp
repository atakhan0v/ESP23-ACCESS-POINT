#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "atakhanov";
const char* password = "newDIYAR";

const int ledPin = 2; // Pin connected to the LED

WebServer server(80); // Create a web server listening on port 80

void handleRoot() {
  // HTML-страница с кнопками для управления светодиодом
  String html = "<!DOCTYPE html><html><head><title>LED Control</title>";
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  html += "</head><body><h1>LED Control</h1>";
  html += "<img src=\"/https://y2y.hu/storage/gallery/images/2020/03/27/vnJ5odoKN6Mu4aVQOFHmXvwe0zty6Vukz30k2iav.jpeg\" alt=\"ESP32 Image\"><br>";
  html += "<form action=\"/on\" method=\"get\"><button>LED ON</button></form><br>";
  html += "<form action=\"/off\" method=\"get\"><button>LED OFF</button></form>";
  html += "</body></html>";
  

  server.send(200, "text/html", html);
}

void handleOn() {
  digitalWrite(ledPin, HIGH); // Turn the LED on
  handleRoot(); // Refresh the root page to reflect the new LED state
}

void handleOff() {
  digitalWrite(ledPin, LOW); // Turn the LED off
  handleRoot(); // Refresh the root page to reflect the new LED state
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  
  // Set up ESP32 as an access point
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Define server endpoints
  server.on("/", HTTP_GET, handleRoot);
  server.on("/on", HTTP_GET, handleOn);
  server.on("/off", HTTP_GET, handleOff);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}