#ifndef SYSTEM_INITIALIZATION_H
#define SYSTEM_INITIALIZATION_H

#include "stm32f4xx.h"

extern uint32_t ticks;

void clock_init(void);
void sysTick_init(void);
void delay_ms(uint32_t); //delay milliseconds
void systick_handler(void);


#endif // SYSTEM_INITIALIZATION_H