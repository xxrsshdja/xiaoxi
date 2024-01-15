#ifndef _STATUS_H
#define _STATUS_H

#include "drv_dr16.h"

#define ON 1
#define OFF 0

#define mode_0 0
#define mode_1 1
#define mode_2 2
enum
{
	Reset_system=1, 
	Status_pick,
	Status_chassis,
  Status_platform,
	Status_Chassis_and_Pick,
};

typedef struct
{
	int16_t ch[5];
	char s[2];
}REMOTE;

char status_change_callback(RC_ctrl_t *_rc);
char status_mode_change_callback(RC_ctrl_t *_rc);
REMOTE status_remote_callback(RC_ctrl_t *_rc);



#endif

