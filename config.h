#ifndef CONFIG_H
#define CONFIG_H
#include <avr/io.h>
#include <avr/interrupt.h>
#if defined (__AVR_ATmega328P__)||defined(__AVR_ATmega328__)
#define LED_PORT      PORTB
#define LED_DDR       DDRB
#define LED_PIN       PB5

#define BOARD_PORT    PORTD
#define BOARD_DDR     DDRD
#define BOARD_PIN     PD7
#define BOARD_IN      PIND

#define KEY_PORT      PORTD
#define KEY_DDR       DDRD
#define KEY_PIN_UP    PD2
#define KEY_PIN_DOWN  PD3
#define KEY_IN        PIND
#define KEY_MASK      (_BV(KEY_PIN_UP)|_BV(KEY_PIN_DOWN))

#define REGOUT_PORT   PORTB
#define REGOUT_DDR    DDRB
#define REGOUT_PIN    PB1
#elif defined(__AVR_ATmega2560__)
#define LED_PORT      PORTB
#define LED_DDR       DDRB
#define LED_PIN       PB7

#define BOARD_PORT    PORTD
#define BOARD_DDR     DDRD
#define BOARD_PIN     PD2
#define BOARD_IN      PIND

#define KEY_PORT      PORTD
#define KEY_DDR       DDRD
#define KEY_PIN_UP    PD0
#define KEY_PIN_DOWN  PD1
#define KEY_IN        PIND
#define KEY_MASK      (_BV(KEY_PIN_UP)|_BV(KEY_PIN_DOWN))

#define REGOUT_PORT   PORTB
#define REGOUT_DDR    DDRB
#define REGOUT_PIN    PB5
#else
#error "device type not defined"
#endif
static inline void hw_init (void); 
static inline void hw_init(void)
{
  LED_PORT &= ~_BV(LED_PIN);
  LED_DDR |= _BV(LED_PIN);
  BOARD_PORT |= _BV(BOARD_PIN);
  BOARD_DDR &= ~_BV(BOARD_PIN);
  KEY_PORT |= KEY_MASK;
  KEY_DDR &= ~KEY_MASK;
  REGOUT_PORT &= ~_BV(REGOUT_PIN);
  REGOUT_DDR |= _BV(REGOUT_PIN);
  TCCR1A |= _BV(COM1A1)|_BV(WGM10)|_BV(WGM11);
  TCCR1B |=_BV(WGM12)|_BV(CS10);
  TIMSK1 |= _BV(TOIE1)|_BV(OCIE1A);
  __builtin_avr_sei();

}


#endif
