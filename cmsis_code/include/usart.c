#include "usart.h"

void usart6_init(uint32_t baud_rate){
    // Enable the USART6 and GPIOC clocks
    RCC->APB2ENR |= RCC_APB2ENR_USART6EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

    // Configure GPIOC pins 6 and 7 for USART6 (TX and RX)
    GPIOC->MODER &= ~(GPIO_MODER_MODER6 | GPIO_MODER_MODER7); // Clear current settings
    GPIOC->MODER |= (GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1); // Set to alternate function
    GPIOC->AFR[0] &= ~((0xF << 24) | (0xF << 28)); // Clear alternate function bits
    GPIOC->AFR[0] |= (8 << 24) | (8 << 28); // Set alternate function to AF8 (USART6)

    // Configure USART6
    USART6->BRR = (SystemCoreClock / baud_rate); // Set baud rate to 9600 (assuming 16 MHz PCLK2)
    USART6->CR1 |= USART_CR1_TE | USART_CR1_RE; // Enable transmitter and receiver
    USART6->CR1 |= USART_CR1_UE; // Enable USART

    // Optional: Enable USART interrupt (if needed)
    // NVIC_EnableIRQ(USART6_IRQn);
}

// Implement _write for printf
int _write(int file, char *ptr, int len) {
    int i;
    for (i = 0; i < len; i++) {
        // Output each character using your USART implementation
        usart6_write(USART2, ptr[i]); // Assuming USART2
    }
    return len;
}

void usart6_write(USART_TypeDef *usart, char c)
{
    while (!(USART6->SR & USART_SR_TXE)); // Wait until transmit data register is empty
    USART6->DR = c; // Transmit character
}

// Implementations of other functions (_close, _lseek, _read, _fstat, _isatty) can be minimal or stubs if not needed
int _close(int file) {
    return -1; // Not implemented
}

int _lseek(int file, int ptr, int dir) {
    return 0; // Not implemented
}

int _read(int file, char *ptr, int len) {
    return 0; // Not implemented
}

int _fstat(int file, struct stat *st) {
    return 0; // Not implemented
}

int _isatty(int file) {
    return 1; // This is a terminal
}

int _kill(int pid, int sig) {
    // Minimal implementation, return error
    return -1;
}

int _getpid(void) {
    // Minimal implementation, return a fixed value
    return 1;  // Return a fixed process ID (PID)
}