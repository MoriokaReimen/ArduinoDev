#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <avr/io.h>
#include <util/delay.h>

#include "LEDTask.hpp"
#include "SensorTask.hpp"
#include "SerialTask.hpp"

void setup(void);
void loop(void);

void setup(void)
{
    QueueHandle_t queue = xQueueCreate(10, sizeof(int));
    xTaskCreate(serial_task, "Serial", 128, &queue, 1, NULL);
    xTaskCreate(led_task,    "LED",    128, &queue, 2, NULL);
    xTaskCreate(sensor_task, "Sensor", 128, &queue, 3, NULL);
    vTaskStartScheduler();
}

void loop(void)
{
    delay(100000);
}
