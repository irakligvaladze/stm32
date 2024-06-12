#include "MAX7219_display.h"

const uint8_t number_0[] = {0b00011000, 
                             0b00100100, 
                             0b00100100, 
                             0b00100100, 
                             0b00100100,
                             0b00100100,
                             0b00011000,
                             0b00000000};

const uint8_t number_1[] = {0b00010000, 
                             0b00011000, 
                             0b00010000, 
                             0b00010000, 
                             0b00010000,
                             0b00010000,
                             0b00111000,
                             0b00000000};

const uint8_t number_2[] = {0b00011000, 
                             0b00100100, 
                             0b00100000, 
                             0b00010000, 
                             0b00001000,
                             0b00000100,
                             0b00111100,
                             0b00000000};
  
const uint8_t number_3[] = {0b00011000, 
                             0b00100100, 
                             0b00100000, 
                             0b00011000, 
                             0b00100000,
                             0b00100100,
                             0b00011000,
                             0b00000000};

const uint8_t number_4[] = {0b00010000, 
                             0b00011000, 
                             0b00010100, 
                             0b00111100, 
                             0b00010000,
                             0b00010000,
                             0b00010000,
                             0b00000000};

const uint8_t number_5[] = {0b00111100, 
                             0b00000100, 
                             0b00011100, 
                             0b00100000, 
                             0b00100000,
                             0b00100100,
                             0b00011000,
                             0b00000000};

const uint8_t number_6[] = {0b00011000, 
                             0b00100100, 
                             0b00000100, 
                             0b00011100, 
                             0b00100100,
                             0b00100100,
                             0b00011000,
                             0b00000000};

const uint8_t number_7[] = {0b00111100, 
                             0b00100000, 
                             0b00010000, 
                             0b00001000, 
                             0b00001000,
                             0b00001000,
                             0b00001000,
                             0b00000000};

const uint8_t number_8[] = {0b00011000, 
                             0b00100100, 
                             0b00100100, 
                             0b00011000, 
                             0b00100100,
                             0b00100100,
                             0b00011000,
                             0b00000000};

const uint8_t number_9[] = {0b00011000, 
                             0b00100100, 
                             0b00100100, 
                             0b00111000, 
                             0b00100000,
                             0b00100100,
                             0b00011000,
                             0b00000000};
const uint8_t number_a[] = {0b00011000, 
                             0b00100100, 
                             0b00100100, 
                             0b00111100, 
                             0b00100100,
                             0b00100100,
                             0b00100100,
                             0b00000000};
const uint8_t number_b[] = {0b00011100, 
                             0b00100100, 
                             0b00100100, 
                             0b00011100, 
                             0b00100100,
                             0b00100100,
                             0b00011100,
                             0b00000000};
const uint8_t number_c[] = {0b0001100, 
                             0b00100100, 
                             0b00000100, 
                             0b00000100, 
                             0b00000100,
                             0b00100100,
                             0b00011000,
                             0b00000000};
const uint8_t number_d[] = {0b00001100, 
                             0b00010100, 
                             0b00100100, 
                             0b00100100, 
                             0b00100100,
                             0b00010100,
                             0b00001100,
                             0b00000000};
const uint8_t number_e[] = {0b00111100, 
                             0b00000100, 
                             0b00000100, 
                             0b00111100, 
                             0b00000100,
                             0b00000100,
                             0b00111100,
                             0b00000000};
const uint8_t number_f[] = {0b00111100, 
                             0b00000100, 
                             0b00000100, 
                             0b00111100, 
                             0b00000100,
                             0b00000100,
                             0b00000100,
                             0b00000000};







														 
unsigned int display_counter = 0;
unsigned int display_timeseconds = 0;


														 

uint8_t display_virtual[DISP_COL][DISP_ROW][8];
					 

// SPI Configuration
void SPI_Config(void) {
    // Enable clock for GPIOA and SPI1
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    // Configure GPIO pins for SPI1
    // PA5 -> SPI1_SCK, PA6 -> SPI1_MISO, PA7 -> SPI1_MOSI
    GPIOA->MODER &= ~((3UL << 10) | (3UL << 12) | (3UL << 14)); // Clear moder bits for PA5, PA6, PA7
    GPIOA->MODER |= (2UL << 10) | (2UL << 12) | (2UL << 14);   // Set alternate function mode
    GPIOA->OSPEEDR |= (3UL << 10) | (3UL << 12) | (3UL << 14); // High speed
    GPIOA->AFR[0] |= (5 << 20) | (5 << 24) | (5 << 28);        // Set AF5 for SPI1

		GPIOA->MODER |= GPIO_MODER_MODER4_0;

		// Set PA4 high (deselect SPI slave)
		GPIOA->BSRR |= GPIO_BSRR_BS4;  // Set pin PA4 high
    // Configure SPI1 in Master mode, CPOL=0, CPHA=0, 8-bit data size
    SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_BR_0 | SPI_CR1_BR_1; // Baud rate = fPCLK/16, enable software slave management
    SPI1->CR1 &= ~SPI_CR1_DFF;  // Set 8-bit data frame format
    SPI1->CR1 |= SPI_CR1_SPE;   // Enable SPI1



}

void SPI_Select(void) {
		GPIOA->BSRR |= GPIO_BSRR_BR4;  // Set pin PA4 low
}

void SPI_Deselect(void) {
    GPIOA->BSRR |= GPIO_BSRR_BS4;  // Set pin PA4 high
}


// SPI Transmit Data
uint8_t SPI_Transmit(uint8_t data) {
    // Wait until transmit buffer is empty
    while (!(SPI1->SR & SPI_SR_TXE));
    
    // Send data
    *(uint8_t *)&SPI1->DR = data;

    // Wait until receive buffer is not empty
    while (!(SPI1->SR & SPI_SR_RXNE));

    // Return the data received from the slave
    return *(uint8_t *)&SPI1->DR;
}




void MAX7219_SendCommand(uint8_t msb, uint8_t lsb){
    GPIOA->BSRR |= GPIO_BSRR_BR4;
    SPI_Transmit(msb);
    SPI_Transmit(lsb);
    GPIOA->BSRR |= GPIO_BSRR_BS4;
	
	
    
}

void MAX7219_SendCommandStealth(uint8_t msb, uint8_t lsb){
    
    SPI_Transmit(msb);
    SPI_Transmit(lsb);
  
}

void MAX7219_DisplayTest(){
	
	for(uint8_t i=0; i<DISP_ROW; i++){
		for(uint8_t j=0; j<DISP_COL; j++){
			for(uint8_t k=0; k<8; k++){
				if((j+1)*(k+1) != DISP_ROW*DISP_COL){
					MAX7219_SendCommandStealth(0x0F, 0x00);
				}else{
					MAX7219_SendCommand(0x0F,0x00);
				}
			}
		}
	}
}

void MAX7219_ScanLimit(){
	for(uint8_t i=0; i<DISP_ROW; i++){
		for(uint8_t j=0; j<DISP_COL; j++){
			for(uint8_t k=0; k<8; k++){
				if((j+1)*(k+1) != DISP_ROW*DISP_COL){
					MAX7219_SendCommandStealth(0x0B, 0x07);
				}else{
					MAX7219_SendCommand(0x0B,0x07);
				}
			}
		}
	}
}

void MAX7219_DecodeMode(){
	for(uint8_t i=0; i<DISP_ROW; i++){
		for(uint8_t j=0; j<DISP_COL; j++){
			for(uint8_t k=0; k<8; k++){
				if((j+1)*(k+1) != DISP_ROW*DISP_COL){
					MAX7219_SendCommandStealth(0x09, 0x00);
				}else{
					MAX7219_SendCommand(0x09,0x00);
				}
			}
		}
	}
}

void MAX7219_ClearDisplay(){
	for(uint8_t i=0; i<8; i++){
		for(uint8_t j=0; j<DISP_ROW; j++){
			for(uint8_t k=0; k<DISP_COL; k++){
				if((j+1)*(k+1) != DISP_ROW*DISP_COL){
					MAX7219_SendCommandStealth(i+1, 0x00);
				}else{
					MAX7219_SendCommand(i+1, 0x00);
				}
			}
		}
	}
}

void MAX7219_SetIntensity(uint8_t intensity){
	
	if(intensity > 0x0F){
		intensity = 0x0F;
	}
	
	for(uint8_t i=0; i<DISP_ROW; i++){
		for(uint8_t j=0; j<DISP_COL; j++){
			for(uint8_t k=0; k<8; k++){
				if((k+1)*(j+1) != DISP_ROW*DISP_COL){
					MAX7219_SendCommandStealth(0x0A, intensity);
				}else{
					MAX7219_SendCommand(0x0A,intensity);
				}
			}
		}
	}
}

void MAX7219_TurnOn(){
	for(uint8_t i=0; i<DISP_ROW; i++){
		for(uint8_t j=0; j<DISP_COL; j++){
			for(uint8_t k=0; k<8; k++){
				if((j+1)*(k+1) != DISP_ROW*DISP_COL-1){
					MAX7219_SendCommandStealth(0x0C, 0x01);
				}else{
					MAX7219_SendCommand(0x0C,0x01);
				}
			}
		}
	}
	
}
void MAX7219_Init(){
    MAX7219_DisplayTest();
    MAX7219_ScanLimit();
		MAX7219_DecodeMode();
		MAX7219_ClearDisplay();
		MAX7219_SetIntensity(0x0F);
		MAX7219_TurnOn();
}

void MAX7219_UpdateDisplay(){
	for(uint8_t i=0; i<8; i++){
		for(uint8_t j=0; j<DISP_ROW; j++){
			for(uint8_t k=0; k<DISP_COL; k++){
				if((j+1)*(k+1) != DISP_ROW*DISP_COL){
					MAX7219_SendCommandStealth(i+1,display_virtual[DISP_COL-1-k][DISP_ROW-1-j][i]);
				}else{
					MAX7219_SendCommand(i+1,display_virtual[DISP_COL-1-k][DISP_ROW-1-j][i]);
				}
			}
		}
	}
}

void MAX7219_SetPoint(int16_t x, int16_t y){
	if((x>=0)&&(x<=X_MAX)&&(y>=0)&&(y<Y_MAX)){
		display_virtual[x/8][y/8][7-y%8] |= 1<<x%8;
	}
}

void MAX7219_ClearVirtualDisplay(){
	for(uint8_t i=0; i<8; i++){
		for(uint8_t j=0; j<DISP_ROW; j++){
			for(uint8_t k=0; k<DISP_COL; k++){
				display_virtual[k][j][i] = 0;
			}
		}
	}
}
