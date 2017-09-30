Hardw = -hardware /usr/share/arduino/hardware/ -hardware ~/.arduino15/packages/esp8266/hardware/
Tools = -tools ~/.arduino15/packages/esp8266/tools/
Librs = -libraries ~/Arduino/libraries
Board = esp8266:2.3.0:d1_mini

Sources = $(shell find $(SOURCEDIR) -name '*.c' -o -name '*.ino' -o -name '*.cpp')


all:
	arduino-builder -compile ${Hardw} ${Tools} ${Librs} -fqbn ${Board} ${Sources}
