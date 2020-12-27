#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <avr/io.h>
#include <util/delay.h>

void sensor_task( void *pvParameters )
{
    QueueHandle_t* queue = static_cast<QueueHandle_t*>(pvParameters);
    while (true)
    {
        const int sensor_val = analogRead(A0);
        xQueueSend(*queue, &sensor_val, static_cast<TickType_t>(0));
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
