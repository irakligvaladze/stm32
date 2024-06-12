#include "stm32f4xx.h"
#include <stdint.h>
#include "graphic.h"
#include "delay.h"
#include "uart.h"


#define CALC_PERIOD_MS 5

float radius = 3;
float x_ball= 16;
float y_ball = 4;
float vx = 10;
float vy = 0;
float ax = 0;
float ay = 10;


void calculateAcceleration(){

}

void calculateVelocity(){
	vx += ax*CALC_PERIOD_MS/1000;
	vy += ay*CALC_PERIOD_MS/1000;
}

void calculatePosition(){
	float deltaVx = vx*CALC_PERIOD_MS/1000;
	if(((x_ball+deltaVx+radius)>X_MAX)||((x_ball+deltaVx-radius)<0)){
		vx *= -0.9;
	} else {
		x_ball+= deltaVx;
	}
	
	float deltaVy = vy*CALC_PERIOD_MS/1000;
	if(((y_ball+deltaVy+radius)>Y_MAX)||((y_ball+deltaVy-radius)<0)){
		vy *= -0.9;
	} else {
		y_ball += deltaVy;
	}
}

int main(void) {

		TIM_Config();

    // Enable timer interrupt in NVIC
    NVIC_EnableIRQ(TIM2_IRQn);
		
		
		UART_Init();
		
	  UART_SendByte(3);
    SPI_Config();
		MAX7219_Init();
	

		MAX7219_ClearVirtualDisplay();
		MAX7219_SetPoint(x_ball,y_ball);
		MAX7219_UpdateDisplay();
	
		uint32_t time0 = millis();
		
		uint32_t counter = 9;
		uint8_t direction = 0;
		for(uint8_t i = 0; i<X_MAX; i++){
					for(uint8_t j=0; j<Y_MAX+1; j++){
						Graphic_SetPixel(i, j);
					}
				}
		MAX7219_UpdateDisplay();
    while (1) {
			
			
			if((millis()-time0)>=CALC_PERIOD_MS){
			
			
				
				time0 = millis();
				//UART_SendByte('a');
				calculateAcceleration();
				calculateVelocity();
				calculatePosition();
				//MAX7219_ClearVirtualDisplay();
				
				
				
			
				
			}
		
		}
					
		while(1);
}
