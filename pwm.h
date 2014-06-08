
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __pwmh
#define __pwmh

#ifdef __cplusplus
 extern "C" {
#endif


  #include "stm32f4xx.h"
  #include "stm32f4xx_tim.h"
  #include "stm32f4xx_adc.h"
  #include "stm32f4xx_gpio.h"
  #include "stm32f4xx_rcc.h"


/*
  #include "misc.h"
  #include "stm32f4xx.h"
  #include "stm32f4xx_gpio.h"
  #include "stm32f4xx_rcc.h"
  #include "stm32f4xx_tim.h"
  #include <stm32f4xx_syscfg.h>
  #include <stm32f4xx_adc.h>
 */


void PWM2(void);
void GPIO(void);
void PWM(void);
void Delay(__IO uint32_t nCount);


#ifdef __cplusplus
}
#endif

#endif


