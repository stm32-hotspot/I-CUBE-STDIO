/**
 ******************************************************************************
 * @file    STMicroelectronics.I-CUBE-STDIO.1.1.0
 * @brief   The Example application
 ******************************************************************************
 * @attention
 *
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
 *
 ******************************************************************************
 */
#include <stdio.h>

extern void stdin_init(void);

void MX_Example_Init(void)
{
  stdin_init();
}

void MX_Example_Process(void)
{
  char c;
  c = getchar();
  printf("You typed: %c\r\n", c);
}

