/**
  ******************************************************************************
  * @file    drv_miniPC.c/h
  * @brief   miniPC�ϲ���������
  * @version 2.0
	@verbatim
	===================================================================      
									##### How to use this driver #####
	=================================================================== 
    @note
      -# ʹ��miniPC_DatePrcess�����������
  
      -# ʹ��get_miniPC_point��ȡ����������

         
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
#include "drv_miniPC.h"
#include "bsp_usart.h"

static miniPC_rx_Union_t	miniPC_rx_union = {0};
/**
  * @brief          ͨ��ָ���ȡ��λ����������
  * @retval         none
  */
const miniPC_rx_Pack_t *get_miniPC_point(void)
{
    return &miniPC_rx_union.rxpack;
}

/**
  * @brief          ��λ��Э�����
  * @param[in]      buf: ԭ������ָ��
  * @retval         none
  */
void miniPC_DatePrcess(volatile const uint8_t * buf)
{
	//���ݽ��
	miniPC_rx_union.PcDataArray[0] = buf[0];
	miniPC_rx_union.PcDataArray[1] = buf[1];
	miniPC_rx_union.PcDataArray[2] = buf[2];
	miniPC_rx_union.PcDataArray[3] = buf[3];
}
/**
	* @brief          ������λ��
	* @param[in]      miniPC_tx���������ݹ�����
  * @retval         none
  */
void miniPC_DateSend(miniPC_tx_Union_t *miniPC_tx)
{
	miniPC_tx->txpack.head = 0x5A;		//֡ͷ
	miniPC_tx->txpack.end  = 0xA5;		//֡β
	
	//JustFloat VofaЭ��
//	miniPC_tx->txpack.tail[0] = 0x00;
//	miniPC_tx->txpack.tail[1] = 0x00;
//	miniPC_tx->txpack.tail[2] = 0x80;
//	miniPC_tx->txpack.tail[3] = 0x7f;
	
	Usart1_DMA_Transmit((uint32_t)&miniPC_tx->PcDataArray, sizeof(miniPC_tx_Pack_t));
}
