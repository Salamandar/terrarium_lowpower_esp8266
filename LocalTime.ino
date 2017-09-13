#include <Timezone.h>

const TimeChangeRule CentralEuropeSummerT = {"CEST", Last, Sun, Mar, 2, 120}; // Central European Summer Time
const TimeChangeRule CentralEuropeWinterT = {"CET ", Last, Sun, Oct, 3,  60}; // Central European Standard Time
Timezone myTimeZone(CentralEuropeSummerT, CentralEuropeWinterT);
TimeChangeRule* currentCR;

time_t utcToLocal(time_t utc) {
  return myTimeZone.toLocal(utc, &currentCR);
}

