/**
  ******************************************************************************
  * @file    system_communication.c/h
  * @brief   ϵͳͨ�Ų��ļ�
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
#include "system_communication.h"
#include "system_datapool.h"
#include "system_os.h"

#include "bsp_usart.h"
#include "bsp_can.h"

#include "drv_miniPC.h"
#include "drv_bluetooth.h"
#include "drv_motor.h"



/*������λ����������*/
TaskHandle_t UC_tx_Task_Handler;
void UC_tx_Task(void *p_arg);
#define UC_TX_TIM	1
/*������λ����������*/
void UC_rx_Task(void *p_arg);
TaskHandle_t UC_rx_Task_Handler;

static void miniPC_call_back(uint8_t *buf, uint16_t len);
static void bluetooth_call_back(uint8_t *buf, uint16_t len);
static void User_CAN1_RxCpltCallback(CAN_RxBuffer *CAN_RxMessage);
static void User_CAN2_RxCpltCallback(CAN_RxBuffer *CAN_RxMessage);

/**
	* @brief  ϵͳͨ�Ų��ʼ��
	* @retval None
	*/
void System_Communication_Init(void)
{
	bsp_can_Init(&hcan1,User_CAN1_RxCpltCallback);
  bsp_can_Init(&hcan2,User_CAN2_RxCpltCallback);
	bsp_usart1_Init(Usart1_Rx_Buff[0], Usart1_Rx_Buff[1], USART1_RX_BUFFER_SIZE, miniPC_call_back);
	bsp_usart2_Init(Usart2_Rx_Buff[0], Usart2_Rx_Buff[1], USART2_RX_BUFFER_SIZE, bluetooth_call_back);
  /*CAN�˲�������*/
	/*CAN1*/
	CAN_Filter_Mask_Config(&hcan1, CanFilter_0|CanFifo_0|Can_STDID|Can_DataType,0x201,0x3ff);
	CAN_Filter_Mask_Config(&hcan1, CanFilter_1|CanFifo_0|Can_STDID|Can_DataType,0x202,0x3ff);
	CAN_Filter_Mask_Config(&hcan1, CanFilter_2|CanFifo_0|Can_STDID|Can_DataType,0x203,0x3ff);
	CAN_Filter_Mask_Config(&hcan1, CanFilter_3|CanFifo_0|Can_STDID|Can_DataType,0x204,0x3ff);
	
	CAN_Filter_Mask_Config(&hcan1, CanFilter_4|CanFifo_0|Can_STDID|Can_DataType,0x510,0x3ff);	//ȫ����λ
	CAN_Filter_Mask_Config(&hcan1, CanFilter_6|CanFifo_0|Can_STDID|Can_DataType,0x321,0x3ff);	//���̽Ƕ�
	/*CAN2*/
	CAN_Filter_Mask_Config(&hcan2, CanFilter_15|CanFifo_1|Can_STDID|Can_DataType,0x201,0x3ff);
	CAN_Filter_Mask_Config(&hcan2, CanFilter_16|CanFifo_1|Can_STDID|Can_DataType,0x202,0x3ff);
  CAN_Filter_Mask_Config(&hcan2, CanFilter_17|CanFifo_1|Can_STDID|Can_DataType,0x203,0x3ff);
	CAN_Filter_Mask_Config(&hcan2, CanFilter_18|CanFifo_1|Can_STDID|Can_DataType,0x204,0x3ff);
	
}
/**
	* @brief  ϵͳͨ�Ų�ѭ��
	* @retval None
	*/
void System_Communication_Loop(void)
{
	/*������λ����Ϣ����*/
	//xTaskCreate(UC_rx_Task, "uc_rx_task", Small_Stack_Size, NULL, PrioritySuperHigh, &UC_rx_Task_Handler);
	/*������λ����Ϣ����*/
	//xTaskCreate(UC_tx_Task, "uc_tx_task", Tiny_Stack_Size, NULL, PriorityHigh, &UC_tx_Task_Handler);

}
/*=========================================================�жϻص�����=========================================================*/
/**
	* @brief  miniPC���մ����жϻص�����
	* @retval None
	*/
static void miniPC_call_back(uint8_t *buf, uint16_t len)
{
	static BaseType_t* miniPC_TaskWoken;
	static USART_COB	miniPC_port = {0};
	if(len == MINIPC_FRAME_LENGTH)
	{
		if(buf[0] == MINIPC_HEAD && buf[len-1] == MINIPC_TAIL)
		{
			miniPC_port.port_num = 1;
			miniPC_port.address = buf;
			xTaskNotifyFromISR(UC_rx_Task_Handler, (uint32_t) &miniPC_port, eSetValueWithOverwrite, miniPC_TaskWoken);
		}
	}
}

/**
	* @brief  �������ݽ��մ����жϻص�����
	* @retval None
	*/
static void bluetooth_call_back(uint8_t *buf, uint16_t len)
{
	static BaseType_t* BT_TaskWoken;
	static USART_COB	BT_port = {0};
	if(len == BT_FRAME_LENGTH)
	{
		if(buf[0] == BT_HEAD && buf[len-1] == BT_TAIL)
		{
			BT_port.port_num = 2;
			BT_port.address = buf;
			xTaskNotifyFromISR(UC_rx_Task_Handler, (uint32_t) &BT_port, eSetValueWithOverwrite, BT_TaskWoken);
		}
	}
}

/**
	* @brief  CAN1�����жϻص�����
	* @retval None
	*/
static void User_CAN1_RxCpltCallback(CAN_RxBuffer *CAN_RxMessage)
{
	Driver_motor_DatePrcess(CAN_RxMessage->header.StdId, CAN_RxMessage->data);

	
	
}
/**
	* @brief  CAN2�����жϻص�����
	* @retval None
	*/
static void User_CAN2_RxCpltCallback(CAN_RxBuffer *CAN_RxMessage)
{
	//Shoot_motor_DatePrcess(CAN_RxMessage->header.StdId, CAN_RxMessage->data);
	
}


/*=========================================================������=========================================================*/

/** 
	* @brief ��λ��������Ϣ������� 
 **/
void UC_rx_Task(void *p_arg)
{
	static USART_COB* UC_RxPort;
	while(1)
	{
		if(xTaskNotifyWait(0x00000000, 0xFFFFFFFF, (uint32_t *) &UC_RxPort, portMAX_DELAY) == pdTRUE)
		{
			if(UC_RxPort->port_num == 1)
			{
				//miniPC_DatePrcess(UC_RxPort->address);
			}
			else if(UC_RxPort->port_num == 2)
			{
				//BT_DatePrcess(UC_RxPort->address);
			}
		}
	}
}

/** 
	* @brief ������λ����Ϣ���� 
 **/
void UC_tx_Task(void *p_arg)
{
	
	TickType_t xLastWakeTime_t = xTaskGetTickCount();
	//static miniPC_tx_Union_t miniPC_port;
//	static BT_tx_Union_t BT_port;
	
	while(1)
	{
		
//		miniPC_port.txpack.Speed1[0] = gimbal_control.shoot_control.shoot_pwm1_val>>8;
//		miniPC_port.txpack.Speed1[1] = gimbal_control.shoot_control.shoot_pwm1_val;
//		miniPC_port.txpack.Speed2[0] = gimbal_control.shoot_control.shoot_pwm2_val>>8;
//		miniPC_port.txpack.Speed2[1] = gimbal_control.shoot_control.shoot_pwm2_val;
//		miniPC_port.txpack.Yaw = chassis_control.yaw;
//		miniPC_port.txpack.voltage = sys_dat.voltage;
		
		//miniPC_DateSend(&miniPC_port);
		
//		BT_port.txpack.pwm_value[0] = gimbal_control.shoot_control.shoot_pwm1_val;
//		BT_port.txpack.pwm_value[1] = gimbal_control.shoot_control.shoot_pwm2_val;
//		BT_port.txpack.check	=	(BT_port.txpack.pwm_value[0] + BT_port.txpack.pwm_value[1]);
//		BT_DateSend(&BT_port);
		
		vTaskDelayUntil(&xLastWakeTime_t,UC_TX_TIM);
	}
}

