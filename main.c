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

/*//Test Serial
char String[25];

int main(void)
{
	UART_init(BAUD_PRESCALER);

	while(1)
	{
		sprintf(String,"Hello world! \n");
		UART_putstring(String);
		_delay_ms(1000);

		sprintf(String,"The year is %u\n", 2020);
		UART_putstring(String);
		_delay_ms(1000);
	}
}
*/

/*// --Question A.1--


void Initialize() 
{
	DDRB |= (1<<DDB1);
	DDRB |= (1<<DDB2);
	DDRB |= (1<<DDB3);
	DDRB |= (1<<DDB4);
	PORTB |= (1<<PORTB1);
	PORTB |= (1<<PORTB2);
	PORTB |= (1<<PORTB3);
	PORTB |= (1<<PORTB4);
}

int main(void)
{
	Initialize();
	while(1);
}

*/

/*// --Question A.2--

void Initialize()
{
	DDRD &= ~(1<<DDD7);
	DDRB |= (1<<DDB1);
}


int main(void)
{
	Initialize();
	UART_init(BAUD_PRESCALER);
	UART_putstring("Test Serial Print");
	while(1)
	{
		if (PIND & (1<<PIND7))
		{
			PORTB |= (1<<PORTB1);
			UART_putstring("The Light is On (button pressed)\n");
			_delay_ms(20);
		}
		else 
		{
			PORTB &= ~(1<<PORTB1);
			UART_putstring("The Light is Off (button not-pressed)\n");
			_delay_ms(20);
		}
	}
}
*/
/*// --Question A.3--

void Initialize()
{
	DDRD &= ~(1<<DDD7);
	DDRB |= (1<<DDB1);
	DDRB |= (1<<DDB2);
	DDRB |= (1<<DDB3);
	DDRB |= (1<<DDB4);
	PORTB |= (1<<PORTB1);
}

int main(void)
{
	Initialize();
	UART_init(BAUD_PRESCALER);
	UART_putstring("Test Serial Print");
	while(1){
		if ((PIND & (1<<PIND7)) && (PINB & (1<<PORTB1))){
			PORTB &= ~(1<<PORTB1);
			PORTB |= (1<<PORTB2);
			_delay_ms(200);
			UART_putstring("Light1\n");
		}
		else if ((PIND & (1<<PIND7)) && (PINB & (1<<PORTB2))){
			PORTB &= ~(1<<PORTB2);
			PORTB |= (1<<PORTB3);
			_delay_ms(200);
			UART_putstring("Light2\n");
		}
		else if ((PIND & (1<<PIND7)) && (PINB & (1<<PORTB3))){
			PORTB &= ~(1<<PORTB3);
			PORTB |= (1<<PORTB4);
			_delay_ms(200);
			UART_putstring("Light3\n");
		}
		else if ((PIND & (1<<PIND7)) && (PINB & (1<<PORTB4))){
			PORTB &= ~(1<<PORTB4);
			PORTB |= (1<<PORTB1);
			_delay_ms(200);
			UART_putstring("Light4\n");
		}
	}
}
*/

/*// -- Part B --

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
}*/

// --Question 4--

int edge1 = 0;
int edge2 = 0;
double pulse = 0;

void Initialize(){
	cli();
	DDRB &= ~(1<<DDB0);

	TCCR1B |= (1<<CS10);
	TCCR1B &= ~(1<<CS11);
	TCCR1B |= (1<<CS12);

	TCCR1A &= ~(1<<WGM10);
	TCCR1A &= ~(1<<WGM11);
	TCCR1B &= ~(1<<WGM12);
	TCCR1B &= ~(1<<WGM13);

	TCCR1B |= (1<<ICES1);
	TIFR1 |= (1<<ICF1);

	sei();
}


void translate(char message[]) {
	int i = 0;
	char morse_message[5] = {'\0'};
	for (i = 0; i < 5; i++) {
		if ((message[i]) == 's') {
			morse_message[i] = '-';
			UART_putstring(morse_message);
			break;
		}
		else if ((message[i]) == 'd') {
			if ((message[i+1]) == 'd') {
				if((message[i+2]) == 'd') {
					if((message[i+3]) == 'd') {
						morse_message[i] = 'H';
					}
					else {
						morse_message[i] = 'V';
					}
				}
				else if ((message[i+2] == 'a')){
					if ((message[i+3]) == 'd') {
						morse_message[i] = 'F';
					}
					else {
						morse_message[i] = 'U';
					}
				}
			}
			else if ((message[i+1]) == 'a') {
				if ((message[i+2]) == 'd') {
					if ((message[i+3]) == 'd') {
						morse_message[i] = 'L';
						} else {
						morse_message[i] = 'R';
					}
				}
				else if ((message[i+2]) == 'a') {
					if ((message[i+3]) == 'd') {
						morse_message[i] = 'P';
						} else {
						morse_message[i] = 'J';
					}
					} else {
					morse_message[i] = 'W';
				}
			} else {
				morse_message[i] = 'E';
			}
		}
		else {
			if (message[i+1] == 'd') {
				if (message[i+2] == 'd') {
					if (message[i+3] == 'd') {
						morse_message[i] = 'B';
					} 
					else if (message[i+3] == 'a') {
						morse_message[i] = 'X';
					} else {
						morse_message[i] = 'D';
					}
				} else if (message[i+2] == 'a') {
					if (message[i+3] == 'd') {
						morse_message[i] = 'C';
					} else {
						morse_message[i] = 'Y';
					} 
				} else {
					morse_message[i] = 'N';
				}
			} else if (message[i+1] == 'a') {
				if (message[i+2] == 'a') {
					morse_message[i] = 'O';
				} else if (message[i+2] == 'd') {
					if (message[i+3] == 'd') {
						morse_message[i] = 'Z';
					} else if (message[i+3] == 'a') {
						morse_message[i] = 'Q';
					} else {
						morse_message[i] = 'G';
					}
					}
				} else {
					morse_message[i] = 'M';
				}
		} 
	}
}

int main(void)
{
	Initialize();
	UART_init(BAUD_PRESCALER);
	char message[5];
	int count = 0;
	double pulse;
	while(1)
	{
		while (!(TIFR1 & (1<<ICF1)));
		edge1 = ICR1;
		TIFR1 |= (1<<ICF1);
		TCCR1B &= ~(1<<ICES1);
		pulse = edge1-edge2;
		
		if ((pulse) > 20000 && !(message[0]=='0')) 
		{
			PORTB |= (1<<PORTB3);
			_delay_ms(1000);
			PORTB &= ~(1<<PORTB3);
			message[count] = 's';
			message[count+1] =  '\0';
			translate(message);
			count = 0;
		}
			
		while (!(TIFR1 & (1<<ICF1)));
		edge2 = ICR1;
		TIFR1 |= (1<<ICF1);
		TCCR1B |= (1<<ICES1);

		pulse = edge2 - edge1;
		if ((pulse < 2500) && (pulse > 50))
		{
			PORTB |= (1<<PORTB1);
			_delay_ms(400);
			PORTB &= ~(1<<PORTB1);
			message[count] = 'd';
			count = count + 1;
		}
		else if (pulse > 2500) {
			PORTB |= (1<<PORTB2);
			_delay_ms(800);
			PORTB &= ~(1<<PORTB2);
			message[count] = 'a';
			count = count + 1;
		}
	}
}