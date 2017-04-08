#ifndef __UTIL_H_
#define __UTIL_H_

void pinMode(int base, char num, char mode, char cnf);
void pinOutput(int base, char num, char v);

void uartEnable(int divisor);
void uartSend(int c);
void uartSends(char* s);
void uartSendHex(int x, int d);
void uartSendDec(int x);
void setupPll(int mhz);

#endif

