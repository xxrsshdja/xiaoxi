#ifndef _DEAD_ZONE_H
#define _DEAD_ZONE_H

#include "drv_dr16.h"
#include "status.h"

typedef struct
{
    int16_t ch[5];
    char s[2];
}DEAD_ZONE;

double dead_zone_change(double _input, char _set);
DEAD_ZONE dead_zone_output(RC_ctrl_t *_rc, REMOTE (*callback)(RC_ctrl_t *_rc));


#endif

