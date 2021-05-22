#ifndef __LED_H
#define __LED_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
extern void Led_Init();
extern void RedLed_On();
extern void GreenLed_On();
extern void RedLed_Off();
extern void GreenLed_Off();
#endif
