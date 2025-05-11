#ifndef IMAGE_H_
#define IMAGE_H_
#include "stm32f4xx_hal.h"
typedef struct
{
    uint16_t width;         
    uint16_t height;        
    const uint16_t *data;   
} Image;

extern const uint16_t image_data[];
extern const Image IMG;

#endif