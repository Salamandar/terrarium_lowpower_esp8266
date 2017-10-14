#pragma once

class Main {
public:
  virtual void loop()
  { };
};

// Add here (or other header) your 'new Main' prototypes
Main* newTerraBrain();
Main* newHiveMeter();
Main* newCounterAPServer();
Main* newCounterAPClient();
