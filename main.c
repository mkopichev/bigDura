#include "inc/common.h"

int main(void) {

    counterInit();
    pwmInit();
    uartInit();
    while(1) {

        pwmGo();
    }
}