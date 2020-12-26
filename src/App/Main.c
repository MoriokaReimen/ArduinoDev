#include <avr/io.h>
#include <util/delay.h>

#define MS_DELAY 500

void setup(void);
void loop(void);

int main(void)
{
    setup();

    while (1)
    {
        loop();
    }
}

void setup(void)
{
    /* configure PB5 pin as an output pin */
    DDRB |= _BV(DDB5);
}

void loop(void)
{
    /* set PB5 pin high */
    PORTB |= _BV(PORTB5);

    /*Wait 500 ms */
    _delay_ms(MS_DELAY);

    /* set PB5 pin low */
    PORTB &= ~_BV(PORTB5);

    /*Wait 500 ms */
    _delay_ms(MS_DELAY);

    /* set PB5 pin high */
    PORTB |= _BV(PORTB5);

    /*Wait 500 ms */
    _delay_ms(MS_DELAY);

    /* set PB5 pin low */
    PORTB &= ~_BV(PORTB5);

    /*Wait 500 ms */
    _delay_ms(MS_DELAY);

    /* set PB5 pin high */
    PORTB |= _BV(PORTB5);

    /*Wait 2000 ms */
    _delay_ms(MS_DELAY);
    _delay_ms(MS_DELAY);
    _delay_ms(MS_DELAY);
    _delay_ms(MS_DELAY);

    /* set PB5 pin low */
    PORTB &= ~_BV(PORTB5);

    /*Wait 500 ms */
    _delay_ms(MS_DELAY);
}
