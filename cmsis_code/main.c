#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "system_initialization.h"
#include "usart.h"

#define LED_PIN 5

void setup() {


  clock_init(); // sets clock to external oscillator HSE_VALUE
  sysTick_init(); // for enabling functions like delay
  usart6_init(115200); // to enable printf and other functions

  // GPIO Enable
  RCC->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOAEN_Pos);
  
  // do two dummy reads after enabling the peripheral clock, as per the errata
  volatile uint32_t dummy;
  dummy = RCC->AHB1ENR;
  dummy = RCC->AHB1ENR;

  GPIOA->MODER |= (1 << GPIO_MODER_MODER5_Pos);
  
}


void main(void)    
{  
  
  setup();
  
  while (1)
  {
    GPIOA->ODR ^= (1 << LED_PIN);
    delay_ms(500);
    printf("[%.3f] Hello, World, It's commited!\r\n", (float)ticks/1000.0f);

  }
}