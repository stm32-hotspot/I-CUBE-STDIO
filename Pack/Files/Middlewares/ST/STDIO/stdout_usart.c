/**
******************************************************************************
* @file           : stdout_usart.c 
* @version        : v 1.0.0
* @brief          : This file implements stdout USART channel
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
* All rights reserved.</center></h2>
*
* This software component is licensed by ST under Ultimate Liberty license
* SLA0044, the "License"; You may not use this file except in compliance with
* the License. You may obtain a copy of the License at:
*                             www.st.com/SLA0044
*
******************************************************************************
*/

#include "main.h"
#include "STMicroelectronics.I-CUBE-STDIO_conf.h"
#include <stdio.h>

#ifndef __ICCARM__ /* If not IAR */
int fputc(int ch, FILE *f);
int _write(int file, char *ptr, int len);
#endif /* __CC_ARM */

extern UART_HandleTypeDef STDOUT_UART_HANDLER;

#ifdef __ICCARM__
int __write(int file, char *ptr, int len)
#else
int _write(int file, char *ptr, int len)
#endif
{
  HAL_UART_Transmit(&STDOUT_UART_HANDLER,(uint8_t *)ptr, len, 0xFFFFFFFF);
  
  return len;
}

#ifdef __CC_ARM
int fputc(int ch, FILE *f)
{
  _write(0, (char *)&ch, 1);
  
  return ch;
}
#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
