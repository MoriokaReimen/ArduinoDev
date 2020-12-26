#!/usr/bin/make -f

# setting output file
OUT = build/Program.ihex

# compiler setting
CC = avr-gcc
CFILES = $(wildcard src/App/*.c)
CPU_FREQ = 16000000
CFLAGS = -c -std=gnu99 -Os -Wall -ffunction-sections -fdata-sections -mmcu=atmega328p

# linker setting
LD = avr-ld
OBJFILES = $(addprefix build/, $(notdir $(CFILES:.c=.o)))
LDFLAGS = -Os -mavr5

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

$(OUT:.ihex=.elf) : $(OBJFILES)
	$(LD) $(LDFLAGS) $^ -o $@

build/%.o : src/App/%.c
	$(CC) $(CFLAGS) -DF_CPU=$(CPU_FREQ) $^ -o $@

upload : $(OUT)
	$(AVRDUDE) $(AVRDUDEFLAGS) -U flash:w:$^:i

clean :
	rm -rf build/*.o
	rm -rf build/*.ihex
	rm -rf build/*.elf

.PHONY : all upload clean

