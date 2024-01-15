/**
  ******************************************************************************
  * @file    system_debug.c/h
  * @brief   ϵͳ����
	*					 �����ĵ�������ר�����ڵ���
  * @version 1.0
  * @par Change Log��
  * 		Date				Version				Author					Description
	*			22.12.12		V1.0					Gsx							Creator
  ******************************************************************************
  * @attention
	*	��ģ����Ҫ..\Middlewares\Debug���ļ�֧��
  * if you had modified this file, please make sure your code does not have any 
  * bugs, update the version Number, write dowm your name and the date. The most
  * important thing is make sure the users will have clear and definite under-
  * standing through your new brief.
  ******************************************************************************
*/
#include "system_debug.h"
#include "system_os.h"


/*������*/
TaskHandle_t TestTask_Handler;
/*������*/
void Test_Task(void *p_arg);
/*����ʱ��*/
#define TEST_TASK_TIM	1

void System_Debug_Init(void)
{
	
}

/**
	*	@brief ���������ʼ��
 **/
void System_Debug_Loop(void)
{
	
	xTaskCreate((TaskFunction_t)Test_Task,             
						 (const char*    )"test_task",           
						 (uint16_t       )Small_Stack_Size,        
						 (void*          )NULL,                  
						 (UBaseType_t    )PriorityHigh,        
						 (TaskHandle_t*  )&TestTask_Handler);   
	
}

/**
	*	@brief ��������
 **/
void Test_Task(void *p_arg)
{
	TickType_t xLastWakeTime_t = xTaskGetTickCount();
	while(1)
	{
		
		vTaskDelayUntil(&xLastWakeTime_t,TEST_TASK_TIM);
	}
	
}

