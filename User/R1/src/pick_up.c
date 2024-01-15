#include "R1.h"

static float pick_speed_pid_param[6]={1.2f, 0.0f, 1.0f, 7000.0f, 500.0f, 500.0f};
static float pick_angle_pid_param[6]={1.2f, 0.0f, 0.0f, 7000.0f, 500.0f, 500.0f};
CYLINDER cylinder = {1,0};

void pick_task(void *pvParameters)
{
		
	pick_motor_10_pid_init(&r1.pick,pid_speed_init_callback, pid_angle_init_callback);
	pick_motor_8_pid_init(&r1.pick,pid_speed_init_callback, pid_angle_init_callback);
while(1)
{
	if(status_change_callback(&rc_ctrl)!=Reset_system)
		{
			if(status_change_callback(&rc_ctrl)==Status_pick)
			{
				
			  pick_solve(&r1.pick,status_remote_callback);
				Cylinder_control(status_remote_callback,&cylinder);
				Cylinder_solve(&cylinder,status_remote_callback);

			}	
		}	
		pick_motor_drive(&r1.pick, motor_driver_can2);
		pick_motor_angle_pid_cal(&r1.pick, motor_angle_pid_cal_callback);
	
		vTaskDelay(1);
		
}

}


void pick_solve(PICK *_pick,  REMOTE (*remote)(RC_ctrl_t *_rc) )
{			

			//motor2	
			_pick->motor_p[1].target_rpm=-700;                                       
			//_pick->motor_p[0].target_rpm=_pick->motor_p[1].target_rpm;
			_pick->motor_p[1].target_angle-=rc_ctrl.rc.ch[4]*0.1f;
			//motor3																																		//motor 0 motor 1为3510    motor 2可以为3508
			_pick->motor_p[2].target_rpm=-700;
			//_pick->motor_p[0].target_rpm=_pick->motor_p[2].target_rpm;
			_pick->motor_p[2].target_angle-=rc_ctrl.rc.ch[4]*0.1f;

			_pick->motor_p[3].target_rpm=300;                                           //平台横移具体角度需要再测量
			_pick->motor_p[3].target_angle=rc_ctrl.rc.ch[0]*0.1f;

} 


void Cylinder_solve(CYLINDER *_clinder,  REMOTE (*remote)(RC_ctrl_t *_rc))
{
	switch(_clinder->step)
	{
		
		case 1://前伸
		{
		
			push;
		
			break;
			
		}
		case 2://夹取
		{
			if(_clinder->sta==1) {one_group_one;two_group_one;}
			if(_clinder->sta==2) {one_group_two;two_group_two;}
			if(_clinder->sta==3) {one_group_three;two_group_three;}		
			
			break;
		}
		case 3://抬升
		{
			
			up;
		
			break;
			
		}
		case 4://下降
		{
			
			down;
			
			break;
			
		}
		case 5://收回
		{
			
			pull;
			_clinder->step=0;
			if(_clinder->sta!=3){_clinder->sta++;}
			break;
			
		}
		case 6://前伸
		{
			
			push;
			
			break;
			
		}

		case 7:
		{
			if(_clinder->sta==1){one_group_one_release;two_group_one_release;}
			if(_clinder->sta==2){two_group_two_release;one_group_two_release;}
			if(_clinder->sta==3){one_group_three_release;two_group_three_release;}
			if(_clinder->sta>0) {_clinder->sta--;}
			_clinder->step=0;
	 	  break;
		}
	}
	
}


void Cylinder_control(REMOTE (*remote)(RC_ctrl_t *_rc),CYLINDER *_clinder)
{
	if(_clinder->step==0)
	{
		
		if((*remote)(&rc_ctrl).ch[1]>=400&&(*remote)(&rc_ctrl).ch[0]==0)
		{
			
			_clinder->step=1;
			
		}
		
		if((*remote)(&rc_ctrl).ch[1]<=-400&&(*remote)(&rc_ctrl).ch[0]==0)
		{
			
			_clinder->step=6;
			
		}
	
	}
}


uint8_t timer=0;

void TIM3_IRQHandler(void)
{

//	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)                //溢出中断
//	{
//		if(cylinder.step!=0&&cylinder.step<5){
//			timer++;
//		if (timer == 15) {
//            cylinder.step++;        
//            timer = 0;                                        // 重置timer为0
//        
//		}
//	}
//		if(cylinder.step==6)
//		{
//			timer++;
//		if (timer == 15) {
//            cylinder.step++;
//            timer = 0;														  					// 重置timer为0
//        }
//	}
//		
//	}
//	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  								//清除中断标志位
}



void pick_motor_10_pid_init(PICK *_pick, void (*callback1)(MOTOR *_motor, float _arr[6]), void (*callback2)(MOTOR *_motor, float _arr[6]))
{
	
		(*callback1)(&_pick->motor_p[0], pick_speed_pid_param);
		(*callback2)(&_pick->motor_p[0], pick_angle_pid_param);
	
		(*callback1)(&_pick->motor_p[1], pick_speed_pid_param);
		(*callback2)(&_pick->motor_p[1], pick_angle_pid_param);
	
		(*callback1)(&_pick->motor_p[3], pick_speed_pid_param);
		(*callback2)(&_pick->motor_p[3], pick_angle_pid_param);
	

}
void pick_motor_8_pid_init(PICK *_pick, void (*callback1)(MOTOR *_motor, float _arr[6]), void (*callback2)(MOTOR *_motor, float _arr[6]))
{

		(*callback1)(&_pick->motor_p[2], pick_speed_pid_param);
		(*callback2)(&_pick->motor_p[2], pick_angle_pid_param);


}
void pick_motor_angle_pid_cal(PICK *_pick, void (*callback)(MOTOR *_motor, float  target))
{
	
	(*callback)(&_pick->motor_p[0], _pick->motor_p[0].target_angle);
	(*callback)(&_pick->motor_p[1], _pick->motor_p[1].target_angle);
	(*callback)(&_pick->motor_p[2], _pick->motor_p[2].target_angle);
	(*callback)(&_pick->motor_p[3], _pick->motor_p[3].target_angle);
	
}

void pick_motor_drive(PICK *_pick, void (*callback)( int16_t i1,int16_t i2,int16_t i3,int16_t i4))
{
	 
	(*callback)(   _pick->motor_p[3].pid_param_speed.out, 
								        _pick->motor_p[1].pid_param_speed.out, 
								        _pick->motor_p[2].pid_param_speed.out,
	                      0
	                       );								 
}


