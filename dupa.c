
/*
  void IniWejscia()
  {
	  GPIO_InitTypeDef  GPIO_InitStructure;

	  // GPIOD Periph clock enable *
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

	  /// Configure PD12, PD13, PD14 and PD15 in output pushpull mode /
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_Init(GPIOD, &GPIO_InitStructure);
  }



void IniDiodyPWM()
{
	//dorowadzenie sygna³u zerowego do portu
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef x;
	x.GPIO_Pin = GPIO_Pin_0;//jgfjcfthfthjtfh
	x.GPIO_Mode = GPIO_Mode_AF; //tutaj jest inaczej niz bez PWM af oznacza funkcje alternetywna
	x.GPIO_Speed = GPIO_Speed_100MHz;
	x.GPIO_PuPd = GPIO_PuPd_UP;//tu tez jest inaczej WAZNE!!!
	GPIO_Init(GPIOB, &x);



	//doprowadzenie sygnalu zerowego do portu
	//korzystam z TIM2 ktory ma rozdzielczosc 32bity
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_TimeBaseInitTypeDef a;
	a.TIM_Prescaler=1;//dzielnik
	a.TIM_CounterMode=TIM_CounterMode_Up;
	a.TIM_Period=8399; //liczba impulsow do ktorych zlicza licznik
	a.TIM_ClockDivision=0;
	a.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM3, &a);

	//mapowanie. nie jest potrzebne do samego odpalenia diody
	//mapowanie zeby polaczyc z timerem
	GPIO_PinAFConfig (GPIOB, GPIO_PinSource0 , GPIO_AF_TIM3 );//jgfcfthcfthtfh

	//tutaj zaczyna sie fragment odpowiedzialny za jasnosc
	TIM_OCInitTypeDef b;
	b.TIM_OCMode=TIM_OCMode_PWM1;
	b.TIM_OutputState=TIM_OutputState_Enable;//wybor stanu wyjscia
	b.TIM_Pulse=0 ;//wartosc ladowana do rejestru porownania
	b.TIM_OCPolarity=TIM_OCPolarity_High;//polaryzacja wyjscia

	//OC2 bo wedlug manuala PB3 dziala z TIM2_CH2 - chodzi o kanal 2
	//na poczatku by³ kana³ 2 ale zosta³ zmieniony na 3 przy próbie ogarniecia dlaczego zielona dioda sie swieci...
	TIM_OC3Init(TIM3, &b);//ugjvgyuvfghttfgvhtfvh


	//uruchomienie rejestra Preload Register
	TIM_OC3PreloadConfig (TIM3 , TIM_OCPreload_Enable ) ;
	TIM_ARRPreloadConfig (TIM3 , ENABLE) ;
	//wlaczenie timera
	TIM_Cmd(TIM3, ENABLE);

	//jasnosc w procentach
	TIM3->CCR3 = 50;
}
 */
