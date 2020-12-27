#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <avr/io.h>
#include <util/delay.h>

void serial_task( void *pvParameters )
{
    Serial.begin(9600);
    while (true)
    {
        Serial.println("Buzz");
    }
}
