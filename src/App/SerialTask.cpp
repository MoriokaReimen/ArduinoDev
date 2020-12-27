#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <avr/io.h>
#include <util/delay.h>

void serial_task( void *pvParameters )
{
    Serial.begin(9600);
    QueueHandle_t* queue = static_cast<QueueHandle_t*>(pvParameters);
    while (true)
    {
        int sensor_val = 0;
        xQueueReceive(*queue, &sensor_val, static_cast<TickType_t>(1000 / portTICK_PERIOD_MS));
        Serial.print("Sensor Val:");
        Serial.println(sensor_val);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
