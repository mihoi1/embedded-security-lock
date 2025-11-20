#include <avr/interrupt.h>
#include <util/delay.h>

#define DDRD (*(volatile unsigned char*)0x2A)
#define PORTD (*(volatile unsigned char*)0x2B)
#define PIND (*(volatile unsigned char*)0x29)

#define LED_GREEN 6
#define LED_RED 7
#define ALARM_PIN 2
#define SENSOR_1 4
#define SENSOR_2 5

volatile uint8_t activeAlarm = 0;

void setup() {
  cli();

  DDRD |= (1 << LED_GREEN) | (1 << LED_RED);

  DDRD &= ~((1 << ALARM_PIN) | (1 << SENSOR_1) | (1 << SENSOR_2));

  PORTD |= (1 << ALARM_PIN) | (1 << SENSOR_1) | (1 << SENSOR_2);

  EICRA |= (1 << ISC01);
  EICRA &= ~(1 << ISC00);

  EIMSK |= (1 << INT0);

  sei();
}

ISR(INT0_vect) {
  activeAlarm = 1;
}

void loop() {
  if (activeAlarm == 1) {
    PORTD ^= (1 << LED_RED);
    PORTD &= ~(1 << LED_GREEN);
    _delay_ms(500);
    return;
  }

  uint8_t state = PIND & ((1 << SENSOR_1) | (1 << SENSOR_2));

  if (state == 0) {
    PORTD |= (1 << LED_GREEN);
    PORTD &= ~(1 << LED_RED);
  } 
  else {
    PORTD &= ~(1 << LED_GREEN);
    PORTD |= (1 << LED_RED);
  }

  _delay_ms(50);
}