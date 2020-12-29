#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <avr/io.h>
#include <util/delay.h>

#include "Packet.hpp"

void serial_task( void *pvParameters )
{
    Serial.begin(9600);
    QueueHandle_t* queue = static_cast<QueueHandle_t*>(pvParameters);

    while (true)
    {
        int sensor_val = 0;
        xQueueReceive(*queue, &sensor_val, pdMS_TO_TICKS(50));
        Packet packet;
        packet.data1 = sensor_val;
        Serial.write(reinterpret_cast<const uint8_t*>(&packet), sizeof(Packet));
    }
}
