#include "stm32f4xx.h"
#include "misc.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_exti.h"
#include "math.h"

#include "przerwania.h"
#include "przerw.h"
#include "pwm.h"
#include "adcini.h"
#include "przycisk.h"
#include "motor.h"


//wlasnie dodalem do GITa
//kolejne

/*
PWM do sterownika - TIM3_CH1 na PC6
PWM dla picu drugi - TIM3_CH2 na PC7
*/


//diody na plytce 12 i 13, toggle jak jest przerwania od enkodera
void LEDInit()
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}


float wynikADC1;
float wynikADC2;
int wartoscPrescalera;


int doPWM;
float tymczas;

int do1000;
int doPWM2;

int main(void)
{


	SystemInit();

	//zapisuje oczekiwana predkosc w obr/s
	ZapiszOczekiwanaPredkosc(70);
	//inicjacja sterownika P I D
	IniPID(30 , (2) , 1);

	LEDInit();
	EXTILine0_Config();

	PWM2();//inicjacja timerow do przerwan na wyjsciach PWM (PC6, PC7)
	GPIO();//inicjacja PC6 PC7

	//przycisk
	IniDiody(GPIO_Pin_15);
	//GPIO_SetBits(GPIOD, GPIO_Pin_15);
	IniPrzycisk();
	IniTimerPrzycisk();//to juz samo w sobie dziala za pomoca przerwania

	//timer ktory liczy roznice i wartosci do PID - przerwanie
	IniTimerPID();


	//wyjscia PA8 PA9
	iniSterowanieKierunkiem();
	//na poczatku ustawiam wyjscia na stop
	stop();


	IniADC1();
	IniGPIOC0DlaADC1();


	//liczenie predkosci TIM2 przerwanie
	IniDiody(GPIO_Pin_14);
	IniTimerPrzerwanie1();


    while(1)
    {
    	 ADC_SoftwareStartConv(ADC1);
    	 while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
    	 wynikADC1 = (float)ADC_GetConversionValue(ADC1);


    	 TIM3->CCR1 = (10 * pidDane.wynikDoPWM);
    }


}

