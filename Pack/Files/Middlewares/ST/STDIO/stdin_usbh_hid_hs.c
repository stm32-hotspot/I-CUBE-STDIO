/**
******************************************************************************
* @file           : stdin_usbh_hid_fs.c
* @version        : v 1.0.0
* @brief          : This file implements stdin USBH HS HID channel
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
#include "usb_host.h"
#include "usbh_core.h"
#include "usbh_hid.h"

#ifndef __ICCARM__ /* If not IAR */
int fgetc(FILE * stream);
int _read(int file, char *ptr, int len);
#endif

volatile uint8_t RxData[1];
volatile uint32_t data_received = 0;

extern USBH_HandleTypeDef STDIN_USBH_HS_HANDLER; 
extern ApplicationTypeDef Appli_state;

static uint8_t keyboard_Process(void);
void stdin_init(void);

void stdin_init(void)
{
  do
  {
    do
    {
      USBH_Process(&STDIN_USBH_HS_HANDLER);
    }while(Appli_state != APPLICATION_READY);
  }while(USBH_HID_GetDeviceType(&STDIN_USBH_HS_HANDLER) != HID_KEYBOARD);  
}

void USBH_Keybd_Process(USBH_HandleTypeDef *phost)
{
  HID_KEYBD_Info_TypeDef *k_pinfo; 
  k_pinfo = USBH_HID_GetKeybdInfo(phost);
  char c;
  
  if(k_pinfo != NULL)
  {
    c = USBH_HID_GetASCIICode(k_pinfo);
    
    if(c != 0)
    {
      data_received = 1;
      RxData[0] = c;
    }
  }
}

static uint8_t keyboard_Process(void)
{
  if(Appli_state == APPLICATION_READY)
  {
    if(USBH_HID_GetDeviceType(&STDIN_USBH_HS_HANDLER) == HID_KEYBOARD)
    {
      USBH_Keybd_Process(&STDIN_USBH_HS_HANDLER);
      return 0;
    }
    
    return 1;
  }
  
  return 1;
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
       USBH_Process(&STDIN_USBH_HS_HANDLER);
       keyboard_Process();
     }

      data_received = 0;

     *ptr = RxData[0];
      ptr++;
      length++;
      
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
