#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <avr/io.h>
#include <util/delay.h>

void sensor_task( void *pvParameters )
{
    while (true)
    {
        const int sensor_val = analogRead(A0);

    }
}
