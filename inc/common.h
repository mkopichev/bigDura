#ifndef COMMON_H_
#define COMMON_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include "input.h"
#include "pwm.h"
#include "uart.h"

uint8_t digit(uint16_t d, uint8_t m);

#endif