/**
******************************************************************************
* @file           : stdin_usbd_cdc_fs.c
* @version        : v 1.0.0
* @brief          : This file implements stdin USBD FS CDC channel
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
int fgetc(FILE * stream);
int _read(int file, char *ptr, int len);
#endif

extern USBD_HandleTypeDef STDIN_USBD_FS_HANDLER; 

volatile static uint8_t RxData[APP_RX_DATA_SIZE];
volatile static uint32_t data_received = 0;

void stdin_init(void);

void stdin_init(void)
{
  /* This was intentionally left empty */
}

int8_t CDC_Receive_FS(uint8_t* Buf, uint32_t *Len)
{
  data_received = *Len;
  memcpy((uint8_t *)RxData , Buf, *Len);
  
  USBD_CDC_SetRxBuffer  (&STDIN_USBD_FS_HANDLER, &Buf[0]);
  USBD_CDC_ReceivePacket(&STDIN_USBD_FS_HANDLER);
  return (USBD_OK);
}

#ifdef __ICCARM__
int __read(int file, char *ptr, int len)
#else
int _read(int file, char *ptr, int len)
#endif
{
  int length = 0;
  
  do
  {
    while(data_received == 0)
    {
      ;
    }
    
    *ptr = RxData[0];
    ptr++;
    length+= data_received;
    
    data_received = 0;
  }while((length < len) && (*(ptr-1) != '\r'));   
  
  return length;
}


#ifdef __CC_ARM /* Keil Compiler */
int fgetc(FILE * stream)
{
  char ch;
  _read(0, &ch, 1);
  
  return (int)ch;
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
