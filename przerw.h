#ifndef __przerwh
#define __przerwh
#include "misc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_adc.h"
#include "pid.h"

extern float obrotowNaSekunde;
extern float obrotowNaMinute;
extern int kierunek2;

float OdczytajPredkosc();

void Nowa(void);
void IniDiody(unsigned long pin);
void IniTimerPrzerwanie1();
void TIM2_IRQHandler(void);


void EXTILine0_Config();
void EXTI0_IRQHandler();
void EXTI1_IRQHandler();



#endif

