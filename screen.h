#include <ESP8266WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 0  // GPIO0

class Screen {
public:
  Screen()
  : m_oled(OLED_RESET)
  {
    m_oled.begin();
    m_oled.clearDisplay();
    update();
  };
  ~Screen() = default;

  void update() {
    // Needs to setup at each clear.
    m_oled.clearDisplay();
    m_oled.setRotation(2);
    m_oled.dim(true);
    m_oled.setTextWrap(false);
    m_oled.setTextSize(1);
    m_oled.setTextColor(WHITE);
    m_oled.setCursor(0,0);

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

private:
  Adafruit_SSD1306 m_oled;
};
