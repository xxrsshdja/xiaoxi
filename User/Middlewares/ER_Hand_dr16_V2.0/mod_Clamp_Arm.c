/**
  ******************************************************************************
  * @file    Clamp_Arm.c/h
  * @brief   ��צʰȡģ��
  * @version 2.0
  * @par Change Log��
  * 		Date				Version				Author					Description
	*			23.3.28			V1.0					Gsx							Creator
	*			23.6.2			V2.0					Gsx							�޸����API������������	
  ******************************************************************************
  * @attention
  * 
  * if you had modified this file, please make sure your code does not have any 
  * bugs, update the version Number, write dowm your name and the date. The most
  * important thing is make sure the users will have clear and definite under-
  * standing through your new brief.
  ******************************************************************************
*/
#include "mod_Clamp_Arm.h"
#include "system_os.h"

Clamp_Arm_Control_t clamp_arm_control = {0};

static void Clamp_Arm_Mode_Set(Clamp_Arm_Control_t *clamp_arm);
static void Clamp_Arm_Mode_Update(Clamp_Arm_Control_t *clamp_arm);	
static void Clamp_Arm_Control_Input(Clamp_Arm_Control_t *clamp_arm);

/*========================================================API����========================================================*/
/** 
	* @brief ��צʰȡ�ṹ��ʼ������
 **/
void Clamp_Arm_Init(Clamp_Arm_Control_t *clamp_arm_init)
{
	clamp_arm_init->clamp_arm_rc_ctrl = get_dr16_control_point();		//dr16ң������ʼ��
	Clamp_Arm_action(A0,clamp_arm_init);								//ʰȡ���׸�λ
}
/** 
	* @brief ��צʰȡ���ƺ���
 **/
void Clamp_Arm_Loop(Clamp_Arm_Control_t *clamp_arm_loop)
{
	Clamp_Arm_Mode_Set(clamp_arm_loop);
	Clamp_Arm_Mode_Update(clamp_arm_loop);
	Clamp_Arm_Control_Input(clamp_arm_loop);
}
/*========================================================���ܺ���========================================================*/
int arm_limit(int value, int min, int max)
{
	if(value<min)
		value = min;
	if(value>max)
		value = max;
	return value;
}
/** 
	* @brief 	��е��ʰȡ����
	* @param	mode	��������
 **/
void Clamp_Arm_action(uint8_t mode, Clamp_Arm_Control_t *clamp_arm)
{
	switch(mode)
  {
		/*��צʰȡ�ṹ��ʼ��*/
  	case A0:
		{
			cyl_A(0);
			cyl_B(0);
			cyl_C(0);
			cyl_D(0);
		}
  	break;
		/*����1�����λ�е���½�*/
		case A1:
		{
			cyl_B(1);
		}
  	break;
		/*����2���ڳ��ſ�*/
		case A2:
		{
			cyl_C(1);
		}
  	break;
		/*����3�����λ�е�����������ŵ�����*/
		case A3:
		{
			cyl_A(1);
			cyl_B(0);
		}
  	break;
		/*����4������������ת*/
		case A4:
		{
			cyl_D(1);
		}
  	break;
		/*����5�����λ�е���½�*/
		case A5:
		{
			cyl_B(1);
		}
  	break;
		/*����6���ڳ�����*/
		case A6:
		{
			cyl_C(0);
		}
  	break;
		/*����7�����λ�е�ۻ���*/
		case A7:
		{
			cyl_B(0);
		}
  	break;
		/*����8: �������׹�λ*/
		case A8:
		{
			cyl_D(0);
		}
  	break;
  	default:
  		break;
  }
	clamp_arm->clamp_arm_sta = mode;
}
/** 
	* @brief 	��е�۶�����λ
 **/
void Clamp_Arm_rest(Clamp_Arm_Control_t *clamp_arm)
{
		switch (clamp_arm->clamp_arm_sta)
		{
			case A0:
			break;
			case A1:
			{
				cyl_B(0);
			}
			break;
			case A2:
			{
				cyl_C(0);
				vTaskDelay(ARM_TIME);
				cyl_B(0);
			}
			break;
			case A3:
			{
				cyl_A(0);
				vTaskDelay(ARM_TIME);
				cyl_C(0);
			}
			break;
			case A4:
			{
				cyl_D(0);
				vTaskDelay(ROTATE_TIME);
				cyl_A(0);
				vTaskDelay(ARM_TIME);
				cyl_C(0);
			}
			break;
			case A5:
			{
				cyl_B(0);
				vTaskDelay(ARM_TIME);
				cyl_D(0);
				vTaskDelay(ROTATE_TIME);
				cyl_A(0);
				vTaskDelay(ARM_TIME);
				cyl_C(0);
			}
			break;
			case A6:
			{
				cyl_B(0);
				vTaskDelay(ARM_TIME);
				cyl_D(0);
				vTaskDelay(ROTATE_TIME);
				cyl_A(0);
			}
			break;
			case A7:
			{
				cyl_D(0);
				vTaskDelay(ROTATE_TIME);
				cyl_A(0);
			}
			case A8:
			{
				cyl_A(0);
			}
			default:
				break;
		}
		Clamp_Arm_action(A0,clamp_arm);
}
/*========================================================������========================================================*/
/** 
	* @brief ��צʰȡģʽ����
 **/
static void Clamp_Arm_Mode_Set(Clamp_Arm_Control_t *clamp_arm)
{
	if(switch_is_down(clamp_arm->clamp_arm_rc_ctrl->rc.s[ModeChannel_L]))					//����
	{
		if(switch_is_mid(clamp_arm->clamp_arm_rc_ctrl->rc.s[ModeChannel_R]))			//����	ʰȡ׼��
		{
			clamp_arm->clamp_arm_mode = CLAMP_ARM_READY;
		}
		else if(switch_is_up(clamp_arm->clamp_arm_rc_ctrl->rc.s[ModeChannel_R]))	//����	ʰȡ����
		{
			clamp_arm->clamp_arm_mode = CLAMP_ARM_START;
		}
		
		if(clamp_arm->clamp_arm_rc_ctrl->rc.ch[4] < -100)				//�����ϲ���ʰȡ��λ
		{
			clamp_arm->clamp_arm_mode = CLAMP_ARM_OFF;
		}
		
	}
	else 
		clamp_arm->clamp_arm_mode = CLAMP_ARM_STOP;
}

/** 
	* @brief ��צʰȡģʽ����
 **/
static void Clamp_Arm_Mode_Update(Clamp_Arm_Control_t *clamp_arm)
{
	/*ʰȡģʽ�ı�*/
	if(clamp_arm->clamp_arm_mode_last != clamp_arm->clamp_arm_mode)
	{
		/*CLAMP_ARM_READY(ʰȡ׼��)	-> CLAMP_ARM_START(ʰȡ����)*/
		if(clamp_arm->clamp_arm_mode_last == CLAMP_ARM_READY && clamp_arm->clamp_arm_mode == CLAMP_ARM_START)
		{
				switch (clamp_arm->clamp_arm_sta)
				{
					case A0:
							Clamp_Arm_action(A1,clamp_arm);
					break;
					case A2:
						Clamp_Arm_action(A3,clamp_arm);
					break;
					case A4:
						Clamp_Arm_action(A5,clamp_arm);
					break;
					case A6:
						Clamp_Arm_action(A7,clamp_arm);
					break;
					case A8:
						Clamp_Arm_action(A0,clamp_arm);
					break;
					default:
						Clamp_Arm_action(A0,clamp_arm);
					break;
				}
		}
		/*CLAMP_ARM_START(ʰȡ����)	-> CLAMP_ARM_READY(ʰȡ׼��)*/
		else if(clamp_arm->clamp_arm_mode_last == CLAMP_ARM_START && clamp_arm->clamp_arm_mode == CLAMP_ARM_READY)
		{
				switch (clamp_arm->clamp_arm_sta)
				{
					case A1:
						Clamp_Arm_action(A2,clamp_arm);
					break;
					case A3:
						Clamp_Arm_action(A4,clamp_arm);			
					break;
					case A5:
						Clamp_Arm_action(A6,clamp_arm);
					break;
					case A7:
						Clamp_Arm_action(A8,clamp_arm);
					break;
					default:
						Clamp_Arm_action(A0,clamp_arm);
					break;
				}
		}
		clamp_arm->clamp_arm_mode_last = clamp_arm->clamp_arm_mode;	//����ʰȡģʽ
	}
}

/** 
	* @brief ʰȡ��������
 **/
static void Clamp_Arm_Control_Input(Clamp_Arm_Control_t *clamp_arm)
{
	if(clamp_arm->clamp_arm_mode == CLAMP_ARM_OFF)
	{
		Clamp_Arm_rest(clamp_arm);
	}
	
}

