/*
 * SineLEDs.c
 *
 * License: The Unlicense Public Domain Rights Waiver
 *
 * Created: 27-Aug-16 12:24:23
 * Author : github.com/bithakr
 */ 

 /* Original Arduino Sketch:
 double delayvar = 0;
 void setup(){}
 void loop()  {
	 noInterrupts();
	 while(true){
		 delayvar += 0.00390625*PI;
		 analogWrite(9, 127.5*sin(delayvar-(0.5*PI))+127.5);
		 analogWrite(10, 127.5*sin(delayvar)+127.5);
		 delayMicroseconds(5000);
	 }
 }
 */

#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#define F_CPU 1000000UL /* for delay.h, 1MHz CPU clock */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>
#include "8bitsine.h" /* sinewave lookup table */
#include <math.h>


static uint8_t counter = 0;

static inline void initPWM(void){
/* 
* Since the LEDs are wired using two inverted signals, we can just use one timer
* (Timer2) and set the A and B outputs to different modes.
*/

TCCR0A |= (1 << WGM00) | (1 << WGM01); /* fast PWM, TOP=MAX */
TCCR0B &= ~(1 << WGM02);

TCCR0B |= (1 << CS01); /* 1/8 prescaler */

TCCR0A |= (1 << COM0A1); /* non-inverting mode for OC0A - PD6*/
TCCR0A |= (1 << COM0B1) | (1 << COM0B0); /* inverting for OC0B - PD5*/


DDRD |= (1 << DDD6)|(1 << DDD5); /* set DDRs for output on OC0A/B */

/* debug */
OCR0A = 200;
}

static inline void writeSine(uint8_t c) {
	OCR0A = getSine(c); /* update first comparator unit */
	OCR0B = OCR0A; /*update inverting comparator */
}

int main(void)
{
	/* Initialization code */

	power_adc_disable(); /* save some power */
		
	initPWM(); /* setup Timer0 for 8-bit Fast PWM, 1/8 clkIO prescaler */

	TCNT0 = 0; /* clear Timer0 */

	DDRB = 0xFF;
	PORTB = 0xFF;

	/* debug */
	/* writeSine(100); */

    while (1) 
    {
		/* 
		* pass counter to writeSine(), increment, delay, rinse and repeat...
		*/
		
		writeSine(counter++); 
		_delay_ms(15); /* reduced resolution shouldn't matter here so the abs max is 6.5535 seconds */

    }

}

