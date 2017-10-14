#include <ESP8266WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>

#define OLED_RESET 0  // GPIO0

class Screen {
public:
  Screen()
  : m_oled(OLED_RESET)
  , m_mode(DisplayMode::Terra)
  {
    m_oled.begin();
    update();
  };
  ~Screen() = default;

  void update() {
    // Needs to setup at each clear.
    reset();
    switch (m_mode) {
      case DisplayMode::Terra:    return printTerrarium();
      case DisplayMode::Counter:  return printWifiInfos();
    }
  };

  void setCounterMode() { m_mode = DisplayMode::Counter; }
  void setcounter(String count) { m_counter = count; };

private:
  Adafruit_SSD1306 m_oled;

  enum class DisplayMode { Terra, Counter } m_mode;

  String m_counter = "unset";


  void reset() {
    m_oled.clearDisplay();
    m_oled.setRotation(2);
    m_oled.dim(true);
    m_oled.setTextWrap(false);
    m_oled.setTextSize(1);
    m_oled.setTextColor(WHITE);
    m_oled.setCursor(0,0);
  }

  void printTerrarium() {
    char line[32];

    int temp1(0), temp2(15);
    snprintf(line, 31, "%2s%cC%6s%02dh%02d:%02d", String(temp1).c_str(), 247, "", hour(), minute(), second());
    m_oled.println(line);
    snprintf(line, 31, "%2s%cC%14s", String(temp2).c_str(), 247, WiFi.localIP().toString().c_str());
    m_oled.println(line);

    m_oled.println(String("Plateau: ") + (true  ? "on" : "off"));
    m_oled.println(String("Lampe  : ") + (false ? "on" : "off"));

    m_oled.display();
  };

  void printWifiInfos() {
    char line[32];
    snprintf(line, 31, "co to %s", WiFi.SSID().c_str());
    m_oled.println(line);
    snprintf(line, 31, "power %ld", WiFi.RSSI());
    m_oled.println(line);
    snprintf(line, 31, "counter: %s", m_counter.c_str());
    m_oled.println(line);




    m_oled.display();
  }
};
