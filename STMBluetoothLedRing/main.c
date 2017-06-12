#include "stm32f4xx_conf.h"
#include <stm32f4xx.h>
#include <colours.h>
#include <ctype.h>
#include <misc.h>
#include <sekwencje.h>
#include <stdbool.h>
#include <stdio.h>
#include "stm32f4xx_adc.h"
#include <stm32f4xx_dma.h>
#include "stm32f4xx_exti.h"
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include "stm32f4xx_syscfg.h"
#include <stm32f4xx_tim.h>
#include <stm32f4xx_usart.h>
#include <string.h>
#include "ws2812.h"
#include "cmsis_lib/include/funkcje.h"

#define false 0
#define true 1

bool s,k,m;
bool s1,k1,m1;

uint8_t brightness,brightness2;
uint8_t *pixels;

int x;
bool x1;

int y;
bool y2;

int temp=0;

int red_br,red_br2;
int green_br,green_br2;
int blue_br,blue_br2;

int red_p,red_p2;
int green_p,green_p2;
int blue_p,blue_p2;

int zmienna_usart1,zmienna_usart12;
int zmienna_usart2,zmienna_usart22;
int zmienna_usart3,zmienna_usart32;
int zmienna_usart4,zmienna_usart42;
int zmienna_usart5,zmienna_usart52;
int zmienna_usart6,zmienna_usart62;

void setBrightness(uint8_t x);
uint8_t getBrightness(void);

void TIM2_IRQHandler()
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET){
		pokazZmiane();

		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

void setBrightness(uint8_t x)
{
  uint8_t newBrightness = x + 1;
  uint8_t newBrightness2 = x + 1;

  // RING_1
  	  if(newBrightness != brightness)
  	  {
  		  uint8_t  c,
            *ptr           = pixels,
             oldBrightness = brightness - 1;
  		  uint16_t scale;
  		  if(oldBrightness == 0) scale = 0;
  		  else if(x == 255) scale = 65535 / oldBrightness;
  		  else scale = (((uint16_t)newBrightness << 8) - 1) / oldBrightness;
  		  for(uint16_t i=0; i<3; i++)
  		  {
  			  c      = *ptr;
  			  *ptr++ = (c * scale) >> 8;
  		  }
  		  brightness = newBrightness;
  	  }
}

void setBrightness2(uint8_t x)
{
  uint8_t newBrightness2 = x + 1;

  // RING_2
  	  if(newBrightness2 != brightness2)
  	  {
  		  uint8_t  c1,
            *ptr           = pixels,
             oldBrightness2 = brightness2 - 1;
  		  uint16_t scale;
  		  if(oldBrightness2 == 0) scale = 0;
  		  else if(x == 255) scale = 65535 / oldBrightness2;
  		  else scale = (((uint16_t)newBrightness2 << 8) - 1) / oldBrightness2;
  		  for(uint16_t i=0; i<3; i++)
  		  {
  			  c1      = *ptr;
  			  *ptr++ = (c1 * scale) >> 8;
  		  }
  		  brightness2 = newBrightness2;
  	  }
}

uint8_t getBrightness(void)
{
  return brightness - 1;
}

void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		if(USART3->DR=='x'||temp==0)
		{
			//RING1
			temp=0;
			if(USART3->DR=='y')
			{
				temp=1;
			}

	//ODBIERANIE JASNOŒCI
			uint8_t c = USART3->DR;
			if(USART3->DR=='L')
			{
				x=0;
				x1=1;
			}
			if(x1==1)
			{
				if(c==0)
				x=0;
				if (c >= 1 && c <= 100&&c!=82&&c!=71&&c!=66&&c!=97&&c!=98&&c!=99&&c!=100)
				x = c*10;
				else
				x1=0;
				setBrightness(x);
			}

			if(USART3->DR == 'R')
			{
				brightness=100;
				red_p = 0;
				s = 1;
			}
			if (s==1)
			{
				if(c==0)
				red_p=0;
				if (c >= 1 && c <= 255&&c!=76&&c!=71&&c!=66&&c!=120&&c!=121&&c!=97&&c!=98&&c!=99&&c!=100&&c!=101&&c!=102&&c!=103&&c!=104&&c!=105&&c!=106&&c!=107&&c!=108&&c!=109)
				{
					red_p = c*4-1;
					red_br=red_p;
				}
				else
				s=0;
			}

			if(USART3->DR == 'G')
			{
				brightness=101;
				green_p = 0;
				k = 1;
			}
			if (k==1)
			{
				if(c<1)
				green_p=0;
				if (c >= 1 && c <= 255&&c!=76&&c!=82&&c!=66&&c!=120&&c!=121&&c!=97&&c!=98&&c!=99&&c!=100&&c!=101&&c!=102&&c!=103&&c!=104&&c!=105&&c!=106&&c!=107&&c!=108&&c!=109)
				{
					green_p = c*4-1;
					green_br=green_p;
				}
				else
				k=0;
			}

			if(USART3->DR == 'B')
			{
				brightness=100;
				blue_p = 0;
				m = 1;
			}
			if (m==1)
			{
				if(c<1)
				blue_p=0;
				if (c >= 1 && c <= 255&&c!=76&&c!=82&&c!=71&&c!=120&&c!=121&&c!=97&&c!=98&&c!=99&&c!=100&&c!=101&&c!=102&&c!=103&&c!=104&&c!=105&&c!=106&&c!=107&&c!=108&&c!=109)
				{
					blue_p = c*4-1;
					blue_br=blue_p;
				}
				else
				m=0;
			}
			// RGB - RING_1
			if(zmienna_usart1==0&&zmienna_usart2==0&&zmienna_usart3==0&&zmienna_usart4==0&&zmienna_usart5==0&&zmienna_usart6==0)
			{
				rgb(red_p, green_p,blue_p);
			}


		//	 KOLORY - RING_1
			if(USART3->DR == 'g')
			{
				red_br=135;
				green_br=31;
				blue_br=0;
				brightness=100;
				rgb(red_br, green_br,blue_br);
			}
			if(USART3->DR == 'h')
			{
				red_br=195;
				green_br=111;
				blue_br=0;
				brightness=100;
				rgb(red_br, green_br,blue_br);
			}
			if(USART3->DR == 'i')
			{
				red_br=24;
				green_br=100;
				blue_br=0;
				brightness=100;
				rgb(red_br, green_br,blue_br);
			}
			if(USART3->DR == 'j')
			{
				red_br=0;
				green_br=243;
				blue_br=75;
				brightness=100;
				rgb(red_br, green_br,blue_br);
			}
			if(USART3->DR == 'k')
			{
				red_br=255;
				green_br=0;
				blue_br=51;
				brightness=100;
				rgb(red_br, green_br,blue_br);
			}
			if(USART3->DR == 'l')
			{
				red_br=255;
				green_br=0;
				blue_br=255;
				brightness=100;
				rgb(red_br, green_br,blue_br);
			}
			if(USART3->DR == 'm')
			{
				red_br=19;
				green_br=0;
				blue_br=207;
				brightness=100;
				rgb(red_br, green_br,blue_br);
			}

			// SEKWENCJE - RING_1
			if(USART3->DR == 'a')
			{
				zmienna_usart1=1;
			}
			if(USART3->DR == 'b')
			{
				zmienna_usart2=1;
			}
			if(USART3->DR == 'c')
			{
				zmienna_usart3=1;
			}
			if(USART3->DR == 'd')
			{
				zmienna_usart4=1;
			}
			if(USART3->DR == 'e')
			{
				zmienna_usart5=1;
			}
			if(USART3->DR == 'f')
			{
				zmienna_usart6=1;
			}

			if(brightness&&zmienna_usart1==0&&zmienna_usart2==0&&zmienna_usart3==0&&zmienna_usart4==0&&zmienna_usart5==0&&zmienna_usart6==0)
			{
				if(red_br==327)
				{
					red_br=0;
				}
				if(green_br==283)
				{
					green_br=0;
				}
				if(blue_br==263)
				{
					blue_br=0;
				}
				int i=0;
				for(i=0;i<8;i++)
				{
					diode[i].red=(red_br* brightness) >> 8;
					diode[i].green=(green_br* brightness) >> 8;
					diode[i].blue=(blue_br* brightness) >> 8;
				}
			}

			// TURN OFF
			if(USART3->DR == 'O')
			{
				Ringi[0].sekw =0;
				Ringi[0].czas=0;
				Ringi[0].index = 0;

				red_br=0;
				green_br=0;
				blue_br=0;
				red_p=0;
				green_p=0;
				blue_p=0;

				zmienna_usart1=0;
				zmienna_usart2=0;
				zmienna_usart3=0;
				zmienna_usart4=0;
				zmienna_usart5=0;
				zmienna_usart6=0;
			}
		}

	////////////////////RING2/////////////////////////
		if(USART3->DR=='y'||temp==1)
		{
			//RING2
			temp=1;

			if(USART3->DR=='x')
			{
				temp=0;
			}

	//ODBIERANIE JASNOŒCI
			uint8_t c1 = USART3->DR;

			if(USART3->DR=='L')
			{
				y=0;
				y2=1;
			}
			if(y2==1)
			{
				if(c1==0)
				y=0;
				if (c1 >= 1 && c1 <= 100 && c1!=82 && c1!=71 && c1!=66 && c1!=97 && c1!=98 && c1!=99 && c1!=100)
				y = c1*10;
				else
				y2=0;
				setBrightness2(y);
			}

			if(USART3->DR == 'R')
			{
				brightness2=100;
				red_p2 = 0;
				s1 = 1;
			}
			if (s1==1)
			{
				if(c1==0)
				red_p2=0;
				if (c1 >= 1 && c1 <= 255&&c1!=76&&c1!=71&&c1!=66&&c1!=120&&c1!=121&&c1!=97&&c1!=98&&c1!=99&&c1!=100&&c1!=101&&c1!=102&&c1!=103&&c1!=104&&c1!=105&&c1!=106&&c1!=107&&c1!=108&&c1!=109&&c1!=283)
				{
					red_p2 = c1*4-1;
					red_br2=red_p2;
				}
				else
				s1=0;
			}

			if(USART3->DR == 'G')
			{
				brightness2=100;
				green_p2 = 0;
				k1 = 1;
			}
			if (k1==1)
			{
				if(c1<1)
				green_p2=0;
				if (c1 >= 1 && c1 <= 255&&c1!=76&&c1!=82&&c1!=66&&c1!=120&&c1!=121&&c1!=97&&c1!=98&&c1!=99&&c1!=100&&c1!=101&&c1!=102&&c1!=103&&c1!=104&&c1!=105&&c1!=106&&c1!=107&&c1!=108&&c1!=109&&c1!=283)
				{
					green_p2 = c1*4-1;
					green_br2=green_p2;
				}
				else
				k1=0;
			}

			if(USART3->DR == 'B')
			{
				brightness2=100;
				blue_p2 = 0;
				m1 = 1;
			}
			if (m1==1)
			{
				if(c1<1)
				blue_p2=0;
				if (c1 >= 1 && c1 <= 255 && c1!=76 && c1!=82 && c1!=71&&c1!=120&&c1!=121&&c1!=97&&c1!=98&&c1!=99&&c1!=100&&c1!=101&&c1!=102&&c1!=103&&c1!=104&&c1!=105&&c1!=106&&c1!=107&&c1!=108&&c1!=109&&c1!=283)
				{
					blue_p2 = c1*4-1;
					blue_br2=blue_p2;
				}
				else
				m1=0;
			}
			// RGB - RING_2

			if(zmienna_usart12==0&&zmienna_usart22==0&&zmienna_usart32==0&&zmienna_usart42==0&&zmienna_usart52==0&&zmienna_usart62==0)
			{
				rgb2(red_p2, green_p2,blue_p2);
			}

			// KOLORY - RING_2
			if(USART3->DR == 'g')
			{
				red_br2=135;
				green_br2=31;
				blue_br2=0;
				brightness2=100;
				rgb2(red_br2, green_br2,blue_br2);
			}
			if(USART3->DR == 'h')
			{
				red_br2=195;
				green_br2=111;
				blue_br2=0;
				brightness2=100;
				rgb2(red_br2, green_br2,blue_br2);
			}
			if(USART3->DR == 'i')
			{
				red_br2=24;
				green_br2=100;
				blue_br2=0;
				brightness2=100;
				rgb2(red_br2, green_br2,blue_br2);
			}
			if(USART3->DR == 'j')
			{
				red_br2=0;
				green_br2=243;
				blue_br2=75;
				brightness2=100;
				rgb2(red_br2, green_br2,blue_br2);
			}
			if(USART3->DR == 'k')
			{
				red_br2=255;
				green_br2=0;
				blue_br2=51;
				brightness2=100;
				rgb2(red_br2, green_br2,blue_br2);
			}
			if(USART3->DR == 'l')
			{
				red_br2=255;
				green_br2=0;
				blue_br2=255;
				brightness2=100;
				rgb2(red_br2, green_br2,blue_br2);
			}
			if(USART3->DR == 'm')
			{
				red_br2=19;
				green_br2=0;
				blue_br2=207;
				brightness2=100;
				rgb2(red_br2, green_br2,blue_br2);
			}

			// SEKWENCJE - RING_2
			if(USART3->DR == 'a')
			{
				zmienna_usart12=1;
			}
			if(USART3->DR == 'b')
			{
				zmienna_usart22=1;
			}
			if(USART3->DR == 'c')
			{
				zmienna_usart32=1;
			}
			if(USART3->DR == 'd')
			{
				zmienna_usart42=1;
			}
			if(USART3->DR == 'e')
			{
				zmienna_usart52=1;
			}
			if(USART3->DR == 'f')
			{
				zmienna_usart62=1;
			}

			if(brightness2&&zmienna_usart12==0&&zmienna_usart22==0&&zmienna_usart32==0&&zmienna_usart42==0&&zmienna_usart52==0&&zmienna_usart62==0)
			{
				if(red_br2==327)
				{
					red_br2=0;
				}
				if(green_br2==283)
				{
					green_br2=0;
				}
				if(blue_br2==263)
				{
					blue_br2=0;
				}
				int i=8;
				for(i=8;i<16;i++)
				{
					diode[i].red=(red_br2* brightness2) >> 8;
					diode[i].green=(green_br2* brightness2) >> 8;
					diode[i].blue=(blue_br2* brightness2) >> 8;
				}
			}

			// TURN OFF
			if(USART3->DR == 'O')
			{
				Ringi[1].sekw =0;
				Ringi[1].czas=0;
				Ringi[1].index = 0;

				red_br2=0;
				green_br2=0;
				blue_br2=0;
				red_p2=0;
				green_p2=0;
				blue_p2=0;

				zmienna_usart12=0;
				zmienna_usart22=0;
				zmienna_usart32=0;
				zmienna_usart42=0;
				zmienna_usart52=0;
				zmienna_usart62=0;
			}
		}
	}
}

int main(void)
{
	SystemInit();
	rcc();
	gpio();
	usart();
	ws2812_init();	//LED

	UstawTimer(Tim2,8399, 49, ENABLE);
	UstawPrzerwanie(TIM2_IRQn, 0);
	UstawPrzerwanieTimera(TIM2, TIM_IT_Update);
	ustawSekwencje();

	while(1)
	{
		if(zmienna_usart1==1)
		{
			Ringi[0].sekw = &Sekwencje.sekw[0];
		}

		if(zmienna_usart2==1)
		{
			Ringi[0].sekw = &Sekwencje.sekw[1];
		}
		if(zmienna_usart3==1)
		{
			Ringi[0].sekw = &Sekwencje.sekw[2];
		}
		if(zmienna_usart4==1)
		{
			Ringi[0].sekw = &Sekwencje.sekw[3];
		}
		if(zmienna_usart5==1)
		{
			Ringi[0].sekw = &Sekwencje.sekw[5];
		}
		if(zmienna_usart6==1)
		{
			Ringi[0].sekw = &Sekwencje.sekw[4];
		}

		//////////////////RING2///////////////////////////
		if(zmienna_usart12==1)
		{
			Ringi[1].sekw = &Sekwencje.sekw[0];
		}
		if(zmienna_usart22==1)
		{
			Ringi[1].sekw = &Sekwencje.sekw[1];
		}
		if(zmienna_usart32==1)
		{
			Ringi[1].sekw = &Sekwencje.sekw[2];
		}
		if(zmienna_usart42==1)
		{
			Ringi[1].sekw = &Sekwencje.sekw[3];
		}
		if(zmienna_usart52==1)
		{
			Ringi[1].sekw = &Sekwencje.sekw[5];
		}
		if(zmienna_usart62==1)
		{
			Ringi[1].sekw = &Sekwencje.sekw[4];
		}
	}
}
