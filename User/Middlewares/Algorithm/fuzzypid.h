#ifndef __FUZZYPID_H
#define __FUZZYPID_H
#include <stdint.h>
#include <stddef.h> 

#define NB  -3
#define NM  -2
#define NS  -1
#define ZO  0
#define PS  1
#define PM  2
#define PB  3

typedef struct
{
	float  e_grad_mem[2];      //����e��������
   float  ec_grad_mem[2];     //����de/dt��������
	char   e_grad_index[2];    //����e�������ڹ���������
   char   ec_grad_index[2];   //����de/dt�������ڹ���������
   float  KpgradSums[7];      //�������kp�ܵ�������
   float  KigradSums[7];      //�������ki�ܵ�������
   float  KdgradSums[7];      //�������kd�ܵ�������
   float  qdetail_kp;         //����kp��Ӧ�����е�ֵ
   float  qdetail_ki;         //����ki��Ӧ�����е�ֵ
   float  qdetail_kd;         //����kd��Ӧ�����е�ֵ
   float  qerro;              //����e��Ӧ�����е�ֵ
   float  qerro_c;            //����de/dt��Ӧ�����е�ֵ
   float errosum;             //������  

   float detail_kp;                //�������kp
   float detail_ki;                //�������ki
   float detail_kd;                //�������kd

   float kp;                       //PID����kp
   float ki;                       //PID����ki
   float kd;                       //PID����kd
   float out;                      //PID���
}FuzyPID_TypeDef;


void FuzyPidTable(float ERR, float ERRC, FuzyPID_TypeDef *pid);
void PIDPos_Set(float pid_p,float pid_i,float pid_d,FuzyPID_TypeDef *fpid);
void PIDAngle_Set(float pid_p,float pid_i,float pid_d,FuzyPID_TypeDef *fpid);
void PIDActvel_Set(float pid_p,float pid_i,float pid_d,FuzyPID_TypeDef *fpid);
void FuzzyPIDcontroller(FuzyPID_TypeDef* fpid, float e_max, float e_min, float ec_max, float ec_min, float kp_max, float kp_min, 
												 float erro, float erro_c,float ki_max,float ki_min,float kd_max,float kd_min,float erro_pre,float errp_ppre);

#endif
    

