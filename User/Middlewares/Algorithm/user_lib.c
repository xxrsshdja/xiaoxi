#include "user_lib.h"

/**
  * @brief				��Χӳ��
  * @author				RW
  * @param a			ԭʼ��ֵ
  * @param amin		ԭʼ��Сֵ
  * @param amax		ԭʼ���ֵ
  * @param bmin		ӳ������Сֵ
  * @param bmax		ӳ�������ֵ
  * @retval				ӳ������ֵ
  */
float float_map(float a, float amin, float amax, float bmin, float bmax)
{
	float adel = amax - amin, bdel = bmax - bmin;
	if(a > amax)a = amax;
	if(a < amin)a = amin;
	return (float)(bdel * ((float)(a-amin) / adel))+bmin;
}
int int_map(int a, int amin, int amax, int bmin, int bmax)
{
	int adel = amax - amin, bdel = bmax - bmin;
	if(a > amax)a = amax;
	if(a < amin)a = amin;
	return (bdel * ((float)(a-amin) / adel))+bmin;
}

//��������
float float_deadline(float Value, float minValue, float maxValue)
{
    if (Value < maxValue && Value > minValue)
    {
        Value = 0.0f;
    }

    return Value;
}

//int16����
int16_t int16_deadline(int16_t Value, int16_t minValue, int16_t maxValue)
{
    if (Value < maxValue && Value > minValue)
    {
        Value = 0;
    }

    return Value;
}

int16_t int16_limit(int16_t raw, int16_t limit_min, int16_t limit_max)
{
	if(raw > limit_max)
		return limit_max;
	else if(raw < limit_min)
		return limit_min;
	else
		return raw;
}

float float_limit(float raw, float limit_min, float limit_max)
{
	if(raw > limit_max)
		return limit_max;
	else if(raw < limit_min)
		return limit_min;
	else
		return raw;
}

//����ӳ��
int int_map_shoot_pwm(int a, int amin, int amax, int value, int MIN, int MAX)
{
	int bmin, bmax, adel, bdel, out;
	adel = amax - amin;
	bmin = value-1000;
	bmax = value+1000;
	bdel = bmax - bmin;
	if(a > amax)a = amax;
	if(a < amin)a = amin;
	out = (bdel * ((float)(a-amin) / adel))+bmin;
	if(out<MIN) out = MIN;
	if(out>MAX)	out = MAX;
	return out;
	
}


//int16����
int16_t int16_buffer(int16_t Value, int16_t buffer)
{
  if(Value > 0) 
	{
		Value -= buffer;
		if(Value < 0) Value=0;
	}
	else if(Value < 0)
	{
		Value += buffer;
		if(Value > 0) Value=0;
	}
	return Value;
}

int user_abs(int value)
{
	if(value >= 0)
		return value;
	else
		return -value;
}
