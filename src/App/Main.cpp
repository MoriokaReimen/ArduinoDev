#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <avr/io.h>
#include <util/delay.h>

#include "LEDTask.hpp"
#include "SensorTask.hpp"
#include "SerialTask.hpp"

void setup(void);
void loop(void);

void setup(void)
{
    xTaskCreate(serial_task, "Serial", 128, NULL, 1, NULL);
    xTaskCreate(led_task,    "LED",    128, NULL, 2, NULL);
    xTaskCreate(sensor_task, "Sensor", 128, NULL, 3, NULL);
}

void loop(void)
{
}
