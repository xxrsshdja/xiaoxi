#include "bsp_can.h"

static void (*pCAN1_RxCpltCallback)(CAN_RxBuffer *);
static void (*pCAN2_RxCpltCallback)(CAN_RxBuffer *);

/**
* @brief  CAN��ʼ��
* @param  hcan: CANx created by CubeMX.
* @return None.
*/
uint8_t bsp_can_Init(CAN_HandleTypeDef* hcan, void (*pFunc)(CAN_RxBuffer*))
{
	assert_param(hcan != NULL);
	
  HAL_CAN_Start(hcan);
	__HAL_CAN_DISABLE_IT(hcan, CAN_IT_ERROR);
  __HAL_CAN_ENABLE_IT(hcan,CAN_IT_RX_FIFO0_MSG_PENDING);
  __HAL_CAN_ENABLE_IT(hcan,CAN_IT_RX_FIFO1_MSG_PENDING);
  
	if(hcan->Instance == CAN1)
	{
		pCAN1_RxCpltCallback = pFunc;
		return SUCCESS;
	}
	else if(hcan->Instance == CAN2)
	{
		pCAN2_RxCpltCallback = pFunc;
		return SUCCESS;
	}
	else
		return ERROR;
}


/**
 * @brief ����CAN�Ĺ�����
 * @param object_para [|���|FIFOx|ID����|֡����|ID|]
 * @param Id          [ID]
 * @param MaskId      [����λ(0x3ff,0x1FFFFFFF)]
 * @brief             [ɸѡ��:|���|FIFOx|ID����|֡����|ID|����λ(0x3ff,0x1FFFFFFF)|] \n
 *
 */
void CAN_Filter_Mask_Config(CAN_HandleTypeDef * hcan, uint8_t object_para,uint32_t Id,uint32_t MaskId)
{
	CAN_FilterTypeDef  CAN_FilterInitStructure;

	assert_param(hcan != NULL);

	if( (object_para&0x02))	//ɸѡ��ID>=10
	{
    CAN_FilterInitStructure.FilterIdHigh         = Id<<3<<16;                       /* �����ID�ĸ�16bit */
    CAN_FilterInitStructure.FilterIdLow          = Id<<3| ((object_para&0x03)<<1);  /* �����ID�ĵ�16bit */
    CAN_FilterInitStructure.FilterMaskIdHigh     = MaskId<<3<<16;                   /* ID����ֵ��16bit */
    CAN_FilterInitStructure.FilterMaskIdLow      = MaskId<<3| ((object_para&0x03)<<1);;   /* ID����ֵ��16bit */
	}
	else
	{
    CAN_FilterInitStructure.FilterIdHigh         = Id<<5;                           /* �����ID�ĸ�16bit */
    CAN_FilterInitStructure.FilterIdLow          = ((object_para&0x03)<<1);         /* �����ID�ĵ�16bit */
    CAN_FilterInitStructure.FilterMaskIdHigh     = MaskId<<5;                       /* ID����ֵ��16bit */
    CAN_FilterInitStructure.FilterMaskIdLow      = ((object_para&0x03)<<1);;        /* ID����ֵ��16bit */
	}
    CAN_FilterInitStructure.FilterBank           = object_para>>3;                  /* �˲�����ţ�0-13����14���˲��� */
    CAN_FilterInitStructure.FilterFIFOAssignment = (object_para>>2)&0x01;           /* �˲�����FIFO 0 */
    CAN_FilterInitStructure.FilterActivation     = ENABLE;                          /* ʹ���˲��� */
    CAN_FilterInitStructure.FilterMode         = CAN_FILTERMODE_IDMASK;             /* �˲���ģʽ������ID����ģʽ */
    CAN_FilterInitStructure.FilterScale        = CAN_FILTERSCALE_32BIT;             /* 32λ�˲� */
    CAN_FilterInitStructure.SlaveStartFilterBank = 14;                              /* Select the start bank filter for slave CAN*/
    HAL_CAN_ConfigFilter(hcan, &CAN_FilterInitStructure);
}


/**
* @brief  CAn���ͱ�׼֡
* @param  hcan  :CAN bus used to send.
* @param  ID    :ID of frame.
* @param  *pData:Data to send.
* @param  Len   :Length of data.
* @return CAN_SUCCESS:  Operation success.
* @return CAN_LINE_BUSY:CAN line busy.
*/
uint8_t CANx_SendData(CAN_HandleTypeDef* hcan,uint16_t ID,uint8_t *pData,uint16_t Len)
{
	static CAN_TxHeaderTypeDef   Tx_Header;
  uint32_t  used_mailbox;
	/* Check the parameters */
	assert_param(hcan != NULL);
	
	Tx_Header.StdId=ID;
	Tx_Header.ExtId=0;
	Tx_Header.IDE=0;
	Tx_Header.RTR=0;
	Tx_Header.DLC=Len;
	
	if(HAL_CAN_AddTxMessage(hcan,&Tx_Header,pData,&used_mailbox)!= HAL_OK)
	{
			return CAN_LINE_BUSY;
	}
	else{}
		
	return CAN_SUCCESS;
}


/**
* @brief  CAN������չ֡
* @param  hcan  :CAN bus used to send.
* @param  ID    :ID of frame.
* @param  *pData:Data to send.
* @param  Len   :Length of data.
* @return CAN_SUCCESS:  Operation success.
* @return CAN_LINE_BUSY:CAN line busy.
*/
uint8_t CANx_SendExtData(CAN_HandleTypeDef* hcan,uint16_t ID,uint8_t *pData,uint16_t Len)
{
	static CAN_TxHeaderTypeDef   Tx_Header;
  uint32_t  used_mailbox;
	/* Check the parameters */
	assert_param(hcan != NULL);
	
	Tx_Header.RTR=0;
	Tx_Header.DLC=Len;
	Tx_Header.StdId=0;
	Tx_Header.ExtId=ID;
	Tx_Header.IDE=CAN_ID_EXT;

	if(HAL_CAN_AddTxMessage(hcan,&Tx_Header,pData,&used_mailbox)!= HAL_OK)
	{
			return CAN_LINE_BUSY;
	}
	else{}
		
	return CAN_SUCCESS;
}


/*HAL��FIFO0�ж�*/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	/*!< CAN receive buffer */
	static CAN_RxBuffer CAN_RxBuffer;

	if(hcan->Instance ==CAN1)
	{
		HAL_CAN_GetRxMessage(hcan,CAN_FILTER_FIFO0,&CAN_RxBuffer.header,CAN_RxBuffer.data);
		pCAN1_RxCpltCallback(&CAN_RxBuffer);
	}
	else if(hcan->Instance == CAN2)
	{
		HAL_CAN_GetRxMessage(hcan,CAN_FILTER_FIFO0,&CAN_RxBuffer.header,CAN_RxBuffer.data);
			pCAN2_RxCpltCallback(&CAN_RxBuffer);
	}
}
/*HAL��FIFO1�ж�*/
void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	static CAN_RxBuffer CAN_RxBuffer;

	if(hcan->Instance ==CAN1)
	{
		HAL_CAN_GetRxMessage(hcan,CAN_FILTER_FIFO1,&CAN_RxBuffer.header,CAN_RxBuffer.data);
		pCAN1_RxCpltCallback(&CAN_RxBuffer);
	}
	else if(hcan->Instance == CAN2)
	{
		HAL_CAN_GetRxMessage(hcan,CAN_FILTER_FIFO1,&CAN_RxBuffer.header,CAN_RxBuffer.data);
		pCAN2_RxCpltCallback(&CAN_RxBuffer);
	}
}
