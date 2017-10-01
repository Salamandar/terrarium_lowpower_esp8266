#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 OLED(OLED_RESET);

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
    OLED.clearDisplay();
    OLED.setRotation(2);
    OLED.dim(true);
    OLED.setTextWrap(false);
    OLED.setTextSize(1);
    OLED.setTextColor(WHITE);
    OLED.setCursor(0,0);

    char line[32];

    int temp1(0), temp2(15);
    snprintf(line, 31, "%2s%cC%6s%02dh%02d:%02d", String(temp1).c_str(), 247, "", hour(), minute(), second());
    OLED.println(line);
    snprintf(line, 31, "%2s%cC%14s", String(temp2).c_str(), 247, WiFi.localIP().toString().c_str());
    OLED.println(line);
  
    OLED.println(String("Plateau: ") + (true  ? "on" : "off"));
    OLED.println(String("Lampe  : ") + (false ? "on" : "off"));
  
    OLED.display();
  };

private:
  Adafruit_SSD1306 oled;
};
