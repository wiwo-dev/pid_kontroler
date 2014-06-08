#ifndef __przyciskh
#define __przyciskh

#include "misc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_adc.h"
#include "pid.h"

void IniPrzycisk(void);
void IniTimerPrzycisk();//wykorzystywany do przycisku
void EXTI0_IRQHandler ( void );
void TIM5_IRQHandler(void);

#endif
