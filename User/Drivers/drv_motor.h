#ifndef _DRV_MOTOR_H_
#define _DRV_MOTOR_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "system.h"
#include "pid.h"

/*==========rm电机数据读取==========*/
#define get_RMmotor_measure(ptr, Data)                                        \
{                                                                             \
		if((ptr)->ecd-(ptr)->last_ecd>4096) 																			\
		{(ptr)->round_cnt-- ;}                               											\
		else if((ptr)->ecd-(ptr)->last_ecd<-4096 ) 																\
		{(ptr)->round_cnt ++ ;}											 															\
		(ptr)->last_ecd = (ptr)->ecd;                                             \
		(ptr)->ecd = (uint16_t)(Data[0] << 8 | Data[1]);           								\
		(ptr)->speed_rpm = (uint16_t)(Data[2] << 8 | Data[3]);     								\
		(ptr)->given_current = (uint16_t)(Data[4] << 8 | Data[5]); 								\
		(ptr)->temperate = Data[6];                                              	\
		(ptr)->total_ecd=(ptr)->round_cnt*8191+(ptr)->ecd;                        \
		(ptr)->all_ecd=(ptr)->total_ecd;                                   \
}	


/*              can 1                 */
#define chassis_motor1 0x201
#define chassis_motor2 0x202
#define chassis_motor3 0x203
#define chassis_motor4 0x204

/**************************************/


/*              can 2                 */
#define pick_motor1 0x201
#define pick_motor2 0x202
#define pick_motor3 0x203
#define pick_motor4 0x204

/**************************************/
/*==========电机标准帧ID==========*/
typedef enum
{
	Null_id											= 0x000,
	
	chassis_motor        			= 0x200,
	chassis_motor_1              				= 0x201,
	chassis_motor_2							 				= 0x202,
	chassis_motor_3             				= 0x203,
	chassis_motor_4							 				= 0x204,
	
	pick_motor        			= 0x200,
	pick_motor_1          = 0x201,
	pick_motor_2               = 0x202,
	pick_motor_3              = 0x203,
    pick_motor_4              = 0x204,	
	
} can_msg_id_e;





/*==========RM电机信息==========*/
typedef struct
{
	vu16 	ecd;
	vs16 	last_ecd;
	vs16 	total_ecd;
	vs16 	all_ecd;
	vs16 	speed_rpm;
	vs16 	given_current;
	vu8 	temperate;
	vs32	round_cnt;
} motor_measure_t;

typedef struct
{
	float target_rpm;
	float target_angle;
	
	int initial_ecd;
	PidType pid_param_speed;
	PidType pid_param_angle;
	motor_measure_t feedback;
}MOTOR;


/*==========驱动电机内部信息==========*/
typedef struct
{
	const motor_measure_t *motor_measure;
	int16_t set_current;
	int32_t real_speed;
	int32_t set_motor_speed;
} Driver_Motor_t;

void motor_speed_pid_cal_callback(MOTOR *_motor, float _target);
void motor_angle_pid_cal_callback(MOTOR *_motor, float _target);
void pid_angle_init_callback(MOTOR *_motor,  float _arr[6]);
void pid_speed_init_callback(MOTOR *_motor,  float _arr[6]);
void Driver_motor_DatePrcess(uint32_t ID, uint8_t *Data);
void motor_driver_can1(int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4);
void motor_driver_can2(int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4);
extern const motor_measure_t *get_Driver_Measure_Point(uint8_t i);


#ifdef __cplusplus
}
#endif
#endif

