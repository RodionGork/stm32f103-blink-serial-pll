.equ RCC_BASE, 0x40021000
.equ AFIO_BASE, 0x40010000
.equ GPIOA_BASE, 0x40010800
.equ GPIOB_BASE, 0x40010C00
.equ USART_BASE, 0x40013800

.equ RCC_CR, 0x00
.equ RCC_CFGR, 0x04
.equ RCC_APB2ENR, 0x18

.equ GPIO_CRL, 0x00
.equ GPIO_CRH, 0x04
.equ GPIO_ODR, 0x0C
.equ GPIO_BSRR, 0x10

.equ AFIO_MAPR, 0x04

.equ USART_SR, 0x00
.equ USART_DR, 0x04
.equ USART_BRR, 0x08
.equ USART_CR1, 0x0C
.equ USART_CR2, 0x10

.equ PIN_MODE_IN, 0
.equ PIN_MODE_OUT, 1
.equ PIN_MODE_OUT_FAST, 3
.equ PIN_MODE_OUT_SLOW, 2

.equ PIN_CNF_I_ANA, 0
.equ PIN_CNF_I_FLT, 4
.equ PIN_CNF_I_PULL, 8

.equ PIN_CNF_O_PP, 0
.equ PIN_CNF_O_OD, 4
.equ PIN_CNF_O_APP, 8
.equ PIN_CNF_O_AOD, 12

.macro initAfioAndGpios mask
    store32masked (RCC_BASE + RCC_APB2ENR), 1, 1
    store32masked (RCC_BASE + RCC_APB2ENR), (0x7F << 2), (\mask << 2)
    store32masked (AFIO_BASE + AFIO_MAPR), (7 << 24), (4 << 24)
.endm

.macro pinMode baseAddr, pin, mode
    store32masked (\baseAddr + GPIO_CRL + (\pin / 8) * 4), (0xF << ((\pin % 8) * 4)), (\mode << ((\pin % 8) * 4))
.endm
