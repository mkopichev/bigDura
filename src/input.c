#include "../inc/input.h"

int16_t verticalChannel = 0, horizontalChannel = 0;

void counterInit(void) {

    DDRD &= ~((1 << 2) | (1 << 3));      // int 0 and int 1
    EICRA = (1 << ISC00) | (1 << ISC10); // any logical change
    EIMSK = (1 << INT0) | (1 << INT1);
    TCCR2B = (1 << CS22); // prescaler 256, counter period 4080 us
    sei();
}

ISR(INT0_vect) {

    if(PIND & (1 << 2)) {

        EIMSK &= ~(1 << INT1);
        TCNT2 = 0;
    } else {

        verticalChannel = TCNT2;
        verticalChannel -= 110;
        verticalChannel *= -1;
        EIMSK |= (1 << INT1);
    }
}

ISR(INT1_vect) {

    if(PIND & (1 << 3)) {

        EIMSK &= ~(1 << INT0);
        TCNT2 = 0;
    } else {

        horizontalChannel = TCNT2;
        horizontalChannel -= 110;
        horizontalChannel *= -1;
        EIMSK |= (1 << INT0);
    }
}