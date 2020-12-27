#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <avr/io.h>
#include <util/delay.h>

void led_task( void *pvParameters )
{
    /* configure PB5 pin as an output pin */
    pinMode(13, OUTPUT);

    while (true)
    {
        /* set PB5 pin high */
        digitalWrite(13, HIGH);

        /*Wait 500 ms */
        vTaskDelay(500 / portTICK_PERIOD_MS);

        /* set PB5 pin low */
        digitalWrite(13, LOW);

        /*Wait 500 ms */
        vTaskDelay(500 / portTICK_PERIOD_MS);

    }
}
