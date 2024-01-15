/**
  ******************************************************************************
  * @file    drv_ps2.c/h
  * @brief   ps2ң����Э�������������
  * @version 1.0
	@verbatim
	===================================================================      
									##### How to use this driver #####
	=================================================================== 
    @note
      -# ʹ��PS2_DateDatePrcess�����������
  
      -# ʹ��get_ps2_control_point��ȡ����������

         
    @attention
      
  ******************************************************************************
  * @attention
  * 
  * if you had modified this file, please make sure your code does not have any 
  * bugs, update the version Number, write dowm your name and the date. The most
  * important thing is make sure the users will have clear and definite under-
  * standing through your new brief.
  ******************************************************************************
*/
#include "drv_ps2.h"
#include "bsp_timer.h"
#include "bsp_spi.h"

#define sp2_delay	delay_us_nos
#define DelayTIM	10

#define CS_H		HAL_GPIO_WritePin(SP2_CS_GPIO_Port,SP2_CS_Pin,GPIO_PIN_SET);
#define CS_L		HAL_GPIO_WritePin(SP2_CS_GPIO_Port,SP2_CS_Pin,GPIO_PIN_RESET);

static PS2_ctrl_t ps2_ctrl = {
	.ps2_cmd = {0x01,0x42},
	.ps2_data =  {0},
	.XY = {500, 500, 500, 500},		//ҡ��ģ��ֵ(500����)
	.MASK = {0},						//����ֵ��ʼ��
	.PS2_Mode = No,
};


/**
  * @brief          ͨ��ָ���ȡPS2�ֱ�����
  * @retval         none
  */
const PS2_ctrl_t *get_ps2_control_point(void)
{
    return &ps2_ctrl;
}


/**
  * @brief      PS2�ֱ���ȡ����
  * @retval     none
  */
void PS2_DateGet(void)
{
	volatile uint8_t byte=0;
	CS_L  //���ͣ���ʼͨѶ
	sp2_delay(DelayTIM);
	SPI_ReadWrite_8Byte(SPI1, ps2_ctrl.ps2_cmd[0]);									//����0x01������ͨѶ
	sp2_delay(DelayTIM);
	ps2_ctrl.ps2_data[1] = SPI_ReadWrite_8Byte(SPI1, ps2_ctrl.ps2_cmd[1]);		//����0x42�������������
	sp2_delay(DelayTIM);
	if(ps2_ctrl.ps2_data[1] == 0x41)
	{
		ps2_ctrl.PS2_Mode = Green;
	}
	else if(ps2_ctrl.ps2_data[1] == 0x73)
	{
		ps2_ctrl.PS2_Mode = Red;
	}
	else
	{
		ps2_ctrl.PS2_Mode = No;
	}
	ps2_ctrl.ps2_data[2] = SPI_ReadWrite_8Byte(SPI1, 0x00);
	sp2_delay(DelayTIM);
	if(ps2_ctrl.ps2_data[2] == 0x5a)
	{
		for(byte = 3;byte <9;byte++){
			ps2_ctrl.ps2_data[byte] = SPI_ReadWrite_8Byte(SPI1, 0x00);
			sp2_delay(DelayTIM);
		}
	}
	CS_H  	 //���ߣ�׼���´�ͨѶ
}

/**
  * @brief      PS2�ֱ������������
  * @retval     none
  */
void PS2_DateClear(void)
{
	uint8_t byte;
	for(byte=0;byte<9;byte++)
		ps2_ctrl.ps2_data[byte]=0x00;
}

/**
  * @brief      PS2�ֱ����˽���
  * @retval     none
  */
void PS2_DateAnolog(void)
{
	uint8_t i = 0;
	if(ps2_ctrl.PS2_Mode == Red)
	{
		for ( i = 5; i < 9; i++)
		{
			ps2_ctrl.ps2_data[i] = (uint16_t)ps2_ctrl.ps2_data[i];
			ps2_ctrl.XY[i-5] = (ps2_ctrl.ps2_data[i] * 1000)/255;
			if(ps2_ctrl.XY[i-5] < 503 && ps2_ctrl.XY[i-5] >497) ps2_ctrl.XY[i-5] = 500;
		}
	}
	else if(ps2_ctrl.PS2_Mode == Green)
	{
		for ( i = 0; i < 4; i++)
		{
			ps2_ctrl.XY[i] = 500;
		}
	}
}

/**
  * @brief      PS2�ֱ���������
  * @retval     none
  */
void PS2_DateKey(void)
{
	uint8_t loc = 1;
	uint8_t set = 0;
  for(loc = 8;loc > 0;loc--)  //λ�����ȡǰ��λ
  {
		loc -= 1;
		ps2_ctrl.MASK[set] = (ps2_ctrl.ps2_data[3]&(1<<loc))>>loc;
		loc += 1;
		set++;
  }
	for(loc = 8;loc > 0;loc--)   //λ�����ȡ���λ
  {
		loc -= 1;
		ps2_ctrl.MASK[set] = (ps2_ctrl.ps2_data[4]&(1<<loc))>>loc;
		loc += 1;
		set++;
  }
	for(set = 0;set < 16;set++)    //��ΪЭ���ϰ�������Ϊ0��δ����Ϊ1������Ҫ������з�ת
	{
		if(ps2_ctrl.MASK[set] == 1)  ps2_ctrl.MASK[set] = 0;
		else  ps2_ctrl.MASK[set] = 1;			 
	}
}


/**
  * @brief      PS2�ֱ����ݽ��
  * @retval     none
  */
void PS2_DateDatePrcess(void)
{
	PS2_DateClear();
	PS2_DateGet();
	PS2_DateAnolog();
	PS2_DateKey();
}



