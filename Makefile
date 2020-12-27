#!/usr/bin/make -f

# setting output file
OUT = build/Program.ihex

# Hardware Setting
CPU_FREQ = 16000000

# Directory structure setting
INCLUDE = \
-I./src/App/ \
-I./src/Arduino/ \
-I./src/Atmega328P/ \
-I./src/FreeRTOS/


# App Directory setting
APPCFILES = $(wildcard src/App/*.c)
APPCXXFILES = $(wildcard src/App/*.cpp)
APPASMFILES = $(wildcard src/App/*.S)
APPOBJFILES = $(addprefix build/, $(notdir $(APPCFILES:.c=.o))) $(addprefix build/, $(notdir $(APPCXXFILES:.cpp=.o))) $(addprefix build/, $(notdir $(APPASMFILES:.S=.o)))

# FreeRTOS Directory setting
FreeRTOSCFILES = $(wildcard src/FreeRTOS/*.c)
FreeRTOSCXXFILES = $(wildcard src/FreeRTOS/*.cpp)
FreeRTOSASMFILES = $(wildcard src/FreeRTOS/*.S)
FreeRTOSOBJFILES = $(addprefix build/, $(notdir $(FreeRTOSCFILES:.c=.o))) $(addprefix build/, $(notdir $(FreeRTOSCXXFILES:.cpp=.o))) $(addprefix build/, $(notdir $(FreeRTOSASMFILES:.S=.o)))

# Arduino Directory setting
ArduinoCFILES = $(wildcard src/Arduino/*.c)
ArduinoCXXFILES = $(wildcard src/Arduino/*.cpp)
ArduinoASMFILES = $(wildcard src/Arduino/*.S)
ArduinoOBJFILES = $(addprefix build/, $(notdir $(ArduinoCFILES:.c=.o))) $(addprefix build/, $(notdir $(ArduinoCXXFILES:.cpp=.o))) $(addprefix build/, $(notdir $(ArduinoASMFILES:.S=.o)))

# Assembler setting
ASM = avra
ASMFLAGS = -c $(INCLUDE) -Wall -ffunction-sections -fdata-sections -mmcu=atmega328p 

# C compiler setting
CC = avr-gcc
CFLAGS = -c $(INCLUDE) -std=gnu99 -Os -Wall -ffunction-sections -fdata-sections -mmcu=atmega328p

# C++ compiler setting
CXX = avr-c++
CXXFLAGS = -c $(INCLUDE) -std=c++11 -Os -Wall -ffunction-sections -fdata-sections -mmcu=atmega328p

# linker setting
LD = avr-gcc
LDFLAGS = -mmcu=atmega328p 

# Archiver setting
AR = avr-ar
ARFLAGS = -rv

#  objcopy setting
OBJCOPY = avr-objcopy
OBJFLAGS = -O ihex -R .eeprom 

# avrdude setting
AVRDUDE = avrdude
PORT = /dev/ttyACM0
AVRDUDECONF = ./conf/avrdude.conf
AVRDUDEFLAGS = -C $(AVRDUDECONF) -v -V -p atmega328p -carduino -b 115200 -P $(PORT) -D

# Build Step Setting
all : $(OUT)

$(OUT) : $(OUT:.ihex=.elf)
	$(OBJCOPY) $(OBJFLAGS) $^ $@

$(OUT:.ihex=.elf) : $(APPOBJFILES) build/libArduino.a build/libFreeRTOS.a 
	$(LD) $(LDFLAGS) $^ -o $@

# App directroy build setting
build/%.o : src/App/%.c
	$(CC) $(CFLAGS) -DF_CPU=$(CPU_FREQ) $^ -o $@

build/%.o : src/App/%.cpp
	$(CXX) $(CXXFLAGS) -DF_CPU=$(CPU_FREQ) $^ -o $@

build/%.o : src/App/%.S
	$(ASM) $(ASMFLAGS) -DF_CPU=$(CPU_FREQ) $^ -o $@

# FreeRTOS directroy build setting
build/libFreeRTOS.a : $(FreeRTOSOBJFILES)
	$(AR) $(ARFLAGS) $@ $^

build/%.o : src/FreeRTOS/%.c
	$(CC) $(CFLAGS) -DF_CPU=$(CPU_FREQ) $^ -o $@

build/%.o : src/FreeRTOS/%.cpp
	$(CXX) $(CXXFLAGS) -DF_CPU=$(CPU_FREQ) $^ -o $@

build/%.o : src/FreeRTOS/%.S
	$(ASM) $(ASMFLAGS) -DF_CPU=$(CPU_FREQ) $^ -o $@

# Arduino directroy build setting
build/libArduino.a : $(ArduinoOBJFILES)
	$(AR) $(ARFLAGS) $@ $^

build/%.o : src/Arduino/%.c
	$(CC) $(CFLAGS) -DF_CPU=$(CPU_FREQ) $^ -o $@

build/%.o : src/Arduino/%.cpp
	$(CXX) $(CXXFLAGS) -DF_CPU=$(CPU_FREQ) $^ -o $@

build/%.o : src/Arduino/%.S
	$(ASM) $(ASMFLAGS) -DF_CPU=$(CPU_FREQ) $^ -o $@

upload : $(OUT)
	$(AVRDUDE) $(AVRDUDEFLAGS) -U flash:w:$^:i

clean :
	rm -rf build/*.a
	rm -rf build/*.o
	rm -rf build/*.ihex
	rm -rf build/*.elf

.PHONY : all upload clean

