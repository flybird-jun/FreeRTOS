
#include"FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "stm32f10x.h"
#include "projdefs.h"
#include "portmacro.h"
#include "task.h"
#include "misc.h"
extern void Driver_Init();

#include "Led.h"
void led_task_control(void * parameter)
{
	while(1)
	{
		RedLed_On();
		GreenLed_Off();
		vTaskDelay(200);
		RedLed_Off();
		GreenLed_On();
		vTaskDelay(200);
	}
}
int main(void)
{
  	TaskHandle_t 	StartTask_Handler;
	int i,j;
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	Driver_Init();
	
    xTaskCreate((TaskFunction_t )led_task_control,            
                (const char*    )"start_task",          
                (uint16_t)128,        
                (void*          )NULL,                  
                (UBaseType_t    )1,       
                (TaskHandle_t*  )&StartTask_Handler);             
    vTaskStartScheduler();        
}

