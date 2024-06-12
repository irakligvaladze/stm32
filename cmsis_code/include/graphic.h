#ifndef GRAPHIC_H
#define GRAPHIC_H


#include <stdint.h>
#include <math.h>
#include "MAX7219_display.h"

void Graphic_SetPixel(float, float);
void Graphic_Line(float, float, float, float, float);
void Graphic_ThreePointLines(float, float, float, float, float, float, uint8_t);
void Graphic_FourPointLines(float, float, float, float, float, float, float, float,uint8_t);
void Graphic_Circle(float, float, float, uint8_t);
void Graphic_Rectangle(float, float, float, float, uint8_t);

#endif // GRAPHIC_H