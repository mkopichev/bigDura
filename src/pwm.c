#include "../inc/pwm.h"

extern int16_t verticalChannel, horizontalChannel;
int16_t leftWheel = 0, rightWheel = 0;

void pwmInit(void) {

    DDRB |= (1 << 1) | (1 << 2);                                          // speed wheel 1
    DDRD |= (1 << 5) | (1 << 6);                                          // speed wheel 2
    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);                // fast pwm 8 bit wheel 1
    TCCR1B = (1 << WGM12) | (1 << CS11);                                  // prescaler 8, pwm freq 7,812 kHz
    TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00) | (1 << WGM01); // fast pwm 8 bit wheel 2
    TCCR0B = (1 << CS01);                                                 // prescaler 8, pwm freq 7,812 kHz
}

void motionCalculations(void) {

    if(verticalChannel >= 0) {

        leftWheel = verticalChannel + horizontalChannel;
        rightWheel = verticalChannel - horizontalChannel;
    } else {

        leftWheel = verticalChannel - horizontalChannel;
        rightWheel = verticalChannel + horizontalChannel;
    }
    leftWheel *= 2;
    rightWheel *= 2;
    if(leftWheel > 250) {

        leftWheel = 250;
    }
    if(leftWheel < -250) {

        leftWheel = -250;
    }
    if(rightWheel > 250) {

        rightWheel = 250;
    }
    if(rightWheel < -250) {

        rightWheel = -250;
    }
}

void pwmGo(void) {

    motionCalculations();

    if(leftWheel > DEAD_ZONE_UPPER_LEVEL) {

        LEFT_WHEEL_FORWARD = leftWheel;
        LEFT_WHEEL_BACKWARD = 0;
    } else if(leftWheel < DEAD_ZONE_LOWER_LEVEL) {

        LEFT_WHEEL_BACKWARD = -leftWheel;
        LEFT_WHEEL_FORWARD = 0;
    } else {

        LEFT_WHEEL_FORWARD = LEFT_WHEEL_BACKWARD = 0;
    }

    if(rightWheel > DEAD_ZONE_UPPER_LEVEL) {

        RIGHT_WHEEL_FORWARD = rightWheel;
        RIGHT_WHEEL_BACKWARD = 0;
    } else if(rightWheel < DEAD_ZONE_LOWER_LEVEL) {

        RIGHT_WHEEL_BACKWARD = -rightWheel;
        RIGHT_WHEEL_FORWARD = 0;
    } else {

        RIGHT_WHEEL_FORWARD = RIGHT_WHEEL_BACKWARD = 0;
    }

    uartTransmitDec(verticalChannel);
    uartTransmitStr("\t");
    uartTransmitDec(horizontalChannel);
    uartTransmitStr("\t");
    uartTransmitDec(leftWheel);
    uartTransmitStr("\t");
    uartTransmitDec(rightWheel);
    uartTransmitStr("\t");
    uartTransmitDec(LEFT_WHEEL_FORWARD);
    uartTransmitStr("\t");
    uartTransmitDec(LEFT_WHEEL_BACKWARD);
    uartTransmitStr("\t");
    uartTransmitDec(RIGHT_WHEEL_FORWARD);
    uartTransmitStr("\t");
    uartTransmitDec(RIGHT_WHEEL_BACKWARD);
    uartTransmitStr("\r\n");

    // if(verticalChannel > DEAD_ZONE_UPPER_LEVEL) {

    //     LEFT_WHEEL_BACKWARD = ((verticalChannel - DEAD_ZONE_UPPER_LEVEL) * SCALE_COEF);
    //     LEFT_WHEEL_FORWARD = 0;
    // } else if(verticalChannel < DEAD_ZONE_LOWER_LEVEL) {

    //     LEFT_WHEEL_FORWARD = ((DEAD_ZONE_LOWER_LEVEL - verticalChannel) * SCALE_COEF);
    //     LEFT_WHEEL_BACKWARD = 0;
    // } else {

    //     LEFT_WHEEL_FORWARD = 0;
    //     LEFT_WHEEL_BACKWARD = 0;
    // }
    // _delay_ms(2);
    // if(horizontalChannel > DEAD_ZONE_UPPER_LEVEL) {

    //     RIGHT_WHEEL_BACKWARD = ((horizontalChannel - DEAD_ZONE_UPPER_LEVEL) * SCALE_COEF);
    //     RIGHT_WHEEL_FORWARD = 0;
    // } else if(horizontalChannel < DEAD_ZONE_LOWER_LEVEL) {

    //     RIGHT_WHEEL_FORWARD = ((DEAD_ZONE_LOWER_LEVEL - horizontalChannel) * SCALE_COEF);
    //     RIGHT_WHEEL_BACKWARD = 0;
    // } else {

    //     RIGHT_WHEEL_BACKWARD = 0;
    //     RIGHT_WHEEL_FORWARD = 0;
    // }
    // _delay_ms(2);
}