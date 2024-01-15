/**
  ******************************************************************************
  * @file    drv_dr16.c/h
  * @brief   dr16接收机上层驱动代码
  * @version 2.0
	@verbatim
	===================================================================      
									##### How to use this driver #####
	=================================================================== 
    @note
      -# 使用dr16_DatePrcess解包接收数据
  
      -# 使用get_remote_control_point获取解包后的数据

         
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
#include "drv_dr16.h"

RC_ctrl_t rc_ctrl ;
//static RC_ctrl_t rc_ctrl = {0};

/**
  * @brief          通过指针获取遥控器数据
  * @retval         none
  */
const RC_ctrl_t *get_remote_control_point(void)
{
    return &rc_ctrl;
}
//dr16取正函数
static signed short int RC_abs(signed short int value)
{
    if (value > 0)
    {
        return value;
    }
    else
    {
        return -value;
    }
}

/**
  * @brief          dr16遥控器协议解析
  * @param[in]      sbus_buf: 原生数据指针
  * @retval         none
  */
void dr16_DatePrcess(volatile const uint8_t * sbus_buf)
{
    if (sbus_buf == NULL)
    {
        return;
    }
		
    rc_ctrl.rc.ch[0] = (sbus_buf[0] | (sbus_buf[1] << 8)) & 0x07ff;        //!< Channel 0
    rc_ctrl.rc.ch[1] = ((sbus_buf[1] >> 3) | (sbus_buf[2] << 5)) & 0x07ff; //!< Channel 1
    rc_ctrl.rc.ch[2] = ((sbus_buf[2] >> 6) | (sbus_buf[3] << 2) | (sbus_buf[4] << 10)) & 0x07ff;        //!< Channel 2
    rc_ctrl.rc.ch[3] = ((sbus_buf[4] >> 1) | (sbus_buf[5] << 7)) & 0x07ff; //!< Channel 3
    rc_ctrl.rc.s[0] = ((sbus_buf[5] >> 4) & 0x0003);                  //!< Switch left
    rc_ctrl.rc.s[1] = ((sbus_buf[5] >> 4) & 0x000C) >> 2;                       //!< Switch right
    rc_ctrl.rc.ch[4] = sbus_buf[16] | (sbus_buf[17] << 8);                 //NULL

    rc_ctrl.rc.ch[0] -= RC_CH_VALUE_OFFSET;
    rc_ctrl.rc.ch[1] -= RC_CH_VALUE_OFFSET;
    rc_ctrl.rc.ch[2] -= RC_CH_VALUE_OFFSET;
    rc_ctrl.rc.ch[3] -= RC_CH_VALUE_OFFSET;
    rc_ctrl.rc.ch[4] -= RC_CH_VALUE_OFFSET;
		
    if(rc_ctrl.rc.ch[1] <= 5 && rc_ctrl.rc.ch[1] >= -5)
        rc_ctrl.rc.ch[1] = 0;
    if(rc_ctrl.rc.ch[2] <= 5 && rc_ctrl.rc.ch[2] >= -5)
        rc_ctrl.rc.ch[2] = 0;
    if(rc_ctrl.rc.ch[3] <= 5 && rc_ctrl.rc.ch[3] >= -5)
        rc_ctrl.rc.ch[3] = 0;
    if(rc_ctrl.rc.ch[4] <= 5 && rc_ctrl.rc.ch[4] >= -5)
        rc_ctrl.rc.ch[4] = 0;
    
		if(rc_ctrl.rc.ch[3] == -660)		//防止油门打死
			rc_ctrl.rc.ch[3] = 0;
		
    if((RC_abs(rc_ctrl.rc.ch[1]) > 660) || \
      (RC_abs(rc_ctrl.rc.ch[2]) > 660) || \
      (RC_abs(rc_ctrl.rc.ch[3]) > 660) || \
      (RC_abs(rc_ctrl.rc.ch[4]) > 660))
        {
        rc_ctrl.rc.ch[1] = 0;	rc_ctrl.rc.ch[2] = 0;
        rc_ctrl.rc.ch[3] = 0;	rc_ctrl.rc.ch[4] = 0;
        }

}

