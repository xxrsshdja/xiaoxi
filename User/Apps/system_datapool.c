#include "system_datapool.h"

uint8_t Usart1_Rx_Buff[2][USART1_RX_BUFFER_SIZE];
uint8_t Usart2_Rx_Buff[2][USART2_RX_BUFFER_SIZE];
uint8_t Uart4_Rx_Buff[2][UART4_RX_BUFFER_SIZE];
uint8_t Usart6_Rx_Buff[2][USART6_RX_BUFFER_SIZE];
System_HEAD	sys_dat = {0};
