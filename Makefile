#!/usr/bin/make -f

# setting output file
OUT = build/Sample.ihex

# compiler setting
CC = avr-gcc
CFILES = $(wildcard src/*.c)
CPU_FREQ = 16000000
CFLAGS = -c -std=gnu99 -Os -Wall -ffunction-sections -fdata-sections -mmcu=atmega328p

# linker setting
LD = avr-gcc
OBJFILES = $(addprefix build/, $(notdir $(CFILES:.c=.o)))
LDFLAGS = -Os -mmcu=atmega328p -ffunction-sections -fdata-sections -Wl,--gc-sections

#  objcopy setting
OBJCOPY = avr-objcopy
OBJFLAGS = -O ihex -R .eeprom 

# avrdude setting
AVRDUDE = avrdude
PORT =
AVRDUDEFLAGS = ./conf/avrdude.conf
AVRDUDECONF = -C $(AVRDUDECONF) -v -V -p atmega328p -c arduino -b 115200 -P $(PORT) -D

# Build Step Setting
all : $(OUT)

$(OUT) : $(OUT:.ihex=.elf)
	$(OBJCOPY) $(OBJFLAGS) $^ $@

$(OUT:.ihex=.elf) : $(OBJFILES)
	$(LD) $(LDFLAGS) $^ -o $@

build/%.o : src/%.c
	$(CC) $(CFLAGS) -DF_CPU=$(CPU_FREQ) $^ -o $@

upload : $(OUT)
	$(AVRDUDE) $(AVRDUDEFLAGS) -U flash:w:$^:i

clean :
	rm -rf build/*.o
	rm -rf build/*.ihex
	rm -rf build/*.elf

.PHONY : all upload clean

