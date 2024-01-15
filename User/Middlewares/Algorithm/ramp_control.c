#include "ramp_control.h"
#include "math.h"

/**
  * @brief  б�º���,ʹĿ�����ֵ������������ֵ
  * @param  �����������,��ǰ���,�仯�ٶ�(Խ��Խ��)
  * @retval ��ǰ���
  * @attention  
  */
int32_t RAMP_int32_t( int32_t final, int32_t now, int32_t ramp )
{
	  int32_t buffer = final - now;
	if(buffer>0)
	{
		if(buffer > ramp)
		{
			now += ramp;
		}
		else
		{
			now = final;
		}
	}
	else if(buffer<0)
	{
		if(buffer < -ramp)
		{
			now += -ramp;
		}
		else
		{
			now = final;
		}
	}
		
		return now;
}

/**
  * @brief  б�º���,ʹĿ�����ֵ������������ֵ
  * @param  �����������,��ǰ���,�仯�ٶ�(Խ��Խ��)
  * @retval ��ǰ���
  * @attention  
  */
uint16_t RAMP_uint16( uint16_t final, uint16_t now, uint16_t ramp )
{
	  float buffer = 0;
	  buffer = final - now;
	
		if (buffer > 0)
		{
				if (buffer > ramp)
				{  
						now += ramp;
				}   
				else
				{
						now += buffer;
				}
		}
		else if(buffer <= 0)
		{
				if (buffer < -ramp)
				{
						now += -ramp;
				}
				else
				{
						now += buffer;
				}
		}
		return now;
}
/**
  * @brief  б�º���,ʹĿ�����ֵ������������ֵ
  * @param  �����������,��ǰ���,�仯�ٶ�(Խ��Խ��)
  * @retval ��ǰ���
  * @attention  
  */
float RAMP_float( float final, float now, float ramp )
{
	  float buffer = 0;
	  buffer = final - now;
		if (buffer > 0)
		{
				if (buffer > ramp)
				{  
						now += ramp;
				}   
				else
				{
						now += buffer;
				}
		}
		else if(buffer <= 0)
		{
				if (buffer < -ramp)
				{
						now += -ramp;
				}
				else
				{
						now += buffer;
				}
		}
		return now;
}

/**
  * @brief  б�º���,ʹĿ�����ֵ��������ָ������ֵ
  * @param  Ҫ�ڵ�ǰ��������ۼӵ�ֵ,Ŀ�������,��������
  * @retval Ŀ�������
  * @attention  
  *             
*/
float RampInc_float( float *buffer, float now, float ramp )
{

		if (*buffer > 0)
		{
				if (*buffer > ramp)
				{  
						now     += ramp;
					  *buffer -= ramp;
				}   
				else
				{
						now     += *buffer;
					  *buffer  = 0;
				}
		}
		else
		{
				if (*buffer < -ramp)
				{
						now     += -ramp;
					  *buffer -= -ramp;
				}
				else
				{
						now     += *buffer;
					  *buffer  = 0;
				}
		}
		return now;
}

float RampCalc(RampGen_t *ramp)
{
	ramp -> count++;
	if(ramp -> count > ramp -> XSCALE) 
		ramp -> count = ramp -> XSCALE;
	ramp -> out = (1.0f * (ramp -> count) / ramp -> XSCALE);
	return ramp->out;
}
void RampSetScale(struct RampGen_t *ramp, int32_t scale)
{
	ramp ->XSCALE = scale;
}
void RampResetCounter(struct RampGen_t *ramp)
{
	ramp ->count = 0;
}

void RampInit(RampGen_t *ramp, int32_t XSCALE)
{
	ramp -> count = 0;
	ramp ->XSCALE = XSCALE;
}
	
void RampSetCounter(struct RampGen_t *ramp, int32_t count)
{
	ramp -> count = count;
}
		
uint8_t RampIsOverflow(struct RampGen_t *ramp)
{
	if(ramp -> count >= ramp -> XSCALE) return 1;
	else 																return 0;
}


//����ʱ���-1��+1��ѭ�����
float RampCalcLoop(RampGenLoop_t *ramp)
{
	if(ramp->flag < 1)
	{
		ramp->count++;
	}
	else if(ramp->flag >-1)
	{
		ramp->count--;
	}
	
	if(ramp->count >= ramp->XSCALE)
	{
		ramp->count = ramp->XSCALE;
		ramp->flag = 1;
	}		
	else if(ramp->count <= -ramp->XSCALE)
	{
		ramp->count = -ramp->XSCALE;
		ramp->flag = -1;
	}		
	
	ramp->out = (1.0f * (ramp->count) / ramp->XSCALE);
	return ramp->out; 
}
void RampSetScaleLoop(struct RampGenLoop_t *ramp, int32_t scale)
{
	ramp->XSCALE = scale;
}
void RampResetCounterLoop(struct RampGenLoop_t *ramp)
{
	ramp->count = 0;
	ramp->flag = 0;
}

void RampInitLoop(RampGenLoop_t *ramp, int32_t XSCALE)
{
	ramp->count = 0;
	ramp->flag = 0;
	ramp->XSCALE = XSCALE;

}
