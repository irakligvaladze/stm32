#ifndef USART_H
#define USART_H

#include "stm32f4xx.h"

#define LED_PIN 5

void usart6_init(uint32_t baud_rate);
int _write(int file, char *ptr, int len);
void usart6_write(USART_TypeDef *usart, char c);
int _close(int file);
int _lseek(int file, int ptr, int dir);
int _read(int file, char *ptr, int len);
int _isatty(int file);
int _kill(int pid, int sig);
int _getpid(void);

#endif // USART_H