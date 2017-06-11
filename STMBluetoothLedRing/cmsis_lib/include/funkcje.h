#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_dac.h"
#include "misc.h"

#ifndef funkcje_h
#define funkcje_h

typedef enum Timer {Tim2, Tim3, Tim4, Tim5} Timer;

void UstawTimer(Timer timer, unsigned int period, unsigned int prescaler, FunctionalState Stan);
void UstawPrzerwanie(unsigned char numer, unsigned char priorytet);
void UstawPrzerwanieTimera(TIM_TypeDef* TIMx, uint16_t TIM_IT);
void rcc();
void gpio();
void usart();
void reset();

#endif
