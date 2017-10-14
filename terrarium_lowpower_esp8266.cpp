// #include "terrarium.h"
// #include "datetime.h"
// #include "screen.h"
//
// #include <ESP8266WiFi.h>
// #include <ESP8266WebServer.h>
// #include <ESP8266HTTPClient.h>
// #include <TimeLib.h>
//
// const char* ssid     = "ESPap";
// const char* password = "thereisnospoon";
//
// //const char* ssid     = "Broceliande";
// //const char* password = "avalonisinbroceliande";
// //const char* ssid     = "Atalante";
// //const char* password = "jeanvigotetlescamelots";
// //const char* host       = "data.sparkfun.com";
// //const char* streamId   = "....................";
// //const char* privateKey = "....................";
//
// ESP8266WebServer server(80);
// DateTime timeupdater;
// SunSetTime sunsettimeupdater(45.1855779, 5.6996643);
// Terrarium terrarium;
// Screen screen;
//
//
// void setup_screen() {
//   Serial.begin(115200);
//   delay(10);
//
//   // We start by connecting to a WiFi network
//   Serial.print("Connecting to ");
//   Serial.print(ssid);
//
//   // Start WiFi connection
//   // WiFi.begin(ssid, password);
//   WiFi.begin(ssid, password);
//
//   // time_setup();
//
//   // Start HTTP Server
//   server.on("/", handleRoot);
//   server.begin();
//
//   // Wait for WiFi to be OK.
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.print(" WiFi connected, ");
//   Serial.print("IP address: ");
//   Serial.println(WiFi.localIP());
//
//   Serial.println("HTTP server started");
//   Serial.println();
//
//   // timeupdater.forceUpdate();
//   // terrarium.detectDS18B20();
//
//
//   // Force the ESP into client-only mode
//   WiFi.mode(WIFI_STA);
// }
//
// String getHttp() {
//   HTTPClient http;
//   String url = "http://192.168.4.1/";
//   http.begin(url);
//
//   int httpCode = http.GET();
//   // httpCode will be negative on error
//   if (httpCode < 0) {
//     Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
//     return "error";
//   }
//
//   String payload = http.getString();
//   // Serial.println(payload);
//   return payload;
// }
// void loop_screen() {
//   Serial.println("loop");
//   // WiFi.forceSleepWake();
//   server.handleClient();
//   screen.update();
//   // time_loop();
//
//   // terra_loop(isDay());
//   Serial.println(getHttp());
//
//   // WiFi.forceSleepBegin();
//   WiFi.setSleepMode(WIFI_LIGHT_SLEEP);
//   delay(100);
// }
//
//
// void handleRoot() {
//   String serverResponse;
//   serverResponse +=  "<h1>You are connected to the esp8266 !</h1><p>It is "
//   + String(hour()) + ":" + String(minute()) + ":" + String(second())
//   + ", and this is the " + (sunsettimeupdater.isDay(now()) ? "day" : "night") + ".</p>";
//
//
//
//   server.send(200, "text/html", serverResponse);
// }
//
//
//
// void setup_accesspoint() {
//   Serial.begin(115200);
//
//   WiFi.mode(WIFI_AP_STA);
//   // WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00
//   WiFi.softAP(ssid);
//
//   // Start HTTP Server
//   server.on("/", handle_accesspoint);
//   server.begin();
//
//   // Wait for WiFi to be OK.
//   Serial.print("IP address: ");
//   Serial.println(WiFi.localIP());
//
//   Serial.println("HTTP server started");
//   Serial.println();
// }
// void loop_accesspoint() {
//   Serial.println("loop");
//   server.handleClient();
//   delay(250);
// }
// int counter = 0;
// void handle_accesspoint() {
//   String serverResponse;
//   serverResponse +=  "Value " + String(counter);
//   counter++;
//   server.send(200, "text/html", serverResponse);
// }
//
//
// // void setup() {
// //   setup_screen();
// //   // setup_accesspoint();
// // }
// // void loop() {
// //   loop_screen();
// //   // loop_accesspoint();
// // }
