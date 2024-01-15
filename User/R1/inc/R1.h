#ifndef _R1_H
#define _R1_H

#include "stdlib.h"
#include "FreeRTOS.h"
#include "stm32f4xx.h"
#include "task.h"
#include "FreeRTOSConfig.h"
//#include "motor_feedback.h"
#include "drv_dr16.h"
#include "arm_math.h"
#include "drv_motor.h"
#include "ramp_control.h"
#include "stdio.h"
#include "dead_zone.h"
#include "status.h"
#include "Low_pass.h"
#include "stdio.h"


/**************************合夹*********************************/
#define one_group_one   HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,GPIO_PIN_SET)    //415
#define one_group_three HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15,GPIO_PIN_SET)    //418
#define two_group_three HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,GPIO_PIN_SET)    //414
#define two_group_one   HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_SET)    //413
#define two_group_two   HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,GPIO_PIN_SET)    //412
#define one_group_two   HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,GPIO_PIN_SET)    //412

/**************************松夹*********************************/
#define one_group_one_release   HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13, GPIO_PIN_RESET)    //415
#define one_group_two_release   HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14, GPIO_PIN_RESET)    //412
#define one_group_three_release HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15, GPIO_PIN_RESET)    //418
#define two_group_one_release   HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11, GPIO_PIN_RESET)    //413
#define two_group_two_release   HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10, GPIO_PIN_RESET)    //412
#define two_group_three_release HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12, GPIO_PIN_RESET)    //414

/**************************平台的抬升收缩*********************************/
#define up              HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,GPIO_PIN_SET)     //411
#define down            HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9, GPIO_PIN_RESET)   //411
#define push            HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,GPIO_PIN_SET)     //410
#define pull            HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8, GPIO_PIN_RESET)   //410


typedef struct
{
	MOTOR motor_p[4];
}PICK;

typedef struct
{	
	int max_straight_speed;
	int max_spin_speed;
	
	MOTOR motor[4];
	
}CHASSIS;

typedef struct
{
    PICK pick;
    CHASSIS chassis;

}R1;

typedef struct
{
	uint8_t sta;
	uint8_t step;
	
}CYLINDER;



extern R1 r1;

void chassis_task(void *pvParameters);
void pick_task(void *pvParameters);
void system_init(void);

/*****************************************************************************/


/**************************************  Chassis.c   **************************************/
void chssis_task_start(void);
void chassis_max_speed_set(CHASSIS *_chassis, int _max_straight_speed, int _max_spin_speed);
void chassis_solve(CHASSIS *_chassis,  REMOTE (*remote)(RC_ctrl_t *_rc));
void chassis_address_transform(CHASSIS *_chassis, __packed double *_arr1, __packed double *_arr2, __packed double *_arr3);
void chassis_motor_pid_cal(CHASSIS *_chassis, void (*callback)(MOTOR *_motor, float  target));
void chassis_motor_drive(CHASSIS *_chassis, void (*callback)( int16_t i1,int16_t i2,int16_t i3,int16_t i4));
void chassis_motor_pid_init(CHASSIS *_chassis, void (*callback)(MOTOR *_motor, float _arr[6]));
void chassis_slow_mode(CHASSIS *_chassis, REMOTE (*remote)(RC_ctrl_t *_rc));
void chassis_close(CHASSIS *_chassis);
void chassis_motor_drive_close(CHASSIS *_chassis, void (*callback)( int16_t i1,int16_t i2,int16_t i3,int16_t i4));
/******************************************************************************************/


/**************************************  Pick_up.c   **************************************/
void pick_task_start(void);
void pick_motor_10_pid_init(PICK *_pick, void (*callback1)(MOTOR *_motor, float _arr[6]), void (*callback2)(MOTOR *_motor, float _arr[6]));
void pick_motor_8_pid_init(PICK *_pick, void (*callback1)(MOTOR *_motor, float _arr[6]), void (*callback2)(MOTOR *_motor, float _arr[6]));
void pick_solve(PICK *_pick, REMOTE (*remote)(RC_ctrl_t *_rc) );
void pick_motor_angle_pid_cal(PICK *_pick, void (*callback)(MOTOR *_motor, float  target));
void pick_motor_speed_pid_cal(PICK *_pick, void (*callback)(MOTOR *_motor, float  target));
void pick_motor_drive(PICK *_pick, void (*callback)( int16_t i1,int16_t i2,int16_t i3,int16_t i4));
void Cylinder_control(REMOTE (*remote)(RC_ctrl_t *_rc),CYLINDER *_clinder);
void Cylinder_solve(CYLINDER *_clinder,  REMOTE (*remote)(RC_ctrl_t *_rc));
/******************************************************************************************/

#endif



