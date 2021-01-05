#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <avr/io.h>
#include <util/delay.h>
#include <crc.hpp>

#include "Packet.hpp"

void serial_task( void *pvParameters )
{
    Serial.begin(9600);
    QueueHandle_t* queue = static_cast<QueueHandle_t*>(pvParameters);

    while (true)
    {
        int sensor_val = 0;
        xQueueReceive(*queue, &sensor_val, portMAX_DELAY);
        Packet packet;
        packet.data1 = sensor_val;
        packet.data2 = xTaskGetTickCount();
        CRC32 crc = calc_crc32(&packet.data1, sizeof(packet.data1));
        crc = calc_crc32(&packet.data2, sizeof(packet.data2), crc);
        packet.crc = crc;
        if (Serial)
        {
            Serial.write(reinterpret_cast<const uint8_t*>(&packet), sizeof(Packet));
        }
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}
