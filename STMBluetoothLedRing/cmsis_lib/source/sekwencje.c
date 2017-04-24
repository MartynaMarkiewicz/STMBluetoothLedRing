#include "stm32f4xx_conf.h"
#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_tim.h>
#include <stm32f4xx_dma.h>
#include <stm32f4xx_usart.h>
#include "stm32f4xx_exti.h"
#include <misc.h>
#include "delay.h"
#include "ws2812.h"
#include "stm32f4xx_usart.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

//sekwencje a-f
void s1()
{
	int i=0;
	for(i=0;i<8;i++)
	{
		diode[i].blue=200;
		delay_ms(250);
		diode[i].red = diode[i].green = diode[i].blue = 255;
		delay_ms(500);
	}
	clear();
}

void s2()
{
	int i=0;
	for(i=0;i<8;i++)
	{
		diode[i].red=195;
		diode[i].green=111;
		diode[i].blue=0;
		delay_ms(100);
	}

	for(i=0;i<8;i++)
	{
		diode[i].red=100;
		delay_ms(100);
	}

	for(i=0;i<8;i++)
	{
		diode[i].red=255;
		diode[i].green=0;
		diode[i].blue=51;
		delay_ms(100);
	}

	for(i=0;i<8;i++)
	{
		diode[i].red=19;
		diode[i].green=0;
		diode[i].blue=207;
		delay_ms(100);
	}

	for(i=0;i<8;i++)
	{
		diode[i].red=0;
		diode[i].green=243;
		diode[i].blue=75;
		delay_ms(100);
	}
}

void s3()
{
	int i=0;
	for(i=0;i<8;i++)
	{
		diode[i].blue=0;
		delay_ms(100);
	}
	for(i=0;i<8;i++)
	{
		diode[i].blue=20;
		delay_ms(100);
	}
	for(i=0;i<8;i++)
	{
		diode[i].blue=50;
		delay_ms(100);
	}
	for(i=0;i<8;i++)
	{
		diode[i].blue=70;
		delay_ms(100);
	}
	for(i=0;i<8;i++)
	{
		diode[i].blue=100;
		delay_ms(100);
	}
	for(i=0;i<8;i++)
	{
		diode[i].blue=120;
		delay_ms(100);
	}
	for(i=0;i<8;i++)
	{
		diode[i].blue=150;
		delay_ms(100);
	}
	for(i=0;i<8;i++)
	{
		diode[i].blue=170;
		delay_ms(100);
	}
	for(i=0;i<8;i++)
	{
		diode[i].blue=200;
		delay_ms(100);
	}
}

void s4()
{
	int i=0;
	for(i=0;i<8;i++)
	{
		diode[i].green=diode[i].blue=diode[i].red=255;
		delay_ms(50);
		diode[i].green=diode[i].blue=diode[i].red=200;
		delay_ms(50);
		diode[i].green=diode[i].blue=diode[i].red=155;
		delay_ms(50);
		diode[i].green=diode[i].blue=diode[i].red=100;
		delay_ms(50);
		diode[i].green=diode[i].blue=diode[i].red=55;
		delay_ms(50);
		diode[i].green=diode[i].blue=diode[i].red=15;
		delay_ms(50);
		diode[i].green=diode[i].blue=diode[i].red=5;
		delay_ms(250);
	}
	for(i=0;i<8;i++)
	{
		diode[i].green=diode[i].blue=diode[i].red=255;
	}
	for(i=0;i<8;i++)
	{
//		delay_ms(250);
		diode[i].green=diode[i].blue=diode[i].red=255;
		delay_ms(50);
		diode[i].green=diode[i].blue=diode[i].red=200;
		delay_ms(50);
		diode[i].green=diode[i].blue=diode[i].red=155;
		delay_ms(50);
		diode[i].green=diode[i].blue=diode[i].red=100;
		delay_ms(50);
		diode[i].green=diode[i].blue=diode[i].red=55;
		delay_ms(50);
		diode[i].green=diode[i].blue=diode[i].red=15;
		delay_ms(50);
		diode[i].green=diode[i].blue=diode[i].red=5;
		delay_ms(250);
	}
	clear();
}

void s5()
{
	int i=0;

			for(i=0;i<8;i++)
			{
				diode[i].green=diode[i].blue=diode[i].red=10;
				delay_ms(50);
			}
			for(i=0;i<8;i++)
			{
				diode[i].green=diode[i].blue=diode[i].red=50;
				delay_ms(50);
			}
			for(i=0;i<8;i++)
			{
				diode[i].green=diode[i].blue=diode[i].red=100;
				delay_ms(50);
			}
			for(i=0;i<8;i++)
			{
				diode[i].green=diode[i].blue=diode[i].red=150;
				delay_ms(50);
			}
			for(i=0;i<8;i++)
			{
				diode[i].green=diode[i].blue=diode[i].red=200;
				delay_ms(50);
			}
			for(i=0;i<8;i++)
			{
				diode[i].green=diode[i].blue=diode[i].red=250;
				delay_ms(50);
			}
			for(i=0;i<8;i++)
			{
				diode[i].green=diode[i].blue=diode[i].red=250;
				delay_ms(50);
			}
			for(i=0;i<8;i++)
			{
				diode[i].green=diode[i].blue=diode[i].red=200;
				delay_ms(50);
			}
			for(i=0;i<8;i++)
			{
				diode[i].green=diode[i].blue=diode[i].red=100;
				delay_ms(50);
			}
			for(i=0;i<8;i++)
			{
				diode[i].green=diode[i].blue=diode[i].red=50;
				delay_ms(50);
			}
			for(i=0;i<8;i++)
			{
				diode[i].green=diode[i].blue=diode[i].red=10;
				delay_ms(50);
			}
			for(i=0;i<8;i++)
			{
				diode[i].green=diode[i].blue=diode[i].red=0;
				delay_ms(50);
			}
			clear();
}

void s6()
{
	int i=0;
			for(i=0;i<8;i++)
			{
				diode[i].red=255;
			}
			delay_ms(550);
			for(i=0;i<8;i++)
			{
				diode[i].red=150;
			}
			delay_ms(550);
			for(i=0;i<8;i++)
			{
				diode[i].red=50;
			}
			delay_ms(550);
			for(i=0;i<8;i++)
			{
				diode[i].red=10;
			}
			delay_ms(550);
			clear_all();
			//////////////////////////BLUE//////////////////////////
			for(i=0;i<8;i++)
			{
				diode[i].blue=255;
			}
			delay_ms(550);
			for(i=0;i<8;i++)
			{
				diode[i].blue=150;
			}
			delay_ms(550);
			for(i=0;i<8;i++)
			{
				diode[i].blue=50;
			}
			delay_ms(550);
			for(i=0;i<8;i++)
			{
				diode[i].blue=10;
			}
			delay_ms(550);
			clear_all();
			//////////////////////////GREEN//////////////////////////
			for(i=0;i<8;i++)
			{
				diode[i].green=255;
			}
			delay_ms(550);
			for(i=0;i<8;i++)
			{
				diode[i].green=150;
			}
			delay_ms(550);
			for(i=0;i<8;i++)
			{
				diode[i].green=50;
			}
			delay_ms(550);
			for(i=0;i<8;i++)
			{
				diode[i].green=10;
			}
			delay_ms(550);
			clear_all();
}

void s7()
{
}

void s10()
{
	int i=0;
for(i=0;i<8;i++)
{
	diode[0].red=255; diode[0].green=255; diode[0].blue=225;
	delay_ms(150);
	diode[1].red=255; diode[1].green=0;	  diode[1].blue=225;
	delay_ms(150);
	diode[2].red=255; diode[2].green=0;   diode[2].blue=0;
	delay_ms(150);
	diode[3].red=255; diode[3].green=69;  diode[3].blue=0; //orange
	delay_ms(150);
	diode[4].red=255; diode[4].green=255; diode[4].blue=0;
	delay_ms(150);
	diode[5].red=0;   diode[5].green=255; diode[5].blue=0;
	delay_ms(150);
	diode[6].red=0;   diode[6].green=0;   diode[6].blue=225;
	delay_ms(150);
	diode[7].red=0;   diode[7].green=0;   diode[7].blue=139;
	delay_ms(50);
		clear_s(150);

	//clear_s(150);
	//////////////////////////////////////////////////////////
	diode[7].red=0;   diode[7].green=0;   diode[7].blue=139;
		delay_ms(150);
	diode[6].red=0;   diode[6].green=0;   diode[6].blue=225;
		delay_ms(150);
	diode[5].red=0;   diode[5].green=255; diode[5].blue=0;
		delay_ms(150);
	diode[4].red=255; diode[4].green=255; diode[4].blue=0;
		delay_ms(150);
	diode[3].red=255; diode[3].green=69;  diode[3].blue=0; //orange
		delay_ms(150);
	diode[2].red=255; diode[2].green=0;   diode[2].blue=0;
		delay_ms(150);
	diode[1].red=255; diode[1].green=0;	  diode[1].blue=225;
		delay_ms(150);
	diode[0].red=255; diode[0].green=255; diode[0].blue=225;
		delay_ms(150);
		clear_s(150);
}
	////////////////////////////////////////////////////////
}


void s12()
{
	int i=0;
	for(i=0;i<8;i++)
	{
		diode[i].red=255;
		delay_ms(100);
		clear_s(50);
		diode[i+1].green=255;
		delay_ms(100);
		clear_s(50);
		diode[i+2].blue=255;
		delay_ms(100);
		clear_s(50);
	}
}
