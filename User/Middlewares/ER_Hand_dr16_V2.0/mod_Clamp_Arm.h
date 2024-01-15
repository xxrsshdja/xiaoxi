#ifndef _MOD_CLAMP_ARM_H_
#define _MOD_CLAMP_ARM_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "system.h"
#include "drv_dr16.h"

/*���׿�*/
/*���ŵ�*/
#define cyl_A(a)						\
				if(a) DC7(1);				\
				else	DC7(0);				\
/*���λ�е��*/
#define cyl_B(a)						\
				if(a) DC5(1);				\
				else	DC5(0);				\
/*�ڳ�*/
#define cyl_C(a)						\
				if(a) DC4(1);				\
				else	DC4(0);				\
/*��ת*/
#define cyl_D(a)						\
				if(a) DC6(1);				\
				else	DC6(0);				\

#define ARM_TIME		550		//��е��ʰȡ�������ʱ��
#define ROTATE_TIME	800

/*==========ʰȡģʽ==========*/
typedef enum
{
	CLAMP_ARM_ON = 0,
	CLAMP_ARM_READY,  //ʰȡ׼��
	CLAMP_ARM_START,	//ʰȡ����
	CLAMP_ARM_STOP,
	CLAMP_ARM_OFF,
} Clamp_Arm_mode_e;
/*==========��е��״̬==========*/
typedef enum
{
	A0 = 0,	//��ʼ��״̬
	A1,			//���λ�е���½�
	A2,			//�ڳ��ſ�
	A3,			//���λ�е�����������ŵ�����
	A4,			//����������ת
	A5,			//���λ�е���½�
	A6,			//�ڳ�����
	A7,			//���λ�е�ۻ���
	A8,			//�������׹�λ
} Clamp_Arm_sta_e;
/*==========ʰȡ����==========*/
typedef struct
{
	const DR16_ctrl_t *clamp_arm_rc_ctrl;
	uint8_t clamp_arm_sta;			//��е��ʰȡ����״̬��־.
	Clamp_Arm_mode_e	clamp_arm_mode;
	Clamp_Arm_mode_e	clamp_arm_mode_last;
	
} Clamp_Arm_Control_t;

/*API*/
void Clamp_Arm_Init(Clamp_Arm_Control_t *clamp_arm_init);
void Clamp_Arm_Loop(Clamp_Arm_Control_t *clamp_arm_loop);
/*���ܺ���*/
void Clamp_Arm_rest(Clamp_Arm_Control_t *clamp_arm);
void Clamp_Arm_action(uint8_t mode, Clamp_Arm_Control_t *clamp_arm);
/*Handle*/
extern Clamp_Arm_Control_t clamp_arm_control;

#ifdef __cplusplus
}
#endif
#endif

