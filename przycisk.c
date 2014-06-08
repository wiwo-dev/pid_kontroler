#include "przycisk.h"


//inicjacja przycisku PA0 - podpietego na plytce i przerwania ktore wywola
void IniPrzycisk(void)
{
//przycisk - PA0

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef y;
	EXTI_InitTypeDef ex;

	y.GPIO_Pin = GPIO_Pin_0;
	y.GPIO_Mode = GPIO_Mode_IN;
	y.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &y);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef NVIC_InitStructure;
	// numer kanalu na ktorym bedzie przerwanie - 0
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	// priorytet gl
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	// subpriorytet
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	// uruchom dany kanal
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//konf lini przerwania - 0
	ex.EXTI_Line=EXTI_Line0;
	ex.EXTI_Mode=EXTI_Mode_Interrupt;
	ex.EXTI_Trigger=EXTI_Trigger_Rising;
	ex.EXTI_LineCmd=ENABLE;
	EXTI_Init(&ex);

	///polaczenie EXTI Line0 do PA0
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0) ;
}


//wykorzystywany do przycisku - TIM5
void IniTimerPrzycisk()
{
	//ustawienie trybu pracy priorytetow przerwan
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef p;
	//numer przerwania
	p.NVIC_IRQChannel = TIM5_IRQn;
	// priorytet gl
	p.NVIC_IRQChannelPreemptionPriority = 0x00;
	// subpriorytet
	p.NVIC_IRQChannelSubPriority = 0x00;
	// uruchom dany kanal
	p.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&p);

	//doprowadzenie sygnalu zerowego
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	TIM_TimeBaseInitTypeDef a;
	a.TIM_Prescaler=8400;
	a.TIM_CounterMode=TIM_CounterMode_Up;
	a.TIM_Period=200;
	a.TIM_ClockDivision=0;
	a.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM5, &a);

	// wyczyszczenie przerwania od timera
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	// zezwolenie na przerwania od przepelnienia dla timera
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
}

//przerwanie wywoluje sie po wcisnieciu przycisku i zalacza timer 5
void EXTI0_IRQHandler ( void )
{
	if ( EXTI_GetITStatus ( EXTI_Line0 ) != RESET ) // sprawdzenie źródł a przerwania
	{
		TIM_Cmd(TIM5, ENABLE);
	}
	EXTI_ClearITPendingBit ( EXTI_Line0 ); //pamiętamy o zerowaniu bitu przerwania
}

void TIM5_IRQHandler(void)//timer wlacza sie przez przerwanie od przycisku
{
	if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
	{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
		{
			GPIO_ToggleBits(GPIOD, GPIO_Pin_15);	//mozna wywalic
			zmienKierunek();
		}
		TIM_Cmd(TIM5, DISABLE);
		// wyzerowanie flagi wyzwolonego przerwania
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	}
}
