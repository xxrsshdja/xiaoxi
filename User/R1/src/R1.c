#include "R1.h"
#include "status.h"



#define CHASSIS_TASK_PRIO	25				//优先级
#define CHASSIS_STK_SIZE	128				//堆栈
static TaskHandle_t Chssis_Task_Handler;	//句柄

#define PICK_TASK_PRIO	25				//优先级
#define PICK_STK_SIZE	256				//堆栈
static TaskHandle_t Pick_Task_Handler;	//句柄

void chssis_task_start(void);
void pick_task_start(void);


R1 r1;



void chssis_task_start(void)
{
    xTaskCreate((TaskFunction_t)chassis_task,				//任务函数
                (const char*   )"chassis_task",			//名称
                (uint16_t	   )CHASSIS_STK_SIZE,			//堆栈
                (void*         )NULL,						//传递参数
                (UBaseType_t   )CHASSIS_TASK_PRIO,			//优先级
                (TaskHandle_t* )&Chssis_Task_Handler);		//句柄

}

void pick_task_start(void)
{
    xTaskCreate((TaskFunction_t)pick_task,				//任务函数
                (const char*   )"pick_task",			//名称
                (uint16_t	   )PICK_STK_SIZE,			//堆栈
                (void*         )NULL,						//传递参数
                (UBaseType_t   )PICK_TASK_PRIO,			//优先级
                (TaskHandle_t* )&Pick_Task_Handler);		//句柄

}



void system_init(void)
{






	
	while(1);
}


