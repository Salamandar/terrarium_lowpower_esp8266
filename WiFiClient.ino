#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <TimeLib.h>


const char* ssid     = "Broceliande";
const char* password = "avalonisinbroceliande";

//const char* host       = "data.sparkfun.com";
//const char* streamId   = "....................";
//const char* privateKey = "....................";

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.print(ssid);

  // Start WiFi connection
  WiFi.begin(ssid, password);

  time_setup();

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

  while(!time_loop()) {};
  terra_setup();

  
  // Force the ESP into client-only mode
  WiFi.mode(WIFI_STA);
}

void loop() {
  Serial.println("loop");
  // WiFi.forceSleepWake();
  server.handleClient();
  time_loop();
  
  // terra_loop(isDay());

  // WiFi.forceSleepBegin();
  WiFi.setSleepMode(WIFI_LIGHT_SLEEP);
  delay(60*1000);
}


void handleRoot() {
  String serverResponse;
  serverResponse +=  "<h1>You are connected to the esp8266 !</h1><p>It is " + String(hour()) + ":" + String(minute()) + ":" + String(second()) + ", and this is the " + (isDay() ? "day" : "night") + ".</p>";


  
  server.send(200, "text/html", serverResponse);
}

