#ifndef _motorh
#define _motorh

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "pid.h"

extern int czyJedzie;

void iniSterowanieKierunkiem();
void wPrzod();
void wTyl();
void stop();
void zmienKierunek();



#endif
