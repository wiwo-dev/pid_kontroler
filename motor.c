#include "motor.h"

int czyJedzie=0;
//tyl stop przod tyl stop przod
//tyl=0, przod=1 nie ustawiam stop
int kierunek=0;

//wyjscia PA8 PA9 podlaczone do wejsc INa INb sterownika
void iniSterowanieKierunkiem()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef x;
	x.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	x.GPIO_Mode = GPIO_Mode_OUT;
	x.GPIO_OType = GPIO_OType_PP;
	x.GPIO_Speed = GPIO_Speed_50MHz;
	x.GPIO_PuPd = GPIO_PuPd_NOPULL;//tu tez cos zmienial
	GPIO_Init(GPIOA, &x);
}



void wPrzod()
{
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
	GPIO_ResetBits(GPIOA, GPIO_Pin_9);
	kierunek=1;
	czyJedzie=1;
}

void wTyl()
{

	GPIO_ResetBits(GPIOA, GPIO_Pin_8);
	GPIO_SetBits(GPIOA, GPIO_Pin_9);
	kierunek=0;
	czyJedzie=1;
}

void stop()
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);
	GPIO_ResetBits(GPIOA, GPIO_Pin_9);
	czyJedzie=0;
	zeruj_sumError();
}


void zmienKierunek()
{
	if(czyJedzie)
	{
		stop();
	}
	else
	{
		if(kierunek==0)//wczesniej w tyl
		{
			wPrzod();
		}
		else //wczesniej w przod
		{
			wTyl();
		}

	}
}
