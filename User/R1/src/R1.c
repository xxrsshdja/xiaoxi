#include "R1.h"
#include "status.h"



#define CHASSIS_TASK_PRIO	25				//���ȼ�
#define CHASSIS_STK_SIZE	128				//��ջ
static TaskHandle_t Chssis_Task_Handler;	//���

#define PICK_TASK_PRIO	25				//���ȼ�
#define PICK_STK_SIZE	256				//��ջ
static TaskHandle_t Pick_Task_Handler;	//���

void chssis_task_start(void);
void pick_task_start(void);


R1 r1;



void chssis_task_start(void)
{
    xTaskCreate((TaskFunction_t)chassis_task,				//������
                (const char*   )"chassis_task",			//����
                (uint16_t	   )CHASSIS_STK_SIZE,			//��ջ
                (void*         )NULL,						//���ݲ���
                (UBaseType_t   )CHASSIS_TASK_PRIO,			//���ȼ�
                (TaskHandle_t* )&Chssis_Task_Handler);		//���

}

void pick_task_start(void)
{
    xTaskCreate((TaskFunction_t)pick_task,				//������
                (const char*   )"pick_task",			//����
                (uint16_t	   )PICK_STK_SIZE,			//��ջ
                (void*         )NULL,						//���ݲ���
                (UBaseType_t   )PICK_TASK_PRIO,			//���ȼ�
                (TaskHandle_t* )&Pick_Task_Handler);		//���

}



void system_init(void)
{






	
	while(1);
}


