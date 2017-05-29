#include "stm32f4xx_conf.h"
#include <stm32f4xx.h>
#include <clear.h>
#include <colours.h>
#include <ctype.h>
#include "delay.h"
#include "math.h"
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
#include <time.h>
#include "ws2812.h"



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

int temp;

int red_br,red_br2;
int green_br,green_br2;
int blue_br,blue_br2;

int red_p,red_p2;
int green_p,green_p2;
int blue_p,blue_p2;

volatile int zmienna_usart1,zmienna_usart12;
volatile int zmienna_usart2,zmienna_usart22;
volatile int zmienna_usart3,zmienna_usart32;
volatile int zmienna_usart4,zmienna_usart42;
volatile int zmienna_usart5,zmienna_usart52;
volatile int zmienna_usart6,zmienna_usart62;
volatile int turn_led,turn_led2;

void rcc();
void gpio();
void usart();
void setBrightness(uint8_t x);
uint8_t getBrightness(void);

void reset()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void rcc()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
}

void gpio()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	// konfiguracja linii Tx
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_13|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	// konfiguracja linii Rx
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void usart()
{
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;

	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
	USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	// konfiguracja
	USART_Init(USART3, &USART_InitStructure);

	// wlaczenie ukladu USART
	USART_Cmd(USART3, ENABLE );

	NVIC_InitTypeDef NVIC_InitStructure;
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE );
	NVIC_InitStructure. NVIC_IRQChannel = USART3_IRQn ;
	NVIC_InitStructure. NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure. NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure. NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_EnableIRQ( USART3_IRQn );
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
	//FUNKCJE WSZYSTKIE OD KOLORÓW itp. RING1

	//ODBIERANIE JASNOŒCI
			uint8_t c = USART3->DR;
			//>>>>>>>>>>>>>>>>>>>>>>>
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
			rgb(red_p, green_p,blue_p);


			// KOLORY - RING_1
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
				red_p=0;
				green_p=0;
				blue_p=0;
				zmienna_usart1=1;
			}
			if(USART3->DR == 'b')
			{
				red_p=0;
				green_p=0;
				blue_p=0;
				zmienna_usart2=1;
			}
			if(USART3->DR == 'c')
			{
				red_p=0;
				green_p=0;
				blue_p=0;
				zmienna_usart3=1;
			}
			if(USART3->DR == 'd')
			{
				red_p=0;
				green_p=0;
				blue_p=0;
				zmienna_usart4=1;
			}
			if(USART3->DR == 'e')
			{
				red_p=0;
				green_p=0;
				blue_p=0;
				zmienna_usart5=1;
			}
			if(USART3->DR == 'f')
			{
				red_p=0;
				green_p=0;
				blue_p=0;
				zmienna_usart6=1;
			}

			if(brightness)
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
				turn_led=1;
				clear_app(0,8);
				red_br=0;
				green_br=0;
				blue_br=0;
				red_p=0;
				green_p=0;
				blue_p=0;
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

	//FUNKCJE WSZYSTKIE OD KOLORÓW itp. / RING2
	//ODBIERANIE JASNOŒCI
			uint8_t c1 = USART3->DR;
			//>>>>>>>>>>>>>>>>>>>>>>>
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
				if (c1 >= 1 && c1 <= 255&&c1!=76&&c1!=71&&c1!=66&&c1!=120&&c1!=121&&c1!=97&&c1!=98&&c1!=99&&c1!=100&&c1!=101&&c1!=102&&c1!=103&&c1!=104&&c1!=105&&c1!=106&&c1!=107&&c1!=108&&c1!=109)
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
				if (c1 >= 1 && c1 <= 255&&c1!=76&&c1!=82&&c1!=66&&c1!=120&&c1!=121&&c1!=97&&c1!=98&&c1!=99&&c1!=100&&c1!=101&&c1!=102&&c1!=103&&c1!=104&&c1!=105&&c1!=106&&c1!=107&&c1!=108&&c1!=109)
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
				if (c1 >= 1 && c1 <= 255 && c1!=76 && c1!=82 && c1!=71&&c1!=120&&c1!=121&&c1!=97&&c1!=98&&c1!=99&&c1!=100&&c1!=101&&c1!=102&&c1!=103&&c1!=104&&c1!=105&&c1!=106&&c1!=107&&c1!=108&&c1!=109)
				{
					blue_p2 = c1*4-1;
					blue_br2=blue_p2;
				}
				else
				m1=0;
			}
			// RGB - RING_2
			rgb2(red_p2, green_p2,blue_p2);


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
				red_p2=0;
				green_p2=0;
				blue_p2=0;
				zmienna_usart12=1;
			}
			if(USART3->DR == 'b')
			{
				red_p2=0;
				green_p2=0;
				blue_p2=0;
				zmienna_usart22=1;
			}
			if(USART3->DR == 'c')
			{
				red_p2=0;
				green_p2=0;
				blue_p2=0;
				zmienna_usart32=1;
			}
			if(USART3->DR == 'd')
			{
				red_p2=0;
				green_p2=0;
				blue_p2=0;
				zmienna_usart42=1;
			}
			if(USART3->DR == 'e')
			{
				red_p2=0;
				green_p2=0;
				blue_p2=0;
				zmienna_usart52=1;
			}
			if(USART3->DR == 'f')
			{
				red_p2=0;
				green_p2=0;
				blue_p2=0;
				zmienna_usart62=1;
			}
			if(brightness2)
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
				turn_led2=1;
				red_br2=0;
				green_br2=0;
				blue_br2=0;
				red_p2=0;
				green_p2=0;
				blue_p2=0;
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
	init_systick();	//delay
	ws2812_init();	//LED

	while(1)
	{
		if(zmienna_usart1==1)
		{
			seq11(0,8);
			if(turn_led==1)
			{
				zmienna_usart1=0;
				clear_app(0,8);
				turn_led=0;
			}
		}


		if(zmienna_usart2==1)
		{
			seq2(0,8);
			if(turn_led==1)
			{
				clear_app(0,8);
				turn_led=0;
				zmienna_usart2=0;
			}
		}
		if(zmienna_usart3==1)
		{
			seq3(0,8);
			if(turn_led==1)
			{
				clear_app(0,8);
				turn_led=0;
				zmienna_usart3=0;
			}
		}
		if(zmienna_usart4==1)
		{
			seq10(0,8);
			if(turn_led==1)
			{
				clear_app(0,8);
				turn_led=0;
				zmienna_usart4=0;
			}
		}
		if(zmienna_usart5==1)
		{
			seq7(0,8);
			if(turn_led==1)
			{
				clear_app(0,8);
				turn_led=0;
				zmienna_usart5=0;
			}
		}
		if(zmienna_usart6==1)
		{
			seq6(0,8);
			if(turn_led==1)
			{
				clear_app(0,8);
				turn_led=0;
				zmienna_usart6=0;
			}
		}

		//////////////////RING2///////////////////////////
		if(zmienna_usart12==1)
		{
			seq112(8,16);
			if(turn_led2==1)
			{
				clear_app(8,16);
				turn_led2=0;
				zmienna_usart12=0;
			}
		}
		if(zmienna_usart22==1)
		{
			seq2(8,16);
			if(turn_led2==1)
			{
				clear_app(8,16);
				turn_led2=0;
				zmienna_usart22=0;
			}
		}
		if(zmienna_usart32==1)
		{
			seq3(8,16);
			if(turn_led2==1)
			{
				clear_app(8,16);
				turn_led2=0;
				zmienna_usart32=0;
			}
		}
		if(zmienna_usart42==1)
		{
			seq9(8,16);
			if(turn_led2==1)
			{
				clear_app(8,16);
				turn_led2=0;
				zmienna_usart42=0;
			}
		}
		if(zmienna_usart52==1)
		{
			seq8(8,16);
			if(turn_led2==1)
			{
				clear_app(8,16);
				turn_led2=0;
				zmienna_usart52=0;
			}
		}
		if(zmienna_usart62==1)
		{
			seq6(8,16);
			if(turn_led2==1)
			{
				clear_app(8,16);
				turn_led2=0;
				zmienna_usart62=0;
			}
		}
	}
}
