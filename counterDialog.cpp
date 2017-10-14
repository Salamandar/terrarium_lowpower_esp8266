#include "main.h"
#include "screen.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


static const char* ssid     = "ESPap";
static const char* password = "thereisnospoon";
static const char* ipaddr   = "192.168.4.1";


class CounterAPServer
: public Main {
public:
  CounterAPServer()
  : m_server(80)
  {
    Serial.begin(115200);
    delay(10);

    Serial.print("Starting Wifi AP '");
    Serial.print(ssid);
    Serial.println("'");

    WiFi.mode(WIFI_AP_STA);
    // WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00
    WiFi.softAP(ssid);

    m_ip = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(m_ip);

    // m_server.on("/", this->serverHandleRoot);
    m_server.begin();
    Serial.println("HTTP server started");
  }

  void loop() {
    Serial.println("server loop");
    m_server.handleClient();
    delay(100);
  };

  virtual ~CounterAPServer() = default;
private:
  ESP8266WebServer m_server;
  IPAddress m_ip;

  int counter = 0;

  void serverHandleRoot() {
    String serverResponse;
    serverResponse +=  "val=" + String(counter) + "\n";
    counter++;
    m_server.send(200, "text/html", serverResponse);
  }
};

class CounterAPClient
: public Main {
public:
  CounterAPClient() {
    Serial.begin(115200);
    delay(10);

    // Force the ESP into client-only mode
    WiFi.mode(WIFI_STA);

    connectWifi();
  }

  void loop() {
    Serial.println("clientloop");
    auto request = getHttp();

    m_screen.setcounter(request);
    m_screen.update();

    delay(1000);
  }

  void connectWifi() {
    Serial.print("Connecting to ");
    Serial.print(ssid);

    WiFi.begin(ssid, password);

    // Wait for WiFi to be OK.
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.print(" WiFi connected, ");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }


  virtual ~CounterAPClient() = default;
private:
  HTTPClient m_http;

  Screen m_screen;

  String getHttp() {
    String url = "http://192.168.4.1/";
    m_http.begin(url);

    int httpCode = m_http.GET();
    // httpCode will be negative on error
    if (httpCode < 0) {
      Serial.printf("[HTTP] GET... failed, error: %s\n", m_http.errorToString(httpCode).c_str());
      return "error";
    }

    return m_http.getString();
  }
};








Main* newCounterAPServer() { return new CounterAPServer(); }
Main* newCounterAPClient() { return new CounterAPClient(); }
