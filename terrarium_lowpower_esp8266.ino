#include "terrarium.h"
#include "datetime.h"
#include "screen.h"

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <TimeLib.h>

const char* password = "NutellaEtGuizmo";
const char* ssid     = "LaQueue";

//const char* ssid     = "Broceliande";
//const char* password = "avalonisinbroceliande";
//const char* ssid     = "Atalante";
//const char* password = "jeanvigotetlescamelots";
//const char* host       = "data.sparkfun.com";
//const char* streamId   = "....................";
//const char* privateKey = "....................";

ESP8266WebServer server(80);
DateTime timeupdater;
SunSetTime sunsettimeupdater(45.1855779, 5.6996643);
Terrarium terrarium;
Screen screen;


void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.print(ssid);

  // Start WiFi connection
  WiFi.begin(ssid, password);

  // time_setup();

  // Start HTTP Server
  server.on("/", handleRoot);
  server.begin();

  // Wait for WiFi to be OK.
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print(" WiFi connected, ");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("HTTP server started");
  Serial.println();

  timeupdater.forceUpdate();
  terrarium.detectDS18B20();


  // Force the ESP into client-only mode
  WiFi.mode(WIFI_STA);
}

void loop() {
  Serial.println("loop");
  // WiFi.forceSleepWake();
  server.handleClient();
  screen.update();
  // time_loop();

  // terra_loop(isDay());

  // WiFi.forceSleepBegin();
  WiFi.setSleepMode(WIFI_LIGHT_SLEEP);
  delay(1000);
}


void handleRoot() {
  String serverResponse;
  serverResponse +=  "<h1>You are connected to the esp8266 !</h1><p>It is "
  + String(hour()) + ":" + String(minute()) + ":" + String(second())
  + ", and this is the " + (sunsettimeupdater.isDay(now()) ? "day" : "night") + ".</p>";



  server.send(200, "text/html", serverResponse);
}
