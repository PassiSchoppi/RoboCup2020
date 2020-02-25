#include "timer.h"

void timerInit() {
	
	// reset default Arduino clock Controll Register
  	TCCR0A = 0;

	// enable CTC to auto reset clock after CMI
  	TCCR0A &= ~(1 << WGM02);
  	TCCR0A |= (1 << WGM01);
  	TCCR0A &= ~(1 << WGM00);

  	// set prescaler to 64
  	// set CS02 to 0
  	TCCR0B &= ~(1 << CS02);
  	// set CS01 to 1
  	TCCR0B |= (1 << CS01);
  	// set CS00 to 1
  	TCCR0B |= (1 << CS00);

  	// set clock to 0
  	TCNT0 = t0_load;
  	// set compare register to t0_comp
  	OCR0A = t0_comp;
	
  	// configure the clock 0 to throw an inetrrupt when
  	// the value of OCR0A is reached by clock 0
  	TIMSK0 = (1 << OCIE0A);

  	// enable global interrupts
  	sei();
	
}


// Inerrupt service routine on timer 0 compare match with A
ISR(TIMER0_COMPA_vect) {

	for(uint8_t i=0; i<4; ++i) {
		checkForStepsMade(i);	
	}

}
