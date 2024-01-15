/*___    _____  ___    _____  ___    _____  _   _    __     __      __      ___ 
	|  _`\ (  _  )(  _`\ (  _  )(  _`\ (  _  )( ) ( ) /'__`\ /' _`\  /'__`\  /'_  )
	| (_) )| ( ) || (_) )| ( ) || ( (_)| ( ) || `\| |(_)  ) )| ( ) |(_)  ) )(_)_) |
	| ,  / | | | ||  _ <'| | | || |  _ | | | || , ` |   /' / | | | |   /' /  _(_ < 
	| |\ \ | (_) || (_) )| (_) || (_( )| (_) || |`\ | /' /( )| (_) | /' /( )( )_) |
	(_) (_)(_____)(____/'(_____)(____/'(_____)(_) (_)(_____/'`\___/'(_____/'`\____)
  ______ _____                  _      
 |  ____|  __ \                | |     
 | |__  | |__) |   ___ ___   __| | ___ 
 |  __| |  _  /   / __/ _ \ / _` |/ _ \
 | |____| | \ \  | (_| (_) | (_| |  __/
 |______|_|  \_\  \___\___/ \__,_|\___|
																																								 */
/**
  ******************************************************************************
  * @file    system_start.c/h
  * @brief   ������ʼ��
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
#include "system_start.h"
#include "system.h"
#include "system_app.h"
#include "system_driver.h"
#include "system_communication.h"
#include "system_debug.h"
#include "R1.h"


uint32_t Systick;

/**
	* @brief  ϵͳ��ʼ��
	* @retval None
	*/
void System_Init(void)
{
	HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_RESET);	//��ʼ��ʼ��ָʾ��
	Systick = HAL_RCC_GetSysClockFreq();	//��ȡϵͳ��Ƶ
	System_Driver_Init();									//ϵͳ�ײ�������ʼ��
	System_Communication_Init();					//ϵͳͨ�Ų��ʼ��
	System_App_Init();										//ϵͳӦ�ò��ʼ��
	HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_SET);		//������ʼ��ָʾ��
	
}

/**
	* @brief  ϵͳ�����ʼ��
	* @retval None
	*/
void RTOS_Init(void)
{
	System_Driver_Loop();
	System_Communication_Loop();
	chssis_task_start();
	pick_task_start();
	//System_App_Loop();
	//System_Debug_Loop();
}

