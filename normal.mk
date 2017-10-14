Sources = $(shell find $(SOURCEDIR) -name '*.c' -o -name '*.ino' -o -name '*.cpp')
Objects = $(Sources:cpp=o)

ardflags = -DARDUINO=1900
espflags = -I ~/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/libraries/ESP8266WiFi/src/ \
					 -I ~/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/cores/esp8266/ \
					 -I ~/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/tools/sdk/include/ \
					 -I ~/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/variants/d1_mini/ \
					 -I ~/.arduino15/packages/esp8266/hardware/esp8266/2.3.0/libraries/ESP8266HTTPClient/src


libflags =  -I ~/Arduino/libraries/NTPClient \
						-I ~/Arduino/libraries/Timezone \
						-I ~/Arduino/libraries/Time \
						-I ~/Arduino/libraries/ArduinoJson \
						-I ~/Arduino/libraries/Time \
						-I ~/Arduino/libraries/Time

CXX_FLAGS = $(ardflags) $(espflags) $(libflags)
LD_FLAGS  =

*.o: *.cpp
	g++ $< -o $@ -c $(CXX_FLAGS)

*.elf: $(Objects)
	h++ $< -o $@    $(LD_FLAGS)
