#ifndef WS2812_H
#define WS2812_H

#include <stm32f4xx.h>

//enter number of LEDs here!
#define FRAMEBUFFER_SIZE 16

//Size of Ring-Buffer
#define PWM_BUFFER_SIZE 192


struct led {
	unsigned int red : 16;
	unsigned int green : 16;
	unsigned int blue : 16;
	};
	

struct led diode[FRAMEBUFFER_SIZE];

void ws2812_init(void);

#endif
