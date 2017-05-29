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
void seq1(int k, int j)
{
	int i=0;
	for(i=k;i<j;i++)
	{
		diode[i].blue=200;
		delay_ms(250);
		diode[i].red = diode[i].green = diode[i].blue = 255;
		delay_ms(500);
	}
	clear();
}

void seq2(int k, int j)
{

	int i=0;
	for(i=k;i<j;i++)
	{
		diode[i].red=195;
		diode[i].green=111;
		diode[i].blue=0;
		delay_ms(100);
	}

	for(i=k;i<j;i++)
	{
		diode[i].red=100;
		delay_ms(100);
	}

	for(i=k;i<j;i++)
	{
		diode[i].red=255;
		diode[i].green=0;
		diode[i].blue=51;
		delay_ms(100);
	}

	for(i=k;i<j;i++)
	{
		diode[i].red=19;
		diode[i].green=0;
		diode[i].blue=207;
		delay_ms(100);
	}

	for(i=k;i<j;i++)
	{
		diode[i].red=0;
		diode[i].green=243;
		diode[i].blue=75;
		delay_ms(100);
	}

}

void seq3(int k, int j)
{
	int i=0;
	for(i=k;i<j;i++)
	{
		diode[i].blue=0;
		delay_ms(100);
	}
	for(i=k;i<j;i++)
	{
		diode[i].blue=20;
		delay_ms(100);
	}
	for(i=k;i<j;i++)
	{
		diode[i].blue=50;
		delay_ms(100);
	}
	for(i=k;i<j;i++)
	{
		diode[i].blue=70;
		delay_ms(100);
	}
	for(i=k;i<j;i++)
	{
		diode[i].blue=100;
		delay_ms(100);
	}
	for(i=k;i<j;i++)
	{
		diode[i].blue=120;
		delay_ms(100);
	}
	for(i=k;i<j;i++)
	{
		diode[i].blue=150;
		delay_ms(100);
	}
	for(i=k;i<j;i++)
	{
		diode[i].blue=170;
		delay_ms(100);
	}
	for(i=k;i<j;i++)
	{
		diode[i].blue=200;
		delay_ms(100);
	}
}

void seq4(int k, int j) //tak sobie
{
	int i=0;
	for(i=k;i<j;i++)
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
	for(i=k;i<j;i++)
	{
		diode[i].green=diode[i].blue=diode[i].red=255;
	}
	for(i=k;i<j;i++)
	{
		delay_ms(250);
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

void seq5(int k, int j) //polaczyc z czyms
{
	int i=0;
	for(i=k;i<j;i++)
	{
		diode[i].green=diode[i].blue=diode[i].red=10;
		delay_ms(50);
	}
	for(i=k;i<j;i++)
	{
		diode[i].green=diode[i].blue=diode[i].red=50;
		delay_ms(50);
	}
	for(i=k;i<j;i++)
	{
		diode[i].green=diode[i].blue=diode[i].red=100;
		delay_ms(50);
	}
	for(i=k;i<j;i++)
	{
		diode[i].green=diode[i].blue=diode[i].red=150;
		delay_ms(50);
	}
	for(i=k;i<j;i++)
	{
		diode[i].green=diode[i].blue=diode[i].red=200;
		delay_ms(50);
	}
	for(i=k;i<j;i++)
	{
		diode[i].green=diode[i].blue=diode[i].red=250;
		delay_ms(50);
	}
	for(i=k;i<j;i++)
	{
		diode[i].green=diode[i].blue=diode[i].red=250;
		delay_ms(50);
	}
	for(i=k;i<j;i++)
	{
		diode[i].green=diode[i].blue=diode[i].red=200;
		delay_ms(50);
	}
	for(i=k;i<j;i++)
	{
		diode[i].green=diode[i].blue=diode[i].red=100;
		delay_ms(50);
	}
	for(i=k;i<j;i++)
	{
		diode[i].green=diode[i].blue=diode[i].red=50;
		delay_ms(50);
	}
	for(i=k;i<j;i++)
	{
		diode[i].green=diode[i].blue=diode[i].red=10;
		delay_ms(50);
	}
	for(i=k;i<j;i++)
	{
		diode[i].green=diode[i].blue=diode[i].red=0;
		delay_ms(50);
	}
	clear();
}

void seq6(int k, int j)
{
	int i=0;
	for(i=k;i<j;i++)
	{
		diode[i].red=255;
	}
		delay_ms(550);
	for(i=k;i<j;i++)
	{
		diode[i].red=150;
	}
		delay_ms(550);
	for(i=k;i<j;i++)
	{
		diode[i].red=50;
	}
		delay_ms(550);
	for(i=k;i<j;i++)
	{
		diode[i].red=10;
	}
		delay_ms(550);
	clear_all();
	//////////////////////////BLUE//////////////////////////
	for(i=k;i<j;i++)
	{
		diode[i].blue=255;
	}
		delay_ms(550);
	for(i=k;i<j;i++)
	{
		diode[i].blue=150;
	}
		delay_ms(550);
	for(i=k;i<j;i++)
	{
		diode[i].blue=50;
	}
		delay_ms(550);
	for(i=k;i<j;i++)
	{
		diode[i].blue=10;
	}
		delay_ms(550);
	clear_all();
	//////////////////////////GREEN//////////////////////////
	for(i=k;i<j;i++)
	{
		diode[i].green=255;
	}
		delay_ms(550);
	for(i=k;i<j;i++)
	{
		diode[i].green=150;
	}
		delay_ms(550);
	for(i=k;i<j;i++)
	{
		diode[i].green=50;
	}
		delay_ms(550);
	for(i=k;i<j;i++)
	{
		diode[i].green=10;
	}
		delay_ms(550);
	clear_all();
}

void seq7()
{
	diode[0].red=255; 	diode[0].green=255; 	diode[0].blue=225;
	diode[1].red=255; 	diode[1].green=0;	  	diode[1].blue=225;
	diode[2].red=255; 	diode[2].green=0;   	diode[2].blue=0;
	diode[3].red=255; 	diode[3].green=69;  	diode[3].blue=0;
	diode[4].red=255; 	diode[4].green=255; 	diode[4].blue=0;
	diode[5].red=0;   	diode[5].green=255; 	diode[5].blue=0;
	diode[6].red=0;   	diode[6].green=0;   	diode[6].blue=225;
	diode[7].red=0;   	diode[7].green=243; 	diode[7].blue=75;
	delay_ms(250);
	////////////////////
	diode[0].red=0;   	diode[0].green=243; 	diode[0].blue=75;
	diode[1].red=255; 	diode[1].green=255; 	diode[1].blue=225;
	diode[2].red=255; 	diode[2].green=0;	  	diode[2].blue=225;
	diode[3].red=255; 	diode[3].green=0;   	diode[3].blue=0;
	diode[4].red=255; 	diode[4].green=69;  	diode[4].blue=0;
	diode[5].red=255; 	diode[5].green=255; 	diode[5].blue=0;
	diode[6].red=0;   	diode[6].green=255; 	diode[6].blue=0;
	diode[7].red=0;   	diode[7].green=0;   	diode[7].blue=225;
	delay_ms(250);
	///////////////
	diode[0].red=0;   	diode[0].green=0;   	diode[0].blue=225;
	diode[1].red=0;   	diode[1].green=243; 	diode[1].blue=75;
	diode[2].red=255; 	diode[2].green=255; 	diode[2].blue=225;
	diode[3].red=255; 	diode[3].green=0;	  	diode[3].blue=225;
	diode[4].red=255; 	diode[4].green=0;   	diode[4].blue=0;
	diode[5].red=255; 	diode[5].green=69;  	diode[5].blue=0;
	diode[6].red=255; 	diode[6].green=255; 	diode[6].blue=0;
	diode[7].red=0;   	diode[7].green=255; 	diode[7].blue=0;
	delay_ms(250);
	///////////////
	diode[0].red=0;   	diode[0].green=255; 	diode[0].blue=0;
	diode[1].red=0;   	diode[1].green=0;   	diode[1].blue=225;
	diode[2].red=0;   	diode[2].green=243; 	diode[2].blue=75;
	diode[3].red=255; 	diode[3].green=255; 	diode[3].blue=225;
	diode[4].red=255; 	diode[4].green=0;	  	diode[4].blue=225;
	diode[5].red=255; 	diode[5].green=0;   	diode[5].blue=0;
	diode[6].red=255; 	diode[6].green=69;  	diode[6].blue=0;
	diode[7].red=255; 	diode[7].green=255; 	diode[7].blue=0;
	delay_ms(250);
	///////////////
	diode[0].red=255; 	diode[0].green=255; 	diode[0].blue=0;
	diode[1].red=0;   	diode[1].green=255; 	diode[1].blue=0;
	diode[2].red=0;   	diode[2].green=0;   	diode[2].blue=225;
	diode[3].red=0;   	diode[3].green=243; 	diode[3].blue=75;
	diode[4].red=255; 	diode[4].green=255; 	diode[4].blue=225;
	diode[5].red=255; 	diode[5].green=0;	  	diode[5].blue=225;
	diode[6].red=255; 	diode[6].green=0;   	diode[6].blue=0;
	diode[7].red=255; 	diode[7].green=69;  	diode[7].blue=0;
	delay_ms(250);
	///////////////
	diode[0].red=255; 	diode[0].green=69;  	diode[0].blue=0;
	diode[1].red=255; 	diode[1].green=255; 	diode[1].blue=0;
	diode[2].red=0;   	diode[2].green=255; 	diode[2].blue=0;
	diode[3].red=0;   	diode[3].green=0;   	diode[3].blue=225;
	diode[4].red=0;   	diode[4].green=243; 	diode[4].blue=75;
	diode[5].red=255; 	diode[5].green=255; 	diode[5].blue=225;
	diode[6].red=255; 	diode[6].green=0;	  	diode[6].blue=225;
	diode[7].red=255; 	diode[7].green=0;   	diode[7].blue=0;
	delay_ms(250);
	///////////////
	diode[0].red=255; 	diode[0].green=0;   	diode[0].blue=0;
	diode[1].red=255; 	diode[1].green=69;  	diode[1].blue=0;
	diode[2].red=255; 	diode[2].green=255; 	diode[2].blue=0;
	diode[3].red=0;   	diode[3].green=255; 	diode[3].blue=0;
	diode[4].red=0;   	diode[4].green=0;   	diode[4].blue=225;
	diode[5].red=0;   	diode[5].green=243; 	diode[5].blue=75;
	diode[6].red=255; 	diode[6].green=255; 	diode[6].blue=225;
	diode[7].red=255; 	diode[7].green=0;	  	diode[7].blue=225;
	delay_ms(250);
	///////////////
	diode[0].red=255; 	diode[0].green=0;	  	diode[0].blue=225;
	diode[1].red=255; 	diode[1].green=0;   	diode[1].blue=0;
	diode[2].red=255; 	diode[2].green=69;  	diode[2].blue=0;
	diode[3].red=255; 	diode[3].green=255; 	diode[3].blue=0;
	diode[4].red=0;   	diode[4].green=255; 	diode[4].blue=0;
	diode[5].red=0;   	diode[5].green=0;   	diode[5].blue=225;
	diode[6].red=0;   	diode[6].green=243; 	diode[6].blue=75;
	diode[7].red=255; 	diode[7].green=255; 	diode[7].blue=225;
	delay_ms(250);
}

void seq8(int k, int j)
{
	diode[8].red=255; 	diode[8].green=255; 	diode[8].blue=225;
	diode[9].red=255; 	diode[9].green=0;	  	diode[9].blue=225;
	diode[10].red=255; 	diode[10].green=0;   	diode[10].blue=0;
	diode[11].red=255; 	diode[11].green=69;  	diode[11].blue=0;
	diode[12].red=255; 	diode[12].green=255; 	diode[12].blue=0;
	diode[13].red=0;   	diode[13].green=255; 	diode[13].blue=0;
	diode[14].red=0;   	diode[14].green=0;   	diode[14].blue=225;
	diode[15].red=0;   	diode[15].green=243;   	diode[15].blue=75;
	delay_ms(250);

	diode[8].red=0;   	diode[8].green=243;   	diode[8].blue=75;
	diode[9].red=255; 	diode[9].green=255; 	diode[9].blue=225;
	diode[10].red=255; 	diode[10].green=0;	  	diode[10].blue=225;
	diode[11].red=255; 	diode[11].green=0;   	diode[11].blue=0;
	diode[12].red=255; 	diode[12].green=69;  	diode[12].blue=0;
	diode[13].red=255; 	diode[13].green=255; 	diode[13].blue=0;
	diode[14].red=0;   	diode[14].green=255; 	diode[14].blue=0;
	diode[15].red=0;   	diode[15].green=0;   	diode[15].blue=225;
	delay_ms(250);

	diode[8].red=0;   	diode[8].green=0;   	diode[8].blue=225;
	diode[9].red=0;   	diode[9].green=243;   	diode[9].blue=75;
	diode[10].red=255; 	diode[10].green=255; 	diode[10].blue=225;
	diode[11].red=255; 	diode[11].green=0;	  	diode[11].blue=225;
	diode[12].red=255; 	diode[12].green=0;   	diode[12].blue=0;
	diode[13].red=255; 	diode[13].green=69;  	diode[13].blue=0;
	diode[14].red=255; 	diode[14].green=255; 	diode[14].blue=0;
	diode[15].red=0;   	diode[15].green=255; 	diode[15].blue=0;
	delay_ms(250);

	diode[8].red=0;   	diode[8].green=255; 	diode[8].blue=0;
	diode[9].red=0;   	diode[9].green=0;   	diode[9].blue=225;
	diode[10].red=0;  	diode[10].green=243;   	diode[10].blue=75;
	diode[11].red=255; 	diode[11].green=255; 	diode[11].blue=225;
	diode[12].red=255; 	diode[12].green=0;	  	diode[12].blue=225;
	diode[13].red=255; 	diode[13].green=0;   	diode[13].blue=0;
	diode[14].red=255; 	diode[14].green=69;  	diode[14].blue=0;
	diode[15].red=255; 	diode[15].green=255; 	diode[15].blue=0;
	delay_ms(250);

	diode[8].red=255; 	diode[8].green=255; 	diode[8].blue=0;
	diode[9].red=0;   	diode[9].green=255; 	diode[9].blue=0;
	diode[10].red=0;   	diode[10].green=0;   	diode[10].blue=225;
	diode[11].red=0;   	diode[11].green=243;   	diode[11].blue=75;
	diode[12].red=255; 	diode[12].green=255; 	diode[12].blue=225;
	diode[13].red=255; 	diode[13].green=0;	  	diode[13].blue=225;
	diode[14].red=255; 	diode[14].green=0;   	diode[14].blue=0;
	diode[15].red=255; 	diode[15].green=69;  	diode[15].blue=0;
	delay_ms(250);

	diode[8].red=255; 	diode[8].green=69;  	diode[8].blue=0;
	diode[9].red=255; 	diode[9].green=255; 	diode[9].blue=0;
	diode[10].red=0;   	diode[10].green=255; 	diode[10].blue=0;
	diode[11].red=0;   	diode[11].green=0;   	diode[11].blue=225;
	diode[12].red=0;   	diode[12].green=243;   	diode[12].blue=75;
	diode[13].red=255; 	diode[13].green=255; 	diode[13].blue=225;
	diode[14].red=255; 	diode[14].green=0;	  	diode[14].blue=225;
	diode[15].red=255; 	diode[15].green=0;   	diode[15].blue=0;
	delay_ms(250);

	diode[8].red=255; 	diode[8].green=0;   	diode[8].blue=0;
	diode[9].red=255; 	diode[9].green=69;  	diode[9].blue=0;
	diode[10].red=255; 	diode[10].green=255; 	diode[10].blue=0;
	diode[11].red=0;   	diode[11].green=255; 	diode[11].blue=0;
	diode[12].red=0;   	diode[12].green=0;   	diode[12].blue=225;
	diode[13].red=0;   	diode[13].green=243;   	diode[13].blue=75;
	diode[14].red=255; 	diode[14].green=255; 	diode[14].blue=225;
	diode[15].red=255; 	diode[15].green=0;	  	diode[15].blue=225;
	delay_ms(250);

	diode[8].red=255; 	diode[8].green=0;	  	diode[8].blue=225;
	diode[9].red=255; 	diode[9].green=0;   	diode[9].blue=0;
	diode[10].red=255; 	diode[10].green=69;  	diode[10].blue=0;
	diode[11].red=255; 	diode[11].green=255; 	diode[11].blue=0;
	diode[12].red=0;   	diode[12].green=255; 	diode[12].blue=0;
	diode[13].red=0;   	diode[13].green=0;   	diode[13].blue=225;
	diode[14].red=0;   	diode[14].green=243;   	diode[14].blue=75;
	diode[15].red=255; 	diode[15].green=255; 	diode[15].blue=225;
	delay_ms(250);
}

void seq9(int k, int j)
{
	int i=0;
	for(i=k;i<16;i++)
	{
		diode[8].red=255; 	diode[8].green=255; 	diode[8].blue=225;
		delay_ms(150);
		diode[9].red=255; 	diode[9].green=0;	  	diode[9].blue=225;
		delay_ms(150);
		diode[10].red=255; 	diode[10].green=0;   	diode[10].blue=0;
		delay_ms(150);
		diode[11].red=255; 	diode[11].green=69;  	diode[11].blue=0;
		delay_ms(150);
		diode[12].red=255; 	diode[12].green=255; 	diode[12].blue=0;
		delay_ms(150);
		diode[13].red=0;   	diode[13].green=255; 	diode[13].blue=0;
		delay_ms(150);
		diode[14].red=0;   	diode[14].green=0;   	diode[14].blue=225;
		delay_ms(150);
		diode[15].red=0;   	diode[15].green=0;   	diode[15].blue=139;
		delay_ms(50);
		clear_s(150);

	//////////////////////////////////////////////////////////
		diode[15].red=0;   	diode[15].green=0;   	diode[15].blue=139;
		delay_ms(150);
		diode[14].red=0;   	diode[14].green=0;   	diode[14].blue=225;
		delay_ms(150);
		diode[13].red=0;   	diode[13].green=255; 	diode[13].blue=0;
		delay_ms(150);
		diode[12].red=255; 	diode[12].green=255; 	diode[12].blue=0;
		delay_ms(150);
		diode[11].red=255; 	diode[11].green=69;  	diode[11].blue=0;
		delay_ms(150);
		diode[10].red=255; 	diode[10].green=0;   	diode[10].blue=0;
		delay_ms(150);
		diode[9].red=255; 	diode[9].green=0;	  	diode[9].blue=225;
		delay_ms(150);
		diode[8].red=255; 	diode[8].green=255; 	diode[8].blue=225;
		delay_ms(150);
		clear_s(150);
	}
}

void seq10(int k, int j)
{
	int i=0;
	for(i=0;i<8;i++)
	{
		diode[0].red=255; 	diode[0].green=255; 	diode[0].blue=225;
		delay_ms(150);
		diode[1].red=255; 	diode[1].green=0;	  	diode[1].blue=225;
		delay_ms(150);
		diode[2].red=255; 	diode[2].green=0;   	diode[2].blue=0;
		delay_ms(150);
		diode[3].red=255; 	diode[3].green=69;  	diode[3].blue=0;
		delay_ms(150);
		diode[4].red=255; 	diode[4].green=255; 	diode[4].blue=0;
		delay_ms(150);
		diode[5].red=0;   	diode[5].green=255; 	diode[5].blue=0;
		delay_ms(150);
		diode[6].red=0;   	diode[6].green=0;   	diode[6].blue=225;
		delay_ms(150);
		diode[7].red=0;   	diode[7].green=0;   	diode[7].blue=139;
		delay_ms(50);
		clear_s(150);

	//////////////////////////////////////////////////////////
		diode[7].red=0;   	diode[7].green=0;   	diode[7].blue=139;
		delay_ms(150);
		diode[6].red=0;   	diode[6].green=0;   	diode[6].blue=225;
		delay_ms(150);
		diode[5].red=0;   	diode[5].green=255; 	diode[5].blue=0;
		delay_ms(150);
		diode[4].red=255; 	diode[4].green=255; 	diode[4].blue=0;
		delay_ms(150);
		diode[3].red=255; 	diode[3].green=69;  	diode[3].blue=0;
		delay_ms(150);
		diode[2].red=255; 	diode[2].green=0;   	diode[2].blue=0;
		delay_ms(150);
		diode[1].red=255; 	diode[1].green=0;	  	diode[1].blue=225;
		delay_ms(150);
		diode[0].red=255; 	diode[0].green=255; 	diode[0].blue=225;
		delay_ms(150);
		clear_s(150);
	}
}

void seq11(int k, int j)
{
	int x=5;
	while(x<255)
	{
			diode[0].blue=x;
			diode[1].blue=x;
			diode[2].blue=x;
			diode[3].blue=x;
			diode[4].blue=x;
			diode[5].blue=x;
			diode[6].blue=x;
			diode[7].blue=x;
			x+=10;
			delay_ms(150);
	}
		while(x>1)
		{
			diode[0].blue=x;
			diode[1].blue=x;
			diode[2].blue=x;
			diode[3].blue=x;
			diode[4].blue=x;
			diode[5].blue=x;
			diode[6].blue=x;
			diode[7].blue=x;
			x-=10;
			delay_ms(150);
		}

//wiecej kolorow
//	x=5;
//	while(x<255)
//	{
//
//
//		diode[0].red=x; diode[0].blue=25;
//		diode[1].red=x;	diode[1].blue=25;
//		diode[2].red=x;	diode[2].blue=25;
//		diode[3].red=x;	diode[3].blue=25;
//		diode[4].red=x;	diode[4].blue=25;
//		diode[5].red=x;	diode[5].blue=25;
//		diode[6].red=x;	diode[6].blue=25;
//		diode[7].red=x;	diode[7].blue=25;
//		x+=10;
//		delay_ms(150);
//	}
//	while(x>0)
//	{
//				diode[0].red=x; diode[0].blue=25;
//				diode[1].red=x;	diode[1].blue=25;
//				diode[2].red=x;	diode[2].blue=25;
//				diode[3].red=x;	diode[3].blue=25;
//				diode[4].red=x;	diode[4].blue=25;
//				diode[5].red=x;	diode[5].blue=25;
//				diode[6].red=x;	diode[6].blue=25;
//				diode[7].red=x;	diode[7].blue=25;
//			x-=10;
//			delay_ms(150);
//	}
//	x=5;
//	while(x<255)
//	{
//		diode[0].red=x; diode[0].green=51;
//		diode[1].red=x;	diode[1].green=51;
//		diode[2].red=x;	diode[2].green=51;
//		diode[3].red=x;	diode[3].green=51;
//		diode[4].red=x;	diode[4].green=51;
//		diode[5].red=x;	diode[5].green=51;
//		diode[6].red=x;	diode[6].green=51;
//		diode[7].red=x;	diode[7].green=51;
//		x+=10;
//		delay_ms(150);
//	}
//	while(x>0)
//	{
//		diode[0].red=x; diode[0].green=51;
//		diode[1].red=x;	diode[1].green=51;
//		diode[2].red=x;	diode[2].green=51;
//		diode[3].red=x;	diode[3].green=51;
//		diode[4].red=x;	diode[4].green=51;
//		diode[5].red=x;	diode[5].green=51;
//		diode[6].red=x;	diode[6].green=51;
//		diode[7].red=x;	diode[7].green=51;
//			x-=10;
//			delay_ms(150);
//	}
}

void seq112(int k, int j)
{
	int x=5;
	while(x<255)
	{

			diode[8].blue=x;
			diode[9].blue=x;
			diode[10].blue=x;
			diode[11].blue=x;
			diode[12].blue=x;
			diode[13].blue=x;
			diode[14].blue=x;
			diode[15].blue=x;
			x+=10;
			delay_ms(150);
	}
		while(x>1)
		{
			diode[8].blue=x;
			diode[9].blue=x;
			diode[10].blue=x;
			diode[11].blue=x;
			diode[12].blue=x;
			diode[13].blue=x;
			diode[14].blue=x;
			diode[15].blue=x;
			x-=10;
			delay_ms(150);
		}
}


