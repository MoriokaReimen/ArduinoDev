TARGET_NAME = Sample
SRC_FILES = \
	Sample.c

all : $(TARGET_NAME).ihex

$(TARGET_NAME).ihex : $(TARGET_NAME).elf
	avr-objcopy -O ihex -R .eeprom $^ $@

$(TARGET_NAME).elf : $(TARGET_NAME).o
	avr-gcc -Os -mmcu=atmega328p -ffunction-sections -fdata-sections -Wl,--gc-sections $^ -o $@

$(TARGET_NAME).o : $(TARGET_NAME).c
	avr-gcc -c -std=gnu99 -Os -Wall -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000 $^ -o $@

upload : $(TARGET_NAME).ihex
	avrdude -C ./conf/avrdude.conf -p atmega328p -c PROGRAMMER_NAME -b 19600 -P PORT_NAME -U flash:w:$^:i

clean :
	rm -rf *.o
	rm -rf *.ihex
	rm -rf *.elf

.PHONY : all upload clean

