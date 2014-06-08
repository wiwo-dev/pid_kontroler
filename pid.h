#ifndef _pidh
#define _pidh
#include "misc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_adc.h"
#include "przerw.h"
#include "motor.h"


extern struct PID_DANE pidDane;		//extern umozliwia dostep do struktury w calym projekcie, nie wiem czy to dobrze ale duzo ulatwia


typedef struct PID_DANE
{
	float wynikDoPWM;				//tutaj te¿ jest zapisywany wynik dzia³ania funkcji
	float aktualnaPredkosc;			//aktualna predkosc obrotowa w obr/sek
	float oczekiwanaPredkosc;		//oczekiwana predkosc
	float uchybPredkosci;			//= oczekiwanaPredkosc-aktualnaPredkosc
	float poprzedniaPredkosc;		//predkosc zapisana w poprzednim dzialaniu, w czesci D
	float sumError;					//suma uchybów wykorzystywana przy czesci I
	float sumErrorStart;				//przy inicjacji zapisuje sie wart poczatkowoa ktora musi byc bo za slaby zasilacz
	float KP;						//skladowa P
	float KI;						//skladowa I
	float KD;						//skladowa D
	float maxError;					//okreslony max dla uchybPredkosci, w sumie nie wiem po co
	float maxSumError;				//okreslony max dla sumy uchybow - sumError, tez nie wiem po co
	float mnoznik;					//wzmocnienie wyniku

	//ponizej wykorzystywane tylko do sprawdzania wartosci w trakcie dzialania w STM Studio
	float wartP;
	float wartI;
	float wartD;
	float retPrzedIf;

};

void IniTimerPID();

void ZapiszOczekiwanaPredkosc(float oP);

void IniPID(float P, float I, float D);


float PIDLicz();

void zeruj_sumError();

#endif
