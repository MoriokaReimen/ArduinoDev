#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <avr/io.h>
#include <task.h>

void sensor_task( void *pvParameters )
{
    QueueHandle_t* queue = static_cast<QueueHandle_t*>(pvParameters);
    int count = 0;
    TickType_t xLastWakeTime = 0;

    while (true)
    {
        const int sensor_val = analogRead(A0);
        xQueueSend(*queue, &count, pdMS_TO_TICKS(5));
        count++;

        xTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(5));
    }
}
