#include <OneWire.h>
#include <DallasTemperature.h>

const int TapisPin   = 0; // IO0/D3 /!\ HIGH Run LOW Flash at reset
const int LampePin   = 4; // IO4/D2
const int DS18B20Pin = 5; // IO5/D1

const float TempHotZoneDayMin   = 33.0;
const float TempHotZoneDayMax   = 35.0;
const float TempHotZoneNightMin = 25.0;
const float TempHotZoneNightMax = 27.0;

const float TempColdZoneDayMin  = 22.0;
const float TempColdZoneDayMax  = 24.0;
const float TempColdZoneNightMin = 19.0;
const float TempColdZoneNightMax = 21.0;

OneWire oneWire(DS18B20Pin);
DallasTemperature sensors(&oneWire);

void terra_setup() {
  // Relays
  // pinMode(TapisPin, OUTPUT);
  pinMode(LampePin, OUTPUT);

  // Temperature sensors
  sensors.begin();
}

void terra_loop(bool day) {
  String DebugString;
  float tempMoyenne = 0;

  uint8_t sensorsCount;
  for (sensorsCount = 0; sensorsCount < sensors.getDeviceCount(); sensorsCount++) {
    uint8_t address[8];
    sensors.getAddress(address, sensorsCount);
    float temperature = sensors.getTempC(address);
    tempMoyenne += temperature;

    DebugString += "sensor " + String(sensorsCount) + " { ";

    // Print address
    for (uint8_t j = 0; j < 8; j++) {
      DebugString += "0x";
      if (address[j] < 0x10)
        DebugString += "0";
      DebugString += String(address[j], HEX);
      if (j < 7)
        DebugString += ", ";
    }
    DebugString += " }";

    // Print temperature
    DebugString += "  " + String(temperature) + "°C";
    DebugString += "\n";
  }

  if (sensorsCount > 0)
    tempMoyenne /= sensorsCount;

  DebugString += "Temp moyenne: " + String(tempMoyenne) + "°C\n";

  bool tooHot = day
                ? tempMoyenne > TempHotZoneDayMax
                : tempMoyenne > TempHotZoneNightMax;
  bool tooCold = day
                 ? tempMoyenne < TempHotZoneDayMin
                 : tempMoyenne < TempHotZoneNightMin;

  if (tooCold)
    setTapis(true);
  if (tooHot)
    setTapis(false);

  setLampe(day);


  Serial.print(DebugString);
}


void setTapis(bool on) {
  digitalWrite(TapisPin, on ? LOW : HIGH);
}
void setLampe(bool on) {
  digitalWrite(LampePin, on ? LOW : HIGH);
}

