#include "drv_bluetooth.h"
#include "bsp_usart.h"

static BT_rx_Union_t	BT_rx_union = {0};
/**
  * @brief          ͨ��ָ���ȡ������������
  * @retval         none
  */
const BT_rx_Pack_t *get_BT_point(void)
{
    return &BT_rx_union.rxpack;
}

/**
  * @brief          ����Э�����
  * @param[in]      buf: ԭ������ָ��
  * @retval         none
  */
void BT_DatePrcess(volatile const uint8_t * buf)
{
	//���ݽ��
	BT_rx_union.PcDataArray[0] = buf[0];
	BT_rx_union.PcDataArray[1] = buf[1];
	BT_rx_union.PcDataArray[2] = buf[2];
	BT_rx_union.PcDataArray[3] = buf[3];
	BT_rx_union.PcDataArray[4] = buf[4];
}
/**
	* @brief          ��������(Э��ģʽ)
	* @param[in]      miniPC_tx���������ݹ�����
  * @retval         none
  */
void BT_DateSend(BT_tx_Union_t *BT_tx)
{
	BT_tx->txpack.head = 0xA5;		//֡ͷ
	BT_tx->txpack.end	 = 0x5A;		//֡β
	
//	Usart2_Transmit(BT_tx->txpack.head);
//	Usart2_Transmit(BT_tx->txpack.pwm_value[0]);
//	Usart2_Transmit(BT_tx->txpack.pwm_value[1]);
//	Usart2_Transmit(BT_tx->txpack.check);
//	Usart2_Transmit(BT_tx->txpack.end);
	
	Usart2_DMA_Transmit((uint32_t)&BT_tx->PcDataArray, sizeof(BT_tx_Pack_t));
}

