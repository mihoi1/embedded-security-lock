#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define LED_GREEN     PD6
#define LED_RED       PD7
#define PANIC_BUTTON  PD2   
#define BUTTON_1      PD4
#define BUTTON_2      PD5
#define ALARM_DURATION_MS 5000  

volatile uint8_t activeAlarm = 0;

ISR(INT0_vect) {
    activeAlarm = 1;
}

int main(void) {
    DDRD |= (1 << LED_GREEN) | (1 << LED_RED);
    DDRD &= ~((1 << PANIC_BUTTON) | (1 << BUTTON_1) | (1 << BUTTON_2));
    PORTD |= (1 << PANIC_BUTTON) | (1 << BUTTON_1) | (1 << BUTTON_2);

    EICRA |= (1 << ISC01);
    EIMSK |= (1 << INT0);
    
    sei(); 

    uint16_t elapsed = 0;

    while (1) {
        if (activeAlarm) {
            PORTD ^= (1 << LED_RED);
            PORTD &= ~(1 << LED_GREEN);
            _delay_ms(500);
            elapsed += 500;

            if (elapsed >= ALARM_DURATION_MS) {
                activeAlarm = 0;
                elapsed = 0;
                PORTD &= ~(1 << LED_RED);
            }
        } else {
            // Verificare simultaneitate butoane
            if (!(PIND & (1 << BUTTON_1)) && !(PIND & (1 << BUTTON_2))) {
                PORTD |= (1 << LED_GREEN);
                PORTD &= ~(1 << LED_RED);
            } else {
                PORTD |= (1 << LED_RED);
                PORTD &= ~(1 << LED_GREEN);
            }
            _delay_ms(50);
        }
    }
}
