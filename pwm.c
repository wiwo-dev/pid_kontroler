

#include "pwm.h"





	void PWM2(void)
		{
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		TIM_OCInitTypeDef TIM_OCInitStructure;


		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
		//czêstotliwosc PWM ma miec w przyblizeniu 10 000 Hz = 10kHz
		TIM_TimeBaseStructure.TIM_Prescaler=2;
		//przy prescalerze 1 -TIM sterowany 42MHz, przy wiêkszym 84MHz
		//PWM 800Hz - 52499
		//PWM 1000Hz -> TIM_Period = 41999
		//PWM 5000 -> 8399
		//PWM 10000 -> 4199

		//przy prescaler=4
		//PWM 500 -> period=4199

		//przy prescaler=2
		//PWM 1000 -> period 41999

		TIM_TimeBaseStructure.TIM_Period= 41999;


		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
		TIM_TimeBaseStructure.TIM_ClockDivision=0;
		TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
		//PWM canal 1
		TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse=0;
		TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
		TIM_OC1Init(TIM3,&TIM_OCInitStructure);
		TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
		//PWM canal 2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse=0;
		TIM_OC2Init(TIM3, &TIM_OCInitStructure);
		TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
		TIM_ARRPreloadConfig(TIM3,ENABLE);
		TIM_Cmd(TIM3,ENABLE);
		}

	void GPIO(void)
	{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	/* GPIOC Configuration: TIM3 CH1 (PC6), TIM3 CH2 (PC7) */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	//Configuration
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3);
	}




