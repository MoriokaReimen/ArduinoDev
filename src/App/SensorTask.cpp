#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <avr/io.h>
#include <task.h>
#include <math.h>

void sensor_task( void *pvParameters )
{
    QueueHandle_t* queue = static_cast<QueueHandle_t*>(pvParameters);
    TickType_t xLastWakeTime = 0;
    int count = 0;

    while (true)
    {
        int sensor_val = analogRead(A0);
        sensor_val = 500 * sin((double)count / 180.0 * 3.14);
        xQueueSend(*queue, &sensor_val, pdMS_TO_TICKS(5));
        count++;

        xTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(5));
    }
}
