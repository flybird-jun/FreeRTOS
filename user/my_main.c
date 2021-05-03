
#include"FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "stm32f10x.h"
#include "projdefs.h"
#include "portmacro.h"
#include "task.h"
#include "misc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
//extern void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource);
void LED_Init(void) 
{  
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //Ê¹ï¿½ï¿½PB,PEï¿½Ë¿ï¿½Ê±ï¿½ï¿½
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 ï¿½Ë¿ï¿½ï¿½ï¿½ï¿½ï¿½
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IOï¿½ï¿½ï¿½Ù¶ï¿½Îª50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //ï¿½ï¿½ï¿½ï¿½ï¿½è¶¨ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê¼ï¿½ï¿½GPIOB.5
 GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 ï¿½ï¿½ï¿½ï¿½ï¿½

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 ï¿½Ë¿ï¿½ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½IOï¿½ï¿½ï¿½Ù¶ï¿½Îª50MHz
 GPIO_SetBits(GPIOE,GPIO_Pin_5); 	
} 
/*
extern void xPortSysTickHandler(void); 

void SysTick_Handler(void) 
{  

	xPortSysTickHandler();  

} */
void sys_init() 
{ 
	u32 reload;  
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	
	reload=SystemCoreClock/1000000;				//Ã¿ï¿½ï¿½ï¿½ÓµÄ¼ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Î»ÎªM  
	reload*=1000000/configTICK_RATE_HZ;			//ï¿½ï¿½ï¿½ï¿½configTICK_RATE_HZï¿½è¶¨ï¿½ï¿½ï¿½Ê±ï¿½ï¿½
												//reloadÎª24Î»ï¿½Ä´ï¿½ï¿½ï¿½,ï¿½ï¿½ï¿½Öµ:16777216,ï¿½ï¿½72Mï¿½ï¿½,Ô¼ï¿½ï¿½0.233sï¿½ï¿½ï¿½ï¿½	
	//fac_ms=1000/configTICK_RATE_HZ;				//ï¿½ï¿½ï¿½ï¿½OSï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê±ï¿½ï¿½ï¿½ï¿½ï¿½Ùµï¿½Î»	   

	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   	//ï¿½ï¿½ï¿½ï¿½SYSTICKï¿½Ð¶ï¿½
	SysTick->LOAD=reload; 						//Ã¿1/configTICK_RATE_HZï¿½ï¿½ï¿½Ð¶ï¿½Ò»ï¿½ï¿½	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	//ï¿½ï¿½ï¿½ï¿½SYSTICK   
} 

static void AppTask(void* parameter)
{	
 
		while(1)
		{
			GPIOB->ODR|=1<<5;
			GPIOE->ODR|=1<<5;
	//	delay_ms(500);
		vTaskDelay(500);
			GPIOB->ODR&=~(1<<5);
		
			GPIOE->ODR&=~(1<<5);
 vTaskDelay(500);
	//	delay_ms(500);
	}
}
int main()
{
	BaseType_t xReturn = pdPASS;/* ¶¨ÒåÒ»¸ö´´½¨ÐÅÏ¢·µ»ØÖµ£¬Ä¬ÈÏÎªpdPASS */

  /* ¿ª·¢°åÓ²¼þ³õÊ¼»¯ */
  //BSP_Init();
	TaskHandle_t AppTask_Handle;
	LED_Init();
	sys_init();
	LED_Init();
   xReturn = xTaskCreate((TaskFunction_t )AppTask,  /* ÈÎÎñÈë¿Úº¯Êý */
                        (const char*    )"AppTask",/* ÈÎÎñÃû×Ö */
                        (uint16_t       )512,  /* ÈÎÎñÕ»´óÐ¡ */
                        (void*          )NULL,/* ÈÎÎñÈë¿Úº¯Êý²ÎÊý */
                        (UBaseType_t    )1, /* ÈÎÎñµÄÓÅÏÈ¼¶ */
                        (TaskHandle_t*  )&AppTask_Handle);/* ÈÎÎñ¿ØÖÆ¿éÖ¸Õë */ 
  /* Æô¶¯ÈÎÎñµ÷¶È */           
  if(pdPASS == xReturn)
    vTaskStartScheduler();   /* Æô¶¯ÈÎÎñ£¬¿ªÆôµ÷¶È */
  else
    return -1;  
  
  while(1);   /* Õý³£²»»áÖ´ÐÐµ½ÕâÀï */ 
	/*
*/
	
}
