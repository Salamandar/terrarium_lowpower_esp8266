#include "main.h"

Main* main;

void setup() {
  // Change this line to change the program to use
  main = newCounterAPServer();
}
void loop() {
  if (main)
    main->loop();
  else
    delay(-1);
}
