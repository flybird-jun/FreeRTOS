#include "Led.h"
void Led_Init()
{
	GPIO_InitTypeDef Gpio_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE,ENABLE);
	Gpio_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	Gpio_InitStruct.GPIO_Pin = GPIO_Pin_5;
	Gpio_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB, &Gpio_InitStruct);
	GPIO_Init(GPIOE, &Gpio_InitStruct);
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	GPIO_SetBits(GPIOE,GPIO_Pin_5);
}
//PB5 红灯 PE5 绿灯
void RedLed_On()
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_5);
}
void GreenLed_On()
{
	GPIO_ResetBits(GPIOE,GPIO_Pin_5);
}
void RedLed_Off()
{
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
}
void GreenLed_Off()
{
	GPIO_SetBits(GPIOE,GPIO_Pin_5);
}

