/**
  ******************************************************************************
  * File Name          : STMicroelectronics.I-CUBE-STDIO_conf.h
  * Description        : This file provides code for the configuration
  *                      of the STMicroelectronics.I-CUBE-STDIO_conf.h instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STMICROELECTRONICS__I_CUBE_STDIO_CONF__H__
#define __STMICROELECTRONICS__I_CUBE_STDIO_CONF__H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/**
	MiddleWare name : STMicroelectronics.I-CUBE-STDIO.1.4.0
	MiddleWare fileName : STMicroelectronics.I-CUBE-STDIO_conf.h
	MiddleWare version :
*/
/*---------- STDIN_UART_HANDLER  -----------*/
#define STDIN_UART_HANDLER      huart1

/*---------- STDIN_USBD_FS_HANDLER  -----------*/
#define STDIN_USBD_FS_HANDLER      hUsbDeviceFS

/*---------- STDIN_USBD_HS_HANDLER  -----------*/
#define STDIN_USBD_HS_HANDLER      hUsbDeviceHS

/*---------- STDIN_USBH_FS_HANDLER  -----------*/
#define STDIN_USBH_FS_HANDLER      hUsbHostFS

/*---------- STDIN_USBH_HS_HANDLER  -----------*/
#define STDIN_USBH_HS_HANDLER      hUsbHostHS

/*---------- STDOUT_UART_HANDLER  -----------*/
#define STDOUT_UART_HANDLER      huart3

/*---------- STDOUT_USBD_FS_HANDLER  -----------*/
#define STDOUT_USBD_FS_HANDLER      hUsbDeviceFS

/*---------- STDOUT_USBD_HS_HANDLER  -----------*/
#define STDOUT_USBD_HS_HANDLER      hUsbDeviceHS

#ifdef __cplusplus
}
#endif
#endif /*__ STMICROELECTRONICS__I_CUBE_STDIO_CONF__H_H */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
