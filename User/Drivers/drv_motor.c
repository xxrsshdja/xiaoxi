#include "drv_motor.h"
#include "bsp_can.h"
#include "r1.h"


extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

static motor_measure_t  motor_driver[4];


/**
  * @brief          驱动电机信息读取
  * @param		      ID: 标准帧ID
	* @param		      Data: 电机信息
  * @retval         none
  */
void Driver_motor_DatePrcess(uint32_t ID, uint8_t *Data)
{
	switch(ID)
	{
		case chassis_motor_1:
			get_RMmotor_measure(&r1.chassis.motor[0].feedback,Data);
		break;
		case chassis_motor_2:
			get_RMmotor_measure(&r1.chassis.motor[1].feedback,Data);
		break;
		case chassis_motor_3:
			get_RMmotor_measure(&r1.chassis.motor[2].feedback,Data);
		break;
		case chassis_motor_4:
			get_RMmotor_measure(&r1.chassis.motor[3].feedback,Data);
		break;
		default:
			break;
	}
}



/*==========发送驱动电机控制命令函数==========*/
void motor_driver_can1(int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4)
{
		static uint8_t Data[8] = {0};
		Data[0] = iq1 >> 8;
		Data[1] = iq1;
		Data[2] = iq2 >> 8;
		Data[3] = iq2;
		Data[4] = iq3 >> 8;
		Data[5] = iq3;
		Data[6] = iq4 >> 8;
		Data[7] = iq4;
	
		CANx_SendData(&hcan1, chassis_motor, Data, 0x08);
}

void motor_driver_can2(int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4)
{
		static uint8_t Data[8] = {0};
		Data[0] = iq1 >> 8;
		Data[1] = iq1;
		Data[2] = iq2 >> 8;
		Data[3] = iq2;
		Data[4] = iq3 >> 8;
		Data[5] = iq3;
		Data[6] = iq4 >> 8;
		Data[7] = iq4;
	
		CANx_SendData(&hcan2, pick_motor , Data, 0x08);
}

void motor_speed_pid_cal_callback(MOTOR *_motor, float _target)
{
    PID_calc(&_motor->pid_param_speed, _motor->feedback.speed_rpm, _target);
}


void motor_angle_pid_cal_callback(MOTOR *_motor, float _target)
{
    PID_calc(&_motor->pid_param_angle, _motor->feedback.all_ecd, _target);
	  PID_calc(&_motor->pid_param_speed, _motor->feedback.speed_rpm, _motor->pid_param_angle.out);
}


void motor_close_callback(MOTOR *_motor)
{
	PID_calc(&_motor->pid_param_speed, _motor->feedback.speed_rpm, 0);
}


void pid_speed_init_callback(MOTOR *_motor, float _arr[6])
{
	PID_init(&_motor->pid_param_speed, PID_POSITION, _arr[0], _arr[1], _arr[2], _arr[3], _arr[4], _arr[5]);
}

void pid_angle_init_callback(MOTOR *_motor, float _arr[6])
{
	PID_init(&_motor->pid_param_angle, PID_POSITION, _arr[0], _arr[1], _arr[2], _arr[3], _arr[4], _arr[5]);
}


//返回驱动电机变量地址，通过指针方式获取原始数据
const motor_measure_t *get_Driver_Measure_Point(uint8_t i)
{
    return &motor_driver[(i & 0x03)];
}

