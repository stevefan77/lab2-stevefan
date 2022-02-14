/*
 * SF_LAB2.c
 *
 * Created: 2/2/2022 11:46:22 AM
 * Author : Steven Fandozzi
 */ 

#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "uart.h"
#include <avr/interrupt.h>
#include <time.h>

// -- Part B --

void Initialize(){
	cli();
	DDRD |= (1<<DDD7);
	DDRB |= (1<<DDB5);

	TCCR1B |= (1<<CS10);
	TCCR1B &= ~(1<<CS11);
	TCCR1B |= (1<<CS12);

	TCCR1A &= ~(1<<WGM10);
	TCCR1A &= ~(1<<WGM11);
	TCCR1B &= ~(1<<WGM12);
	TCCR1B &= ~(1<<WGM13);

	TCCR1B |= (1<<ICES1);
	TIFR1 |= (1<<ICF1);
	TIMSK1 |= (1<<ICIE1);
	
	sei();
}

ISR(TIMER1_CAPT_vect) {
	PORTB ^= (1<<PORTB5);
}

int main(void) {
	Initialize();
	while(1);
}