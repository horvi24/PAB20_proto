#include "core.h"


// printf >> DBG_RX4 (usart2)
PUTCHAR_PROTOTYPE {
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART4 and Loop until the end of transmission */
	HAL_UART_Transmit(&huart4, (uint8_t*) &ch, 1, 0xFFFF);
	return ch;
}
