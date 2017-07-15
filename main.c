#include "stm32f103.h"

#include "util.h"

char buf[16];
int bufCnt = 0;

void onUartReceive(void) {
    buf[bufCnt++] = uartRead();
}

int main() {
    setupPll(36);
    int n, i;
    REG_L(RCC_BASE, RCC_APB2ENR) |= (1 << 2); // port A
    
    pinMode(GPIOA_BASE, 1, PIN_MODE_OUT_SLOW, PIN_CNF_O_PP);
    
    //Vectors[16 + 37] = onReceive;
    uartEnable(36000000 / 921600);
    uartSends("Started...");
    uartSendHex((int)Vectors[0], 8);
    uartSend('\n');
    uartSendHex((int)Vectors[1], 8);
    uartSend('\n');
    REG_L(NVIC_BASE, NVIC_ISER + (37 / 32) * 4) |= (1 << (37 % 32)); // enable interrupt
    __asm("cpsie i");
    while(1) {
        pinOutput(GPIOA_BASE, 1, 1);
        n=600000; while(--n);
        pinOutput(GPIOA_BASE, 1, 0);
        n=3000000; while(--n);
        uartSendDec(bufCnt);
        uartSend('\n');
        bufCnt = 0;
    }    
}

