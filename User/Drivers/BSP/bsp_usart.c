#include "bsp_usart.h"

static usart_manage_obj_t usart_manage_obj[8] = {NULL};

/**
  * @brief  ����4��ʼ��
 **/
void bsp_uart4_Init(uint8_t* rx_buffr0, uint8_t* rx_buffr1, uint16_t len, usart_call_back fun)
{
	usart_manage_obj[4].rx_buffer_size = len;
	usart_manage_obj[4].rx_buffer0 = rx_buffr0;
	usart_manage_obj[4].rx_buffer1 = rx_buffr1;
	usart_manage_obj[4].call_back_f = fun;
	/*DMA����*/
	/*DMA_rx*/
	LL_DMA_SetPeriphAddress(DMA1, LL_DMA_STREAM_2, (uint32_t)(&UART4->DR));		//����DMA����Ŀ���ַ
	LL_DMA_SetMemoryAddress(DMA1, LL_DMA_STREAM_2, (uint32_t)rx_buffr0);		//����DMA�ڴ��ַ0
	LL_DMA_SetMemory1Address(DMA1, LL_DMA_STREAM_2, (uint32_t)rx_buffr1);		//����DMA�ڴ��ַ1
	LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_2, len);														//����DMA����ͨ������
	LL_DMA_EnableDoubleBufferMode(DMA1, LL_DMA_STREAM_2);												//ʹ��DMA˫���洫��
	LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_2);																	//ʧ��DMA
	LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_2);																	//ʹ��DMA
	
	/*��������*/
	LL_USART_EnableDMAReq_RX(UART4);		//��������DMA����
	LL_USART_EnableIT_IDLE(UART4);			//�������ڿ����ж�
	LL_USART_ClearFlag_IDLE(UART4);		//������ڿ����жϱ�־λ
	LL_USART_Enable(UART4);						//��������

}

/**
  * @brief  ����1��ʼ��
 **/
void bsp_usart1_Init(uint8_t* rx_buffr0, uint8_t* rx_buffr1, uint16_t rx_len, usart_call_back fun)
{
	usart_manage_obj[1].rx_buffer_size = rx_len;
	usart_manage_obj[1].rx_buffer0 = rx_buffr0;
	usart_manage_obj[1].rx_buffer1 = rx_buffr1;
	usart_manage_obj[1].call_back_f = fun;
	
	/*DMA����*/
	/*DMA_rx*/
	LL_DMA_SetPeriphAddress(DMA2, LL_DMA_STREAM_2, (uint32_t)(&USART1->DR));
	LL_DMA_SetMemoryAddress(DMA2, LL_DMA_STREAM_2, (uint32_t)rx_buffr0);
	LL_DMA_SetMemory1Address(DMA2, LL_DMA_STREAM_2, (uint32_t)rx_buffr1);
	LL_DMA_SetDataLength(DMA2, LL_DMA_STREAM_2, rx_len);
	LL_DMA_EnableDoubleBufferMode(DMA2, LL_DMA_STREAM_2);
	LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_2);
	LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_2);
	/*DMA_tx*/
	LL_DMA_SetPeriphAddress(DMA2, LL_DMA_STREAM_7, (uint32_t)(&USART1->DR));
	LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_7);
	/*USART����*/
	LL_USART_EnableDMAReq_RX(USART1);
	LL_USART_EnableDMAReq_TX(USART1);
	LL_USART_EnableIT_IDLE(USART1);
	LL_USART_ClearFlag_IDLE(USART1);
	LL_USART_Enable(USART1);
	
}
/**
  * @brief  ����2��ʼ��
 **/
void bsp_usart2_Init(uint8_t* rx_buffr0, uint8_t* rx_buffr1, uint16_t rx_len, usart_call_back fun)
{
	usart_manage_obj[2].rx_buffer_size = rx_len;
	usart_manage_obj[2].rx_buffer0 = rx_buffr0;
	usart_manage_obj[2].rx_buffer1 = rx_buffr1;
	usart_manage_obj[2].call_back_f = fun;
	
	/*DMA����*/
	/*DMA_rx*/
	LL_DMA_SetPeriphAddress(DMA1, LL_DMA_STREAM_5, (uint32_t)(&USART2->DR));
	LL_DMA_SetMemoryAddress(DMA1, LL_DMA_STREAM_5, (uint32_t)rx_buffr0);
	LL_DMA_SetMemory1Address(DMA1, LL_DMA_STREAM_5, (uint32_t)rx_buffr1);
	LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_5, rx_len);
	LL_DMA_EnableDoubleBufferMode(DMA1, LL_DMA_STREAM_5);
	LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_5);
	LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_5);
	/*DMA_tx*/
	LL_DMA_SetPeriphAddress(DMA1, LL_DMA_STREAM_6, (uint32_t)(&USART2->DR));
	LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_6);
	/*USART����*/
	LL_USART_EnableDMAReq_RX(USART2);
	LL_USART_EnableDMAReq_TX(USART2);
	LL_USART_EnableIT_IDLE(USART2);
	LL_USART_ClearFlag_IDLE(USART2);
	LL_USART_Enable(USART2);
	
}

/**
  * @brief  ����6��ʼ��
 **/
void bsp_usart6_Init(uint8_t* rx_buffr0, uint8_t* rx_buffr1, uint16_t rx_len, usart_call_back fun)
{
	usart_manage_obj[6].rx_buffer_size = rx_len;
	usart_manage_obj[6].rx_buffer0 = rx_buffr0;
	usart_manage_obj[6].rx_buffer1 = rx_buffr1;
	usart_manage_obj[6].call_back_f = fun;
	
	/*DMA����*/
	/*DMA_rx*/
	LL_DMA_SetPeriphAddress(DMA2, LL_DMA_STREAM_1, (uint32_t)(&USART6->DR));
	LL_DMA_SetMemoryAddress(DMA2, LL_DMA_STREAM_1, (uint32_t)rx_buffr0);
	LL_DMA_SetMemory1Address(DMA2, LL_DMA_STREAM_1, (uint32_t)rx_buffr1);
	LL_DMA_SetDataLength(DMA2, LL_DMA_STREAM_1, rx_len);
	LL_DMA_EnableDoubleBufferMode(DMA2, LL_DMA_STREAM_1);
	LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_1);
	LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_1);
	/*DMA_tx*/
	LL_DMA_SetPeriphAddress(DMA2, LL_DMA_STREAM_6, (uint32_t)(&USART6->DR));
	LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_6);
	/*USART����*/
	LL_USART_EnableDMAReq_RX(USART6);
	LL_USART_EnableDMAReq_TX(USART6);
	LL_USART_EnableIT_IDLE(USART6);
	LL_USART_ClearFlag_IDLE(USART6);
	LL_USART_Enable(USART6);
	
}

/*����4�жϷ�����*/
void uart4_IQR_Service(void)
{
	static uint16_t this_time_rx_len = 0;
	
	if(LL_USART_IsActiveFlag_RXNE(UART4) == SET)
	{
		LL_USART_ClearFlag_RXNE(UART4);		//�ϵ������һ�����ڽ����жϣ��ڴ����
	}
	else if(LL_USART_IsActiveFlag_IDLE(UART4) == SET)
	{
		LL_USART_ClearFlag_IDLE(UART4);
		if(LL_DMA_GetCurrentTargetMem(DMA1, LL_DMA_STREAM_2) == 0)		
		{
			/*Memory 0*/
			LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_2);
			while(LL_DMA_IsEnabledStream(DMA1, LL_DMA_STREAM_2)){
			LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_2);}
			LL_DMA_ClearFlag_TC2(DMA1); LL_DMA_ClearFlag_HT2(DMA1);
			LL_DMA_SetCurrentTargetMem(DMA1, LL_DMA_STREAM_2, LL_DMA_CURRENTTARGETMEM1);
			this_time_rx_len = usart_manage_obj[4].rx_buffer_size - LL_DMA_GetDataLength(DMA1, LL_DMA_STREAM_2);
			LL_DMA_ClearFlag_TC2(DMA1); LL_DMA_ClearFlag_HT2(DMA1);
			LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_2);
			
				if(usart_manage_obj[4].call_back_f != NULL)
				usart_manage_obj[4].call_back_f(usart_manage_obj[4].rx_buffer0, this_time_rx_len);
		}
		else
		{
			/*Memory 1*/
			LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_2);
			while(LL_DMA_IsEnabledStream(DMA1, LL_DMA_STREAM_2)){
			LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_2);}
			LL_DMA_ClearFlag_TC2(DMA1); LL_DMA_ClearFlag_HT2(DMA1);
			LL_DMA_SetCurrentTargetMem(DMA1, LL_DMA_STREAM_2, LL_DMA_CURRENTTARGETMEM0);
			this_time_rx_len = usart_manage_obj[4].rx_buffer_size - LL_DMA_GetDataLength(DMA1, LL_DMA_STREAM_2);
			LL_DMA_ClearFlag_TC2(DMA1); LL_DMA_ClearFlag_HT2(DMA1);
			LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_2);

				if(usart_manage_obj[4].call_back_f != NULL)
				usart_manage_obj[4].call_back_f(usart_manage_obj[4].rx_buffer1, this_time_rx_len);
		}
		
	}
}

/*����1�жϷ�����*/
void usart1_IQR_Service(void)
{
	static uint16_t this_time_rx_len = 0;
	if(LL_USART_IsActiveFlag_RXNE(USART1) == SET)
	{
		LL_USART_ClearFlag_RXNE(USART1);
	}
	else if(LL_USART_IsActiveFlag_IDLE(USART1) == SET)
	{
		LL_USART_ClearFlag_IDLE(USART1);
		if(LL_DMA_GetCurrentTargetMem(DMA2, LL_DMA_STREAM_2) == 0)		
		{
			LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_2);
			while(LL_DMA_IsEnabledStream(DMA2, LL_DMA_STREAM_2)){
			LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_2);}
			LL_DMA_ClearFlag_TC2(DMA2); LL_DMA_ClearFlag_HT2(DMA2);
			LL_DMA_SetCurrentTargetMem(DMA2, LL_DMA_STREAM_2, LL_DMA_CURRENTTARGETMEM1);
			this_time_rx_len = usart_manage_obj[1].rx_buffer_size - LL_DMA_GetDataLength(DMA2, LL_DMA_STREAM_2);
			LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_2);
				
				if(usart_manage_obj[1].call_back_f != NULL)
				usart_manage_obj[1].call_back_f(usart_manage_obj[1].rx_buffer0, this_time_rx_len);
				
		}
		else
		{
			LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_2);
			while(LL_DMA_IsEnabledStream(DMA2, LL_DMA_STREAM_2)){
			LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_2);}
			LL_DMA_ClearFlag_TC2(DMA2); LL_DMA_ClearFlag_HT2(DMA2);
			LL_DMA_SetCurrentTargetMem(DMA2, LL_DMA_STREAM_2, LL_DMA_CURRENTTARGETMEM0);
			this_time_rx_len = usart_manage_obj[1].rx_buffer_size - LL_DMA_GetDataLength(DMA2, LL_DMA_STREAM_2);
			LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_2);
			
			if(usart_manage_obj[1].call_back_f != NULL)
				usart_manage_obj[1].call_back_f(usart_manage_obj[1].rx_buffer1, this_time_rx_len);
			
		}
	}
}
/*����2�жϷ�����*/
void usart2_IQR_Service(void)
{
	static uint16_t this_time_rx_len = 0;
	if(LL_USART_IsActiveFlag_RXNE(USART2) == SET)
	{
		LL_USART_ClearFlag_RXNE(USART2);
	}
	else if(LL_USART_IsActiveFlag_IDLE(USART2) == SET)
	{
		LL_USART_ClearFlag_IDLE(USART2);
		if(LL_DMA_GetCurrentTargetMem(DMA1, LL_DMA_STREAM_5) == 0)		
		{
			LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_5);
			while(LL_DMA_IsEnabledStream(DMA1, LL_DMA_STREAM_5)){
			LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_5);}
			LL_DMA_ClearFlag_TC5(DMA1); LL_DMA_ClearFlag_HT5(DMA1);
			LL_DMA_SetCurrentTargetMem(DMA1, LL_DMA_STREAM_5, LL_DMA_CURRENTTARGETMEM1);
			this_time_rx_len = usart_manage_obj[2].rx_buffer_size - LL_DMA_GetDataLength(DMA1, LL_DMA_STREAM_5);
			LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_5);
				
				if(usart_manage_obj[2].call_back_f != NULL)
				usart_manage_obj[2].call_back_f(usart_manage_obj[2].rx_buffer0, this_time_rx_len);
				
		}
		else
		{
			LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_5);
			while(LL_DMA_IsEnabledStream(DMA1, LL_DMA_STREAM_5)){
			LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_5);}
			LL_DMA_ClearFlag_TC5(DMA1); LL_DMA_ClearFlag_HT5(DMA1);
			LL_DMA_SetCurrentTargetMem(DMA1, LL_DMA_STREAM_5, LL_DMA_CURRENTTARGETMEM0);
			this_time_rx_len = usart_manage_obj[2].rx_buffer_size - LL_DMA_GetDataLength(DMA1, LL_DMA_STREAM_5);
			LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_5);
			
			if(usart_manage_obj[2].call_back_f != NULL)
				usart_manage_obj[2].call_back_f(usart_manage_obj[2].rx_buffer1, this_time_rx_len);
			
		}
	}
}

/*����6�жϷ�����*/
void usart6_IQR_Service(void)
{
	static uint16_t this_time_rx_len = 0;
	if(LL_USART_IsActiveFlag_RXNE(USART6) == SET)
	{
		LL_USART_ClearFlag_RXNE(USART6);
	}
	else if(LL_USART_IsActiveFlag_IDLE(USART6) == SET)
	{
		LL_USART_ClearFlag_IDLE(USART6);
		if(LL_DMA_GetCurrentTargetMem(DMA2, LL_DMA_STREAM_1) == 0)		
		{
			LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_1);
			while(LL_DMA_IsEnabledStream(DMA2, LL_DMA_STREAM_1)){
			LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_1);}
			LL_DMA_ClearFlag_TC1(DMA2); LL_DMA_ClearFlag_HT1(DMA2);
			LL_DMA_SetCurrentTargetMem(DMA2, LL_DMA_STREAM_1, LL_DMA_CURRENTTARGETMEM1);
			this_time_rx_len = usart_manage_obj[6].rx_buffer_size - LL_DMA_GetDataLength(DMA2, LL_DMA_STREAM_1);
			LL_DMA_SetDataLength(DMA2, LL_DMA_STREAM_1, usart_manage_obj[6].rx_buffer_size);
			LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_1);
				
				if(usart_manage_obj[6].call_back_f != NULL)
				usart_manage_obj[6].call_back_f(usart_manage_obj[6].rx_buffer0, this_time_rx_len);
				
		}
		else
		{
			LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_1);
			while(LL_DMA_IsEnabledStream(DMA2, LL_DMA_STREAM_1)){
			LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_1);}
			LL_DMA_ClearFlag_TC1(DMA2); LL_DMA_ClearFlag_HT1(DMA2);
			LL_DMA_SetCurrentTargetMem(DMA2, LL_DMA_STREAM_1, LL_DMA_CURRENTTARGETMEM0);
			this_time_rx_len = usart_manage_obj[6].rx_buffer_size - LL_DMA_GetDataLength(DMA2, LL_DMA_STREAM_1);
			LL_DMA_SetDataLength(DMA2, LL_DMA_STREAM_1, usart_manage_obj[6].rx_buffer_size);
			LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_1);
			
			if(usart_manage_obj[6].call_back_f != NULL)
				usart_manage_obj[6].call_back_f(usart_manage_obj[6].rx_buffer1, this_time_rx_len);
			
		}
	}
}


/**
  * @brief  ����1DMA����
 **/
void Usart1_DMA_Transmit(uint32_t data, uint16_t ndtr)
{
	while(LL_USART_IsActiveFlag_TC(USART1) == 0){}
	LL_USART_ClearFlag_TC(USART1);
	LL_DMA_ClearFlag_TC7(DMA2);
	LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_7);
	while(LL_DMA_IsEnabledStream(DMA2, LL_DMA_STREAM_7)){		//ȷ��DMA���Ա�����
	LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_7);}
	LL_DMA_SetMemoryAddress(DMA2, LL_DMA_STREAM_7, data);
	LL_DMA_SetDataLength(DMA2, LL_DMA_STREAM_7, ndtr);
	LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_7);
}
/**
  * @brief  ����2DMA����
 **/
void Usart2_DMA_Transmit(uint32_t data, uint16_t ndtr)
{
	while (LL_USART_IsActiveFlag_TC(USART2) == 0){}
	LL_USART_ClearFlag_TC(USART2);
	LL_DMA_ClearFlag_TC6(DMA1);
	LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_6);
	while(LL_DMA_IsEnabledStream(DMA1, LL_DMA_STREAM_6)){		//ȷ��DMA���Ա�����
	LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_6);}
	LL_DMA_SetMemoryAddress(DMA1, LL_DMA_STREAM_6, data);
	LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_6, ndtr);
	LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_6);

}
/**
  * @brief  ����6DMA����
 **/
void Usart6_DMA_Transmit(uint32_t data, uint16_t ndtr)
{
	while (LL_USART_IsActiveFlag_TC(USART6) == 0){}
	LL_USART_ClearFlag_TC(USART6);
	LL_DMA_ClearFlag_TC6(DMA2);
	LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_6);
	while(LL_DMA_IsEnabledStream(DMA2, LL_DMA_STREAM_6)){		//ȷ��DMA���Ա�����
	LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_6);}
	LL_DMA_SetMemoryAddress(DMA2, LL_DMA_STREAM_6, data);
	LL_DMA_SetDataLength(DMA2, LL_DMA_STREAM_6, ndtr);
	LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_6);

}
