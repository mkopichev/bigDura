#include "../inc/common.h"

uint8_t digit(uint16_t d, uint8_t m) {

    uint8_t i = 5, a;
    while(i) {      // цикл по разрядам числа
        a = d % 10; // выделяем очередной разряд
        // выделен заданный разряд - уходим
        if(i-- == m)
            break;
        d /= 10; // уменьшаем число в 10 раз
    }
    return (a);
}