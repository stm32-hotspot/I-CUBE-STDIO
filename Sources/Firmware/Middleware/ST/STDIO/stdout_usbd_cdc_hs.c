/**
******************************************************************************
*  @file           : stdout_usbd_hs.c 
* @version        : v 1.0.0
* @brief          : This file implements stdout USBD HS CDC channel
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
#include "usbd_cdc_if.h"

#ifndef __ICCARM__ /* If not IAR */
int fputc(int ch, FILE *f);
int _write(int file, char *ptr, int len);
#endif /* __CC_ARM */

extern USBD_HandleTypeDef STDOUT_USBD_HS_HANDLER;

static uint8_t CDC_Transmit(uint8_t* Buf, uint16_t Len);

static uint8_t CDC_Transmit(uint8_t* Buf, uint16_t Len)
{
  uint8_t result = USBD_OK;
  /* USER CODE BEGIN 7 */
  USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef*)STDOUT_USBD_HS_HANDLER.pClassData;
  
  if (hcdc->TxState != 0)
  {
    return USBD_BUSY;
  }
  
  USBD_CDC_SetTxBuffer            (&STDOUT_USBD_HS_HANDLER, Buf, Len);
  result = USBD_CDC_TransmitPacket(&STDOUT_USBD_HS_HANDLER);
  /* USER CODE END 7 */
  return result;
}

#define _write_send(ptr, len)  CDC_Transmit(ptr, len);

#ifdef __ICCARM__ /* IAR Compiler */
int __write(int file, char *ptr, int len)
#else /* Keil and GCC */
int _write(int file, char *ptr, int len)
#endif
{
  _write_send((uint8_t *)ptr, len);

  return len;
}

#ifdef __CC_ARM /* Keil */
int fputc(int ch, FILE *f)
{
  _write(0, (char *)&ch, 1);

  return ch;
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
