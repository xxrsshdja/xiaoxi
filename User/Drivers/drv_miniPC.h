#ifndef __DRV_MINIPC_H
#define __DRV_MINIPC_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <stddef.h>

#define MINIPC_FRAME_LENGTH	12u
#define MINIPC_HEAD							0x55
#define MINIPC_TAIL							0xAA
/*miniPC�������ݰ�*/
typedef __packed struct
{
	uint8_t head;
	float pitch[4];
	float yaw[4];
	float distance;
	uint8_t shoot_flag;
	uint8_t end;
} miniPC_rx_Pack_t;
/*miniPC�������ݰ�*/
typedef __packed struct
{
	char 	head;							//1byte		֡ͷ0x5A
	char 	Speed1[2];				//2byte		�����ٶ�1
	char 	Speed2[2];				//2byte		�����ٶ�2
	float	Yaw;							//4byte		������ת�Ƕ�
	float	voltage;					//4byte		���ص�ѹ
	char 	end;							//1byte		֡β0xA5
	
//	float data[8];
//	uint8_t	tail[4];
	
} miniPC_tx_Pack_t;
/*������λ��������*/
typedef __packed union
{
	miniPC_tx_Pack_t	txpack;
	unsigned char PcDataArray[sizeof(miniPC_tx_Pack_t)];
} miniPC_tx_Union_t;
/*������λ��������*/
typedef __packed union
{
	miniPC_rx_Pack_t	rxpack;
	unsigned char PcDataArray[sizeof(miniPC_rx_Pack_t)];
} miniPC_rx_Union_t;

void miniPC_DatePrcess(volatile const uint8_t * buf);
void miniPC_DateSend(miniPC_tx_Union_t *miniPC_tx);
extern const miniPC_rx_Pack_t *get_miniPC_point(void);

#ifdef __cplusplus
}
#endif
#endif
