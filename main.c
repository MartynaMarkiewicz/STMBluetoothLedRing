#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "misc.h"

int main(void)
{
	SystemInit();

	/* GPIOD Periph clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef  GPIO_InitStructure;
	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	//przyciski
		GPIO_InitTypeDef GPIO_przyciski;
		GPIO_przyciski.GPIO_Pin = GPIO_Pin_0;
		GPIO_przyciski.GPIO_Mode = GPIO_Mode_IN;
		//GPIO_Diody.GPIO_OType = GPIO_OType_PP;
		GPIO_przyciski.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_przyciski.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOA, &GPIO_przyciski);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 8400;
	TIM_TimeBaseStructure.TIM_Prescaler = 10000;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM3, ENABLE);
	int counter=TIM3->CNT;
	int i=0;
	for(;;)
	{
		if(TIM_GetFlagStatus(TIM3, TIM_FLAG_Update))
		{
					switch(i)
			         		{
			         		case 0:
			         			GPIO_SetBits(GPIOD,GPIO_Pin_13);
			         			GPIO_ResetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_15|GPIO_Pin_14);
			         			i++;
			         			break;
			         		case 1:
			         			GPIO_SetBits(GPIOD,GPIO_Pin_12);
			         			GPIO_ResetBits(GPIOD,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
			         			i++;
			         			break;
			         		case 2:
			         			GPIO_SetBits(GPIOD,GPIO_Pin_14);
			         			GPIO_ResetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_15|GPIO_Pin_13);
			         			i++;
			         			break;
			         		case 3:
			         			GPIO_SetBits(GPIOD,GPIO_Pin_15);
			         			GPIO_ResetBits(GPIOD,GPIO_Pin_13|GPIO_Pin_12|GPIO_Pin_14);
			         			i++;
			         			break;
			         		case 4:
			         			GPIO_SetBits(GPIOD,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_12);
			         			i=0;
			         			break;
			         		}
			TIM_ClearFlag(TIM3, TIM_FLAG_Update);
		}

	}
}
