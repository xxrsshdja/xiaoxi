#include "bsp_spi.h"

/**
  * @brief  SPI��д(8byte)
  * @param  Ҫ���͵��ֽ�
  * @retval ��ȡ�����ֽ�
  */
uint8_t SPI_ReadWrite_8Byte(SPI_TypeDef* SPIx, uint8_t TxData)
{
	uint32_t timeout_cnt_num = 1000;
	uint32_t timeout_cnt = 0;
	while(!LL_SPI_IsActiveFlag_TXE(SPIx)){
		timeout_cnt ++;
		if(timeout_cnt > timeout_cnt_num){
			break;
		}
	}

	SPIx->DR = TxData;

	timeout_cnt = 0;
	while(!LL_SPI_IsActiveFlag_RXNE(SPIx)){
		timeout_cnt ++;
		if(timeout_cnt > timeout_cnt_num){
			break;
		}
	}
	return SPIx->DR;

}

/**
  * @brief  SPI��д(8byte)
  * @param  Ҫ���͵��ֽ�
  * @retval ��ȡ�����ֽ�
  */
uint16_t SPI_ReadWrite_16Byte(SPI_TypeDef* SPIx, uint16_t TxData)
{
	uint32_t timeout_cnt_num = 1000;
	uint32_t timeout_cnt = 0;
	while(!LL_SPI_IsActiveFlag_TXE(SPIx)){
		timeout_cnt ++;
		if(timeout_cnt > timeout_cnt_num){
			break;
		}
	}
	SPIx->DR = (uint16_t)TxData;

	timeout_cnt = 0;
	while(!LL_SPI_IsActiveFlag_RXNE(SPIx)){
		timeout_cnt ++;
		if(timeout_cnt > timeout_cnt_num){
			break;
		}
	}
	return LL_SPI_ReceiveData16(SPIx);;

}
