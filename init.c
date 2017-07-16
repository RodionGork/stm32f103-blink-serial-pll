#define STACK_TOP 0x20005000

extern unsigned char  INIT_DATA_VALUES;
extern unsigned char  INIT_DATA_START;
extern unsigned char  INIT_DATA_END;
extern unsigned char  BSS_START;
extern unsigned char  BSS_END;
extern unsigned char  BSS_END;

void init(void);
int main(void);
void uartIrqHandler(void);

const void * intVectors[76] __attribute__((section(".vectors"))) = {
    (void*) STACK_TOP,
    init,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0, uartIrqHandler,
};

void memoryInit(void) {
    unsigned char *src;
    unsigned char *dest;
    unsigned len;
    src= &INIT_DATA_VALUES;
    dest= &INIT_DATA_START;
    len= &INIT_DATA_END-&INIT_DATA_START;
    while (len--)
        *dest++ = *src++;
    dest = &BSS_START;
    len = &BSS_END - &BSS_START;
    while (len--)
        *dest++=0;
}

void init(void) {
    memoryInit();
    main();
}


