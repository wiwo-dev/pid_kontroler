
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __adcinih
#define __adcinih

#include "misc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include <stm32f4xx_syscfg.h>
#include <stm32f4xx_adc.h>


void RCC_Konfiguracja_Adc12(void);

void ADC1_Configuration(void);

void ADC2_Configuration(void);
void GPIO_Configuration_Adc1(void);
void GPIO_Configuration_Adc2(void);


#endif

