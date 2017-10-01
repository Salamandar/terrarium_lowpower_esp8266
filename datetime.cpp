#include "datetime.h"

#include <TimeLib.h>
#include <ArduinoJson.h>
#include <stdio.h>
#include <ESP8266HTTPClient.h>
Timezone myTimeZone(CentralEuropeSummerT, CentralEuropeWinterT);

TimeChangeRule* currentCR;

time_t utcToLocal(time_t utc) {
  return myTimeZone.toLocal(utc, &currentCR);
}

//Print an integer in "00" format (with leading zero).
//Input value assumed to be between 0 and 99.
String sPrintI00(int val)
{
  return String(val < 10 ? "0" : "") + String(val, DEC);
}

//Function to print time with time zone
String hourString(time_t t)
{
  return sPrintI00(hour(t))
  + ":"+ sPrintI00(minute(t))
  + ":"+ sPrintI00(second(t));
}
String timeString(time_t t)
{
  return hourString(t)
  + " "+ dayShortStr(weekday(t))
  + " "+ sPrintI00(day(t))
  + " "+ monthShortStr(month(t))
  + " "+ year(t);
}







DateTime::DateTime()
: ntpUDP()
, timeClient(ntpUDP)
, m_couldUpdate(false)
{
  // Enable time update each day
  timeClient.setUpdateInterval(24 * 3600 * 1000);
  timeClient.begin();
};

void DateTime::updateTime() {
  m_couldUpdate = timeClient.update();
  if (m_couldUpdate) {
    // timezone + time saving handled here
    auto local = utcToLocal(timeClient.getEpochTime());
    setTime(local);
  } else
    Serial.println("Error: could not update NTP time");
}

void DateTime::forceUpdate() {
  while(!couldUpdate())
    updateTime();
}

String DateTime::fullStr() {
  return timeString(now());
}
String DateTime::timeStr() {
  return hourString(now());
}






SunSetTime::SunSetTime(float latitude, float longitude)
: m_lat(latitude)
, m_lng(longitude) {

}
bool SunSetTime::isDay(time_t t) {
  // Update once a day
  int today = day();
  if (today != lastUpdateDay) {
    updateFromServer();
    lastUpdateDay = today;
  }

  return moment(hour(), minute()) >= riseMoment
      && moment(hour(), minute()) <  setMoment;
}

void SunSetTime::updateFromServer() {
  HTTPClient http;
  String url = "http://api.sunrise-sunset.org/json?lat=" + String(m_lat, 7) + "&lng=" + String(m_lng, 7) + "&date=" + String(year()) + "-" + String(month()) + "-" + String(day()) + "&formatted=0";
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
  riseMoment = moment(h, m);
  sscanf(sunset__str, "%d-%d-%dT%d:%d:%d+00:00", &y, &M, &d, &h, &m, &s);
  setMoment  = moment(h, m);
}
