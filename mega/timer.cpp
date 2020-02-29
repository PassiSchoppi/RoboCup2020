#include "timer.h"

void timerInit() {
	
	// reset default Arduino clock Controll Register
  	TCCR1A = 0;

	// enable CTC to auto reset clock after CMI
	TCCR1B |= (1 << WGM12);
  	TCCR1B &= ~(1 << WGM13);

  	// set prescaler to 64
  	// set CS02 to 0
  	TCCR1B &= ~(1 << CS12);
  	// set CS01 to 1
  	TCCR1B |= (1 << CS11);
  	// set CS00 to 1
  	TCCR1B |= (1 << CS10);

  	// set clock to 0
  	TCNT1 = t1_load;
  	// set compare register to t0_comp
  	OCR1A = t1_comp;
	
  	// configure the clock 0 to throw an inetrrupt when
  	// the value of OCR1A is reached by clock 0
  	TIMSK1 = (1 << OCIE1A);

  	// enable global interrupts
  	sei();
	
}


// Inerrupt service routine on timer 0 compare match with A
ISR(TIMER1_COMPA_vect) {
	for(uint8_t i=0; i<4; ++i) {
		motorCheckForStepsMade(i);	
	}

}
