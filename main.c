#include "stm32f103.h"

#include "util.h"

int main() {
    setupPll(36);
    int n, i;
    REG_L(RCC_BASE, RCC_APB2ENR) |= (1 << 2); // port A
    
    pinMode(GPIOA_BASE, 1, PIN_MODE_OUT_SLOW, PIN_CNF_O_PP);
    
    uartEnable(36000000 / 921600);
    enableInterrupts();
    uartSends("Started...\n");
    
    while(1) {
        pinOutput(GPIOA_BASE, 1, 1);
        n=600000; while(--n);
        pinOutput(GPIOA_BASE, 1, 0);
        n=3000000; while(--n);
        while (1) {
            i = uartRead();
            if (i < 0) {
                break;
            }
            uartSend(i);
            if (i == '\r') {
                uartSend('\n');
            }
        }
    }    
}

