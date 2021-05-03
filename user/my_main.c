
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
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //LED0-->PB.5 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
 GPIO_SetBits(GPIOB,GPIO_Pin_5);						 //PB.5 �����

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 �˿�����, �������
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
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
	
	reload=SystemCoreClock/1000000;				//ÿ���ӵļ������� ��λΪM  
	reload*=1000000/configTICK_RATE_HZ;			//����configTICK_RATE_HZ�趨���ʱ��
												//reloadΪ24λ�Ĵ���,���ֵ:16777216,��72M��,Լ��0.233s����	
	//fac_ms=1000/configTICK_RATE_HZ;				//����OS������ʱ�����ٵ�λ	   

	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   	//����SYSTICK�ж�
	SysTick->LOAD=reload; 						//ÿ1/configTICK_RATE_HZ���ж�һ��	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	//����SYSTICK   
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
	BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ����ֵ��Ĭ��ΪpdPASS */

  /* ������Ӳ����ʼ�� */
  //BSP_Init();
	TaskHandle_t AppTask_Handle;
	LED_Init();
	sys_init();
	LED_Init();
   xReturn = xTaskCreate((TaskFunction_t )AppTask,  /* ������ں��� */
                        (const char*    )"AppTask",/* �������� */
                        (uint16_t       )512,  /* ����ջ��С */
                        (void*          )NULL,/* ������ں������� */
                        (UBaseType_t    )1, /* ��������ȼ� */
                        (TaskHandle_t*  )&AppTask_Handle);/* ������ƿ�ָ�� */ 
  /* ����������� */           
  if(pdPASS == xReturn)
    vTaskStartScheduler();   /* �������񣬿������� */
  else
    return -1;  
  
  while(1);   /* ��������ִ�е����� */ 
	/*
*/
	
}
