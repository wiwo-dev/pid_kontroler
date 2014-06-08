#include "przerw.h"

int enkoderA=0;
int enkoderB=0;

int sygObrot=624;

float obrotowNaSekunde;
float obrotowNaMinute;



float OdczytajPredkosc()
{
	return obrotowNaMinute;
}


//konfiguracja przerwa� z enkoder�w
void EXTILine0_Config()
{
  GPIO_InitTypeDef   GPIO_InitStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;
  EXTI_InitTypeDef   EXTI_InitStructure;

  /* Enable GPIOA clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* Configure PA0 pin as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Connect EXTI Line0 to PA0 and PA1 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource2);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource3);

  /* Configure EXTI Line0 and Line1 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line2 | EXTI_Line3;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
  NVIC_Init(&NVIC_InitStructure);
}

//przerwanie z pierwszego enkodera
void EXTI2_IRQHandler()
{
  if(EXTI_GetITStatus(EXTI_Line2) != RESET)
  {
    /* Toggle LED1 */
    GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
    enkoderA++;


    /* Clear the EXTI line 0 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line2);
  }
}

//przerwanie z drugiego enkodera
void EXTI3_IRQHandler()
{
  if(EXTI_GetITStatus(EXTI_Line3) != RESET)
  {
    /* Toggle LED1 */
    GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
    enkoderB++;


    /* Clear the EXTI line 1 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line3);
  }
}


//funkcja do konfiguracji diody wykorzystanej do migania za pomoca przerwania z timera
void IniDiody(unsigned long pin)
{
	//wlaczenie sygnalu zerowego, tutaj zakomentowane bo odpalone w main()
	//SystemInit()
	//dorowadzenie sygnału zerowego do portu
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef x;
	x.GPIO_Pin = pin;
	x.GPIO_Mode = GPIO_Mode_OUT;//tu cos zmienial
	x.GPIO_Speed = GPIO_Speed_100MHz;
	x.GPIO_PuPd = GPIO_PuPd_DOWN;//tu tez cos zmienial
	GPIO_Init(GPIOD, &x);
	//mapowanie. nie jest potrzebne do samego odpalenia diody
}



//konfiguracja przerwania i timera dla ZLICZANIA PREDKOSCI
void IniTimerPrzerwanie1()
{
	//ustawienie trybu pracy priorytetow przerwan
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef p;
	//numer przerwania
	p.NVIC_IRQChannel = TIM2_IRQn;
	// priorytet główny
	p.NVIC_IRQChannelPreemptionPriority = 0x00;
	// subpriorytet
	p.NVIC_IRQChannelSubPriority = 0x00;
	// uruchom dany kanał
	p.NVIC_IRQChannelCmd = ENABLE;
	// zapisz wypełnioną strukturę do rejestrów
	NVIC_Init(&p);

	//doprowadzenie sygnalu zerowego
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	//TIM2 przy prescaler=1 ma 42Mhz a przy wiekszym 84Mhz)
	TIM_TimeBaseInitTypeDef a;
	a.TIM_Prescaler=8400;
	int obliczona = 2000 - 1;
	a.TIM_CounterMode=TIM_CounterMode_Up;
	a.TIM_Period=obliczona;
	a.TIM_ClockDivision=0;
	a.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2, &a);

	// wyczyszczenie przerwania od timera 2 (przy konfiguracji timera)
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	// zezwolenie na przerwania od przepełnienia dla timera 2
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	//wlaczenie timera
	TIM_Cmd(TIM2, ENABLE);

}


void TIM2_IRQHandler(void)
{

		if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		{
			// miejsce na kod wywoływany w momencie wystąpienia przerwania
			GPIO_ToggleBits(GPIOD, GPIO_Pin_14);//czerwona dioda
			//obliczam chwilowa predkosc, mno�e razy 5 bo liczy 5 razy w ci�gu sekundy a dziele przez ilosc obr na sek
			obrotowNaSekunde=(5 * ((float)enkoderA/sygObrot));
			obrotowNaMinute=60 * obrotowNaSekunde;
			enkoderA=0;


			//pidstruktura->predkosc=obrotowNaSekunde;
			// wyzerowanie flagi wyzwolonego przerwania
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

		}
}
