#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <avr/io.h>
#include <util/delay.h>

#define MS_DELAY 500

void task1( void *pvParameters );
void task2( void *pvParameters );
void setup(void);
void loop(void);

void setup(void)
{
    xTaskCreate(task1, "task1", 128, NULL, 1, NULL);
    xTaskCreate(task2, "task2", 128, NULL, 2, NULL);
}

void loop(void)
{
}

void task1( void *pvParameters )
{
    /* configure PB5 pin as an output pin */
    pinMode(13, OUTPUT);

    while (1)
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

void task2( void *pvParameters )
{
    Serial.begin(9600);
    while (1)
    {
        Serial.println("Buzz");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        Serial.println("Fizz");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
