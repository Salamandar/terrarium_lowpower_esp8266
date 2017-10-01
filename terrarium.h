#pragma

#include <DallasTemperature.h>
#include <OneWire.h>

// TODO some PID stuff
// TODO detect the hot/cold zones sensors

const int MaxSensors = 4;



class Terrarium {
public:
  Terrarium();
  virtual ~Terrarium () = default;


  void detectDS18B20();
  void updateTemperatures();

  void handleTemperatures(bool day);

  void loop(bool day) {
    updateTemperatures();
    handleTemperatures(day);
  }

private:
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


  OneWire ds18b20Wire;
  DallasTemperature ds18b20Sensors;


  struct Sensor {
    uint8_t address[8];
    float temp;
    String name;
  };
  int sensorsCount;
  Sensor sensors[MaxSensors];

  float temperatureAverage;

  void setTapis(bool on);
  void setLampe(bool on);


};
