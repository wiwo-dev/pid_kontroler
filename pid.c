#include "pid.h"

//dane na temat PID i silnika
struct PID_DANE pidDane;


//inicjowanie nastawow
void IniPID(float P, float I, float D)
{

	pidDane.sumError=150;
	pidDane.sumErrorStart=150;
	pidDane.aktualnaPredkosc=0;
	pidDane.KP = P;
	pidDane.KI = I;
	pidDane.KD = D;
	pidDane.maxError=65000; // (pidDane.KP + 1);
	pidDane.maxSumError = 699999995535;
	pidDane.mnoznik = 1;
}

//najwazniejsza funkcia, uruchamiana co sekunde w przerwaniu, dokonuje wszystkich obliczen i zmian w PID_DANE
float PIDLicz()
{
  float error; 				//blad, uchyb
  float p_term; 			//wynik po funkcji z czesci P
  float d_term; 			//wynik po funkcji z czesci D
  float i_term; 			//wynik po funkcji z czesci I
  float ret; 				//wynik calosci - jest zwracany
  float temp; 				//do obliczania sumy dotychczasowych bledow
  float wzmocnienieALL;		//wzmocnienie na koncu obliczen

  error = pidDane.oczekiwanaPredkosc - pidDane.aktualnaPredkosc;		//blad, uchyb

  // Oblicza czesc P
  p_term = pidDane.KP * error;
  pidDane.wartP=p_term;						//zapis do zmiennej w strukturze w celu podejrzenia w STM Studio

  // Oblicza czesc I
  temp = pidDane.sumError + error; 			//dodaje aktualny blad do sumy poprzednich
  pidDane.sumError = temp;
  i_term = pidDane.KI * pidDane.sumError;	//oblicza czesc I - KI razy dotychczasowa suma bledow
  pidDane.wartI=i_term;						//zapis do zmiennej w strukturze w celu podejrzenia w STM Studio

  // Oblicza czesc D
  d_term = pidDane.KD * (pidDane.poprzedniaPredkosc - pidDane.aktualnaPredkosc);
  pidDane.wartD=d_term;						//zapis do zmiennej w strukturze w celu podejrzenia w STM Studio
  pidDane.poprzedniaPredkosc = pidDane.aktualnaPredkosc; 	//zapisuje aktualna predkosc jako poprzednia


  //tutaj moze cos z ifem jak stoi w miejscu...?
  wzmocnienieALL = pidDane.mnoznik;


  ret = (wzmocnienieALL * (p_term + i_term + d_term));	// suma P + I + D pomnozona razy wzmocnienie
  pidDane.retPrzedIf=ret;										//tylko do sprawdzenia w STM Studio

  //ponizszy if zeby silnik sie nie wy��cza� i nie przekroczy� wyjscia na PWM
  //100% = 0xFFFF = 65535

  if(ret > 6553)
    ret = 6553;
  else if(ret < 0) //bo ponizej silnik sie zatrzymuje... (za slaby zasilacz)
    ret = 0;
  pidDane.wynikDoPWM = ret;
  return(ret);
}

//funkcja sluzy do zerowania zmiennej sumujacej uchyby
void zeruj_sumError()
{
	pidDane.sumError = pidDane.sumErrorStart;
}

void ZapiszOczekiwanaPredkosc(float oP)
{
	pidDane.oczekiwanaPredkosc=oP;
}



void IniTimerPID()//obsluga timerem
{
	//ustawienie trybu pracy priorytetow przerwan
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef p;
	//numer przerwania
	p.NVIC_IRQChannel = TIM4_IRQn;
	// priorytet główny
	p.NVIC_IRQChannelPreemptionPriority = 0x00;
	// subpriorytet
	p.NVIC_IRQChannelSubPriority = 0x00;
	// uruchom dany kanał
	p.NVIC_IRQChannelCmd = ENABLE;
	// zapisz wypełnioną strukturę do rejestrów
	NVIC_Init(&p);

	//doprowadzenie sygnalu zerowego
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	TIM_TimeBaseInitTypeDef a;
	a.TIM_Prescaler=8400;
	a.TIM_CounterMode=TIM_CounterMode_Up;
	a.TIM_Period=2499;
	a.TIM_ClockDivision=0;
	a.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM4, &a);


	// wyczyszczenie przerwania od timera 2 (wystąpiło przy konfiguracji timera)
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	// zezwolenie na przerwania od przepełnienia dla timera 2
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	//wlaczenie timera
	TIM_Cmd(TIM4, ENABLE);
}


//przerwanie obslugujace regulator PID
void TIM4_IRQHandler(void)
{
		if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
		{
			if(czyJedzie)
			{
				pidDane.aktualnaPredkosc=obrotowNaMinute;
				pidDane.uchybPredkosci = pidDane.oczekiwanaPredkosc-pidDane.aktualnaPredkosc;
				PIDLicz();		//ta funkcja wszystko liczy
			}
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		}
}
