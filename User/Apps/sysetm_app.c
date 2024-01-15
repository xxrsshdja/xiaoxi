/**
  ******************************************************************************
  * @file    system_communication.c/h
  * @brief   ϵͳӦ�ò��ļ�
  * @version 1.0
  * @par Change Log��
  * 		Date				Version				Author					Description
	*			22.6.1			V1.0					Gsx							Creator
  ******************************************************************************
  * @attention
  * 
  * if you had modified this file, please make sure your code does not have any 
  * bugs, update the version Number, write dowm your name and the date. The most
  * important thing is make sure the users will have clear and definite under-
  * standing through your new brief.
  ******************************************************************************
*/	
#include "system_app.h"
#include "system_os.h"
#include "system_datapool.h"


//#include "mod_Clamp_Arm.h"

/*ϵͳ״̬������*/
TaskHandle_t System_Task_Handler;
void System_Task(void *p_arg);
#define SYSTEM_TIM	1
/*��������*/
TaskHandle_t Chassis_Task_Handler;
void Chassis_Task(void *p_arg);
#define CHASSIS_TIM	1
/*��̨ģ��*/
TaskHandle_t GimbalTask_Handler;
void Gimbal_Task(void *p_arg);
#define GIMBAL_TASK_TIM	1
/*ʰȡģ��*/
TaskHandle_t Clamp_ArmTask_Handler;
void Clamp_Arm_Task(void *p_arg);
#define CLAMP_ARM_TASK_TIM	1

/**
	* @brief  ϵͳӦ�ò��ʼ��
	* @retval None
	*/
void System_App_Init(void)
{
	//Chassis_Init(&chassis_control);

	//Clamp_Arm_Init(&clamp_arm_control);

}

/**
	* @brief  ϵͳӦ�ò�ѭ��
	* @retval None
	*/
void System_App_Loop(void)
{

  /*��������*/
	xTaskCreate(Chassis_Task, "chassis_task", Normal_Stack_Size, NULL, PriorityHigh, &Chassis_Task_Handler); 
	
	/*ʰȡ����*/
	xTaskCreate(Clamp_Arm_Task, "clamp_arm_task", Normal_Stack_Size, NULL, PriorityHigh, &Clamp_ArmTask_Handler);	

}



/** 
	* @brief �������� 
 **/
void Chassis_Task(void *p_arg)
{
	TickType_t xLastWakeTime_t = xTaskGetTickCount();
	while(1)
	{
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
//		Chassis_Loop(&chassis_control);
//		CAN_CMD_DRIVER(chassis_control.drive_motor[0].set_current, chassis_control.drive_motor[1].set_current, 
//									 chassis_control.drive_motor[2].set_current, chassis_control.drive_motor[3].set_current);
		vTaskDelayUntil(&xLastWakeTime_t,CHASSIS_TIM);
	}
		
}



/** 
	* @brief ʰȡ���� 
 **/
void Clamp_Arm_Task(void *p_arg)
{
	TickType_t xLastWakeTime_t = xTaskGetTickCount();
	while(1)
	{
		HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
		//Clamp_Arm_Loop(&clamp_arm_control);
		vTaskDelayUntil(&xLastWakeTime_t,CLAMP_ARM_TASK_TIM);
	}
		
}

