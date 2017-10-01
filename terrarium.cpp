#include "terrarium.h"
#include <cassert>

namespace {
String printArray8(uint8_t* array) {
  String msg = "{ ";
  for (uint8_t j = 0; j < 8; j++) {
    msg += "0x";
    if (array[j] < 0x10)
      msg += "0";
      msg += String(array[j], HEX);
    if (j == 7)
      msg += " }";
    else
      msg += ", ";
  }
  return msg;
}
}

Terrarium::Terrarium()
: ds18b20Wire(DS18B20Pin)
, ds18b20Sensors(&ds18b20Wire)
, sensorsCount(0)
{
  // Relays
  pinMode(TapisPin, OUTPUT);
  pinMode(LampePin, OUTPUT);

  // Temperature sensors
  ds18b20Sensors.begin();
}

void Terrarium::detectDS18B20() {
  sensorsCount = ds18b20Sensors.getDeviceCount();
  assert(sensorsCount <= MaxSensors);
  sensorsCount = min(sensorsCount, MaxSensors);

  for (auto i = 0; i < sensorsCount; i++)
    ds18b20Sensors.getAddress(sensors[i].address, i);

  auto debugPrint = [&]() {
    for (size_t i = 0; i < sensorsCount; i++) {
      Serial.print("Detected ds18b20 ");
      Serial.print(i);
      Serial.print(" address ");
      Serial.print(printArray8(sensors[i].address));
      Serial.println("");
    }
  };

}


void Terrarium::updateTemperatures() {
  auto debugPrintSensor = [&](int sensor) {
    Serial.print("sensor ");
    Serial.print(printArray8(sensors[sensor].address));
    Serial.print(", temp: ");
    Serial.print(sensors[sensor].temp);
    Serial.println("°C");
  };
  auto debugPrintMoyenne = [&](float moyenne) {
    Serial.print("Température moyenne: ");
    Serial.print(moyenne);
    Serial.println("°C");
  };

  temperatureAverage = 0;
  for (size_t i = 0; i < sensorsCount; i++) {
    sensors[i].temp = ds18b20Sensors.getTempC(sensors[i].address);
    temperatureAverage += sensors[i].temp;
    // debugPrintSensor(i);
  }

  if (sensorsCount != 0)
    temperatureAverage /= sensorsCount;
  //debugPrintMoyenne(tempMoyenne);

}

void Terrarium::handleTemperatures(bool day) {
  bool tooHot = day
                ? temperatureAverage > TempHotZoneDayMax
                : temperatureAverage > TempHotZoneNightMax;
  bool tooCold = day
                ? temperatureAverage < TempHotZoneDayMin
                : temperatureAverage < TempHotZoneNightMin;

  if (tooCold)
    setTapis(true);
  if (tooHot)
    setTapis(false);
  // Do nothing if in between

  setLampe(day);
}


void Terrarium::setTapis(bool on) {
  digitalWrite(TapisPin, on ? LOW : HIGH);
}
void Terrarium::setLampe(bool on) {
  digitalWrite(LampePin, on ? LOW : HIGH);
}
