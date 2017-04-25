.include "macros.i"
.include "stm32f103.i"

.syntax unified
.thumb

.equ CPU_CLK_MHZ, 48

.section .vectors
.align
.long __stack_top
.long reset_handler

.text
.align

crlf_str:
    .asciz "\r\n"
.align

.thumb_func
reset_handler:
    
    ldr r0, = CPU_CLK_MHZ
    bl init_with_pll
    
    initAfioAndGpios 0x3
    
    ldr r0, = (CPU_CLK_MHZ * 1000000 / 115200)
    bl init_uart
    
    pinMode GPIOB_BASE, 7, (PIN_MODE_OUT + PIN_CNF_O_PP)
    
    ldr r3, = 0
    
    blink:

    store32imm (GPIOB_BASE + GPIO_ODR), (1 << 7)
    ldr r0, = 0x500000
    bl delay_r0
    store32imm (GPIOB_BASE + GPIO_ODR), 0
    ldr r0, = 0x100000
    bl delay_r0
    
    mov r0, r3
    add r3, 3
    ldr r1, = 4
    bl uart_send_dec
    ldr r0, = crlf_str
    bl uart_send_str
    
    b blink

.thumb_func
delay_r0:
    push {lr}
    delay_loop:
    subs r0, 1
    bne delay_loop
    pop {pc}
    
