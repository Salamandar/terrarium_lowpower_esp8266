#include <TimeLib.h>
#include <ArduinoJson.h>
#include <stdio.h>

#include <ESP8266HTTPClient.h>

float lat = 45.1855779,
      lng =  5.6996643;

// Default sun rise/set times
int SunRise =  7*60 + 45;
int SunSet  = 20*60 + 30;

int dayID = 0;

void getSunSetTimes() {
  // Update once a day
  int newDayID = day();
  if (newDayID != dayID)
    return;
  dayID = newDayID;
  
  HTTPClient http;
  String url = "http://api.sunrise-sunset.org/json?lat=" + String(lat, 7) + "&lng=" + String(lng, 7) + "&date=" + String(year()) + "-" + String(month()) + "-" + String(day()) + "&formatted=0";
  http.begin(url);

  int httpCode = http.GET();
  // httpCode will be negative on error
  if (httpCode < 0) {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    return;
  }

  String payload = http.getString();
  Serial.println(payload);

  StaticJsonBuffer<700> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(payload);
  const char* sunrise_str = root["results"]["sunrise"];
  const char* sunset__str = root["results"]["sunset" ];

  int y, M, d, s, h, m;
  sscanf(sunrise_str, "%d-%d-%dT%d:%d:%d+00:00", &y, &M, &d, &h, &m, &s);
  SunRise = h*60+m;
  sscanf(sunset__str, "%d-%d-%dT%d:%d:%d+00:00", &y, &M, &d, &h, &m, &s);
  SunSet  = h*60+m;
}


bool isDay() {
  getSunSetTimes();
  int currentMoment = hour()*60 + minute();
  return currentMoment >= SunRise
      && currentMoment <  SunSet;
}

