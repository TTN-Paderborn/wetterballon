/*
 * my_syscalls.c
 *
 *  Created on: 17.12.2018
 *      Author: rex
 */

#include <string.h>

#include "main.h"
#include "usart.h"

static uint8_t puffer[128];

int _write(int file, char *data, int len)
{
	int out_len = len;

	if (len < sizeof(puffer)) {
		strncpy((char *)puffer, data, len);
	}
	else {
		strcpy((char *)puffer, "Message too long\n");
		out_len = strlen(puffer);
	}

   // arbitrary timeout 1000
   HAL_StatusTypeDef status = HAL_UART_Transmit(&huart2, puffer, out_len, 1000);

   // return # of bytes written - as best we can tell
   return (status == HAL_OK ? len : 0);
}
