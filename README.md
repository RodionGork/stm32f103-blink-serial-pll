# stm32f103-blink-serial-pll

Initializing stm32f103 mcu to:

- setup PLL to 36 MHz (max from internal oscillator)
- blink 1 Hz at PA1 (pin-11 in lqfp-48)
- send incrementing numbers via USART1 at 921600 baud