/**
  ******************************************************************************
  * @file  : custom.c
  * @brief : Source file for the BSP Common driver
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

/* Includes ------------------------------------------------------------------*/
#include "custom.h"
#include "stm32f7xx_hal_exti.h"

/** @defgroup BSP BSP
 * @{
 */

/** @defgroup CUSTOM CUSTOM
 * @{
 */

/** @defgroup CUSTOM_LOW_LEVEL CUSTOM LOW LEVEL
 *  @brief This file provides set of firmware functions to manage Leds and push-button
 *         available on STM32F7xx-Nucleo Kit from STMicroelectronics.
 * @{
 */

/**
 * @}
 */

/** @defgroup CUSTOM_LOW_LEVEL_Private_Defines CUSTOM LOW LEVEL Private Defines
 * @{
 */

/** @defgroup CUSTOM_LOW_LEVEL_FunctionPrototypes CUSTOM LOW LEVEL Private Function Prototypes
 * @{
 */
typedef void (* BSP_EXTI_LineCallback) (void);
typedef void (* BSP_BUTTON_GPIO_Init) (void);

/**
 * @}
 */

/** @defgroup CUSTOM_LOW_LEVEL_Private_Variables CUSTOM LOW LEVEL Private Variables
 * @{
 */
typedef void (* BSP_LED_GPIO_Init) (void);
static GPIO_TypeDef*  LED_PORT[LEDn] = {LED2_GPIO_PORT};
static const uint16_t LED_PIN[LEDn]  = {LED2_PIN};
static void LED_USER_GPIO_Init(void);

static GPIO_TypeDef*   BUTTON_PORT[BUTTONn] = {USER_BUTTON_GPIO_PORT};
static const uint16_t  BUTTON_PIN[BUTTONn]  = {USER_BUTTON_PIN};
static const IRQn_Type BUTTON_IRQn[BUTTONn] = {USER_BUTTON_EXTI_IRQn};
EXTI_HandleTypeDef hpb_exti[BUTTONn] = {{.Line = EXTI_LINE_13}};
/**
 * @}
 */

/** @defgroup CUSTOM_LOW_LEVEL_Private_Functions CUSTOM LOW LEVEL Private Functions
 * @{
 */
static void BUTTON_USER_EXTI_Callback(void);
static void BUTTON_USER_GPIO_Init(void);
/**
 * @brief  This method returns the STM32F7xx NUCLEO BSP Driver revision
 * @retval version: 0xXYZR (8bits for each decimal, R for RC)
 */
int32_t BSP_GetVersion(void)
{
  return (int32_t)__CUSTOM_BSP_VERSION;
}

/**
 * @brief  Configures LED on GPIO and/or on MFX.
 * @param  Led: LED to be configured.
 *              This parameter can be one of the following values:
 *              @arg  LED2, LED4, ...
 * @retval HAL status
 */
int32_t BSP_LED_Init(Led_TypeDef Led)
{
  static const BSP_LED_GPIO_Init LedGpioInit[LEDn] = {LED_USER_GPIO_Init};
  LedGpioInit[Led]();
  return BSP_ERROR_NONE;
}

/**
 * @brief  DeInit LEDs.
 * @param  Led: LED to be configured.
 *              This parameter can be one of the following values:
 *              @arg  LED2, LED4, ...
 * @note Led DeInit does not disable the GPIO clock nor disable the Mfx
 * @retval HAL status
 */
int32_t BSP_LED_DeInit(Led_TypeDef Led)
{
  GPIO_InitTypeDef  gpio_init_structure;

  /* Turn off LED */
  HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_RESET);
  /* DeInit the GPIO_LED pin */
  gpio_init_structure.Pin = LED_PIN[Led];
  HAL_GPIO_DeInit(LED_PORT[Led], gpio_init_structure.Pin);

  return BSP_ERROR_NONE;
}

/**
 * @brief  Turns selected LED On.
 * @param  Led: LED to be set on
 *              This parameter can be one of the following values:
 *              @arg  LED1
 *              @arg  LED2
 *              @arg  LED3
 *              @arg  LED4
 * @retval HAL status
 */
int32_t BSP_LED_On(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(LED_PORT [Led], LED_PIN [Led], GPIO_PIN_SET);

  return BSP_ERROR_NONE;
}

/**
 * @brief  Turns selected LED Off.
 * @param  Led: LED to be set off
 *              This parameter can be one of the following values:
 *              @arg  LED1
 *              @arg  LED2
 *              @arg  LED3
 *              @arg  LED4
 * @retval HAL status
 */
int32_t BSP_LED_Off(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(LED_PORT [Led], LED_PIN [Led], GPIO_PIN_RESET);

  return BSP_ERROR_NONE;
}

/**
 * @brief  Toggles the selected LED.
 * @param  Led: LED to be toggled
 *              This parameter can be one of the following values:
 *              @arg  LED1
 *              @arg  LED2
 *              @arg  LED3
 *              @arg  LED4
 * @retval HAL status
 */
int32_t BSP_LED_Toggle(Led_TypeDef Led)
{
  HAL_GPIO_TogglePin(LED_PORT[Led], LED_PIN[Led]);

  return BSP_ERROR_NONE;
}

/**
 * @brief  Get the status of the LED.
 * @param  Led: LED for which get the status
 *              This parameter can be one of the following values:
 *              @arg  LED1
 *              @arg  LED2
 *              @arg  LED3
 *              @arg  LED4
 * @retval HAL status (1=high, 0=low)
 */
int32_t BSP_LED_GetState(Led_TypeDef Led)
{
  return (int32_t)(HAL_GPIO_ReadPin (LED_PORT [Led], LED_PIN [Led]) == GPIO_PIN_RESET);
}
/**
  * @brief
  * @retval None
  */
static void LED_USER_GPIO_Init(void) {
}

/**
  * @brief  Configures button GPIO and EXTI Line.
  * @param  Button: Button to be configured
  *                 This parameter can be one of the following values:
  *                 @arg  BUTTON_USER: User Push Button
  * @param  ButtonMode Button mode
  *                    This parameter can be one of the following values:
  *                    @arg  BUTTON_MODE_GPIO: Button will be used as simple IO
  *                    @arg  BUTTON_MODE_EXTI: Button will be connected to EXTI line
  *                                            with interrupt generation capability
  * @retval BSP status
  */
int32_t BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode)
{
  int32_t ret = BSP_ERROR_NONE;
  GPIO_InitTypeDef gpio_init_structure;

  static const BSP_EXTI_LineCallback ButtonCallback[BUTTONn] ={BUTTON_USER_EXTI_Callback};
  static const uint32_t  BSP_BUTTON_PRIO [BUTTONn] ={BSP_BUTTON_USER_IT_PRIORITY};
  static const uint32_t BUTTON_EXTI_LINE[BUTTONn] ={USER_BUTTON_EXTI_LINE};
  static const BSP_BUTTON_GPIO_Init ButtonGpioInit[BUTTONn] = {BUTTON_USER_GPIO_Init};

  ButtonGpioInit[Button]();

  if (ButtonMode == BUTTON_MODE_EXTI)
  {
    /* Configure Button pin as input with External interrupt */
    gpio_init_structure.Mode = GPIO_MODE_IT_RISING;

    HAL_GPIO_Init(BUTTON_PORT[Button], &gpio_init_structure);

    if(HAL_EXTI_GetHandle(&hpb_exti[Button], BUTTON_EXTI_LINE[Button]) != HAL_OK)
	{
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
    else if (HAL_EXTI_RegisterCallback(&hpb_exti[Button],  HAL_EXTI_COMMON_CB_ID, ButtonCallback[Button]) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
	else
	{
      /* Enable and set Button EXTI Interrupt to the lowest priority */
      HAL_NVIC_SetPriority((BUTTON_IRQn[Button]), BSP_BUTTON_PRIO[Button], 0x00);
      HAL_NVIC_EnableIRQ((BUTTON_IRQn[Button]));
	}
  }

  return ret;
}

/**
 * @brief  Push Button DeInit.
 * @param  Button Button to be configured
 *                This parameter can be one of the following values:
 *                @arg  BUTTON_USER: Wakeup Push Button
 * @note PB DeInit does not disable the GPIO clock
 * @retval BSP status
 */
int32_t BSP_PB_DeInit(Button_TypeDef Button)
{
  GPIO_InitTypeDef gpio_init_structure;

  gpio_init_structure.Pin = BUTTON_PIN[Button];
  HAL_NVIC_DisableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
  HAL_GPIO_DeInit(BUTTON_PORT[Button], gpio_init_structure.Pin);

  return BSP_ERROR_NONE;
}

/**
 * @brief  Returns the selected button state.
 * @param  Button Button to be adressed
 *                This parameter can be one of the following values:
 *                @arg  BUTTON_USER
 * @retval The Button GPIO pin value (GPIO_PIN_RESET = button pressed)
 */
int32_t BSP_PB_GetState(Button_TypeDef Button)
{
  return (int32_t)(HAL_GPIO_ReadPin(BUTTON_PORT[Button], BUTTON_PIN[Button]) == GPIO_PIN_RESET);
}

/**
 * @brief  User EXTI line detection callbacks.
 * @retval None
 */
void BSP_PB_IRQHandler (Button_TypeDef Button)
{
  HAL_EXTI_IRQHandler( &hpb_exti[Button] );
}

/**
 * @brief  BSP Push Button callback
 * @param  Button Specifies the pin connected EXTI line
 * @retval None.
 */
__weak void BSP_PB_Callback(Button_TypeDef Button)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(Button);

  /* This function should be implemented by the user application.
     It is called into this driver when an event on Button is triggered. */
}

/**
  * @brief  User EXTI line detection callbacks.
  * @retval None
  */
static void BUTTON_USER_EXTI_Callback(void)
{
  BSP_PB_Callback(BUTTON_USER);
}

/**
  * @brief
  * @retval None
  */
static void BUTTON_USER_GPIO_Init(void) {
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

