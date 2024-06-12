#include "graphic.h"

void Graphic_SetPixel(float x, float y){
	MAX7219_SetPoint(x, y);
}


void Graphic_Line(float x1, float y1, float x2, float y2, float thickness){
	
	// fill x axis
	float k = (y2-y1)/(x2-x1);
	
	if(x1>x2){
		int16_t xint = x2;
		float yfloat = y2;
		for(; xint <= x1; xint++){
			yfloat = y2+k*(xint-x2);
			if((y2-y1)>0){
				if((xint<=x1)&&(xint>=x2)&&(yfloat>=y1)&&(yfloat<=y2)){
					MAX7219_SetPoint(xint, yfloat);
				}
			}else{	
				if((xint<=x1)&&(xint>=x2)&&(yfloat<=y1)&&(yfloat>=y2)){
					MAX7219_SetPoint(xint, yfloat);
				}
			}
		}
	} else {
		int16_t xint = x1;
		float yfloat = y1;
		for(; xint <= x2; xint++){
			yfloat = y1+k*(xint-x1);
			if((y2-y1)>0){
				if((xint>=x1)&&(xint<=x2)&&(yfloat>=y1)&&(yfloat<=y2)){
					MAX7219_SetPoint(xint, yfloat);
				}
			}else{	
				if((xint>=x1)&&(xint<=x2)&&(yfloat<=y1)&&(yfloat>=y2)){
					MAX7219_SetPoint(xint, yfloat);
				}
			}
		}	
	}
	
	// fill y axis
	if(y1>y2){
		int16_t yint = y2;
		float xfloat = x2;
		for(; yint <= y1; yint++){
			xfloat = x2+(yint-y2)/k;
			if((x2-x1)>0){
				if((yint>=y2)&&(yint<=y1)&&(xfloat<=x2)&&(xfloat>=x1)){
					MAX7219_SetPoint(xfloat, yint);
				}
			}else{	
				if((yint>=y2)&&(yint<=y1)&&(xfloat>=x2)&&(xfloat<=x1)){
					MAX7219_SetPoint(xfloat, yint);
				}
			}
		}
	} else {
		int16_t yint = y1;
		float xfloat = x1;
		for(; yint <= y2; yint++){
			xfloat = x1+(yint-y1)/k;
			if((x2-x1)>0){
				if((yint<=y2)&&(yint>=y1)&&(xfloat<=x2)&&(xfloat>=x1)){
					MAX7219_SetPoint(xfloat, yint);
				}
			}else{	
				if((yint<=y2)&&(yint>=y1)&&(xfloat>=x2)&&(xfloat<=x1)){
					MAX7219_SetPoint(xfloat, yint);
				}
			}
		}
	}
}

void Graphic_ThreePointLines(float x1, float y1, float x2, float y2, float  x3, float y3, uint8_t fill){
	Graphic_Line(x1, y1, x2, y2, 1);
	Graphic_Line(x2, y2, x3, y3, 1);
	Graphic_Line(x3, y3, x1, y1, 1);
	
}
void Graphic_FourPointLines(float x1, float y1, float x2, float y2, float  x3, float y3, float x4, float y4, uint8_t fill){
	Graphic_Line(x1, y1, x2, y2, 1);
	Graphic_Line(x2, y2, x3, y3, 1);
	Graphic_Line(x3, y3, x4, y4, 1);
	Graphic_Line(x4, y4, x1, y1, 1);
	
}
void Graphic_Circle(float x1, float y1, float radius, uint8_t fill){
	// fill x axis
	for(int16_t xint = x1-radius; xint<=x1+radius; xint++){
		float y = sqrt(pow(radius,2) - pow(x1-xint,2));
		if(((y1+y)>= (y1-radius))&&((y1+y)<= (y1+radius))){
			MAX7219_SetPoint(xint, y1+y);
			MAX7219_SetPoint(xint, y1-y);
		}
		
	}
	
	// fill y axis
	for(int16_t yint = y1-radius; yint<=y1+radius; yint++){
		float x = sqrt(pow(radius,2) - pow(y1-yint,2));
		if(((x1+x)>= (x1-radius))&&((x1+x)<= (x1+radius))){
			MAX7219_SetPoint(x1-x, yint);
			MAX7219_SetPoint(x1+x, yint);
		}
		
	}
	
	if(fill){
		for(uint16_t r=0; r<radius; r++){
			// fill x axis
			for(int16_t xint = x1-r; xint<=x1+r; xint++){
				float y = sqrt(pow(r,2) - pow(x1-xint,2));
				if(((y1+y)>= (y1-r))&&((y1+y)<= (y1+r))){
					MAX7219_SetPoint(xint, y1+y);
					MAX7219_SetPoint(xint, y1-y);
				}
				
			}
			
			// fill y axis
			for(int16_t yint = y1-r; yint<=y1+r; yint++){
				float x = sqrt(pow(r,2) - pow(y1-yint,2));
				if(((x1+x)>= (x1-r))&&((x1+x)<= (x1+r))){
					MAX7219_SetPoint(x1-x, yint);
					MAX7219_SetPoint(x1+x, yint);
				}				
			}
		}
	}
}

void Graphic_Rectangle(float x1, float y1, float width, float height, uint8_t fill){
	Graphic_FourPointLines(x1, y1, x1+width, y1, x1, y1+height, x1+width, y1+height, fill);
	

}
