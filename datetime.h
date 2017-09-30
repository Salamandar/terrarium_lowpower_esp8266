#pragma once

#include <WiFiUdp.h>
#include <NTPClient.h>
#include <Timezone.h>

const TimeChangeRule CentralEuropeSummerT = {"CEST", Last, Sun, Mar, 2, 120}; // Central European Summer Time
const TimeChangeRule CentralEuropeWinterT = {"CET ", Last, Sun, Oct, 3,  60}; // Central European Standard Time
Timezone myTimeZone(CentralEuropeSummerT, CentralEuropeWinterT);
TimeChangeRule* currentCR;




class DateTime {
public:
  DateTime();
  virtual ~DateTime() = default;

  void updateTime();

  bool couldUpdate() { return m_couldUpdate; };
  void forceUpdate();

  String fullStr();
  String timeStr();

private:
  WiFiUDP ntpUDP;
  NTPClient timeClient;

  bool m_couldUpdate;


};



class SunSetTime {
public:
  SunSetTime(float latitude, float longitude);
  virtual ~SunSetTime() = default;

  bool isDay(time_t t);

private:
  float m_lat, m_lng;
  int lastUpdateDay = 0;

  inline
  int moment(int hour, int minute) { return (hour * 64 + minute); }
  int riseMoment, setMoment;

  void updateFromServer();

};
