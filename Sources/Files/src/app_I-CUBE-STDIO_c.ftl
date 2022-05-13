[#ftl]
/**
 ******************************************************************************
 * @file    ${name}
 * @brief   I-CUBE-STDIO Example
 ******************************************************************************
 * @attention
 *
 [@common.optinclude name=mxTmpFolder + "/license.tmp"/][#--include License text --]
 *
 ******************************************************************************
 */
#include <stdio.h>

extern void stdin_init(void);

void ${fctName}(void)
{
  stdin_init();
}

void ${fctProcessName}(void)
{
  char c;
  c = getchar();
  printf("You typed: %c\r\n", c); 
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
