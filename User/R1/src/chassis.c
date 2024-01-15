#include "R1.h"
#include "status.h"

static float chassis_pid_param[6]={20.0f, 1.0f, 0.0f, 15000.0f, 500.0f, 500.0f};

void chassis_task(void *pvParameters)
{
	chassis_motor_pid_init(&r1.chassis, pid_speed_init_callback);
	while(1)
	{
		if(status_change_callback(&rc_ctrl)!=Reset_system)
		{
			if(status_change_callback(&rc_ctrl)==Status_chassis)
			{
				
				chassis_slow_mode(&r1.chassis, status_remote_callback);
				chassis_solve(&r1.chassis, status_remote_callback);			
					
			}
		}
		else if(status_change_callback(&rc_ctrl)==Reset_system)
		{
			chassis_motor_drive_close(&r1.chassis,motor_driver_can1);
		}
		    chassis_motor_pid_cal(&r1.chassis, motor_speed_pid_cal_callback);
				chassis_motor_drive(&r1.chassis, motor_driver_can1);
			vTaskDelay(1);
	}
}


void chassis_max_speed_set(CHASSIS *_chassis, int _max_straight_speed, int _max_spin_speed)
{
	_chassis->max_straight_speed =_max_straight_speed;
	_chassis->max_spin_speed = _max_spin_speed;
}

/**
	*@brief 
	*@param 
	*@param	
	*@retval 
**/
void chassis_solve(CHASSIS *_chassis,  REMOTE (*remote)(RC_ctrl_t *_rc))
{
	float32_t _speed_x, _speed_y, _speed_w;	
	float32_t vw;
	float32_t vx_last,vy_last;
	
	_speed_x = rc_ctrl.rc.ch[2]*(float)(_chassis->max_straight_speed)/660.0f;
	_speed_y = rc_ctrl.rc.ch[3]*(float)(_chassis->max_straight_speed)/660.0f;
	_speed_w = rc_ctrl.rc.ch[0]*(float)(_chassis->max_spin_speed)/660.0f;
	
	if(_speed_x!=0)
			vx_last=RAMP_float(_speed_x,vx_last,5.0f);	
	else 
			vx_last=0;
	if(_speed_y!=0)
			vy_last=RAMP_float(_speed_y,vy_last,5.0f);	
	else
			vy_last=0;
	
  vw = _speed_w;
	
	
	_chassis->motor[0].target_rpm = 350.0f*(+vx_last+vy_last)+vw;
	_chassis->motor[1].target_rpm = 350.0f*(+vx_last-vy_last)+vw;
	
	_chassis->motor[2].target_rpm = 350.0f*(-vx_last+vy_last)+vw;
	_chassis->motor[3].target_rpm = 350.0f*(-vx_last-vy_last)+vw;
	
}


void chassis_motor_pid_cal(CHASSIS *_chassis, void (*callback)(MOTOR *_motor, float  target))
{
	
	(*callback)(&_chassis->motor[0], _chassis->motor[0].target_rpm);
	(*callback)(&_chassis->motor[1], _chassis->motor[1].target_rpm);
	(*callback)(&_chassis->motor[2], _chassis->motor[2].target_rpm);
	(*callback)(&_chassis->motor[3], _chassis->motor[3].target_rpm);
	
}

void chassis_motor_drive(CHASSIS *_chassis, void (*callback)( int16_t i1,int16_t i2,int16_t i3,int16_t i4))
{
	(*callback)(	        _chassis->motor[0].pid_param_speed.out, 
								        _chassis->motor[1].pid_param_speed.out, 
								        _chassis->motor[2].pid_param_speed.out, 
								        _chassis->motor[3].pid_param_speed.out );
	
}
void chassis_motor_pid_init(CHASSIS *_chassis, void (*callback)(MOTOR *_motor, float _arr[6]))
{
	for(int i=0; i<4; i++)
	{
		(*callback)(&_chassis->motor[i], chassis_pid_param);
	}
	
}

void chassis_slow_mode(CHASSIS *_chassis, REMOTE (*remote)(RC_ctrl_t *_rc))
{
		chassis_max_speed_set(&r1.chassis, 5000, 2000);
}

void chassis_motor_drive_close(CHASSIS *_chassis, void (*callback)( int16_t i1,int16_t i2,int16_t i3,int16_t i4))
{
	(*callback)( 0 , 0 , 0 , 0 );
}


