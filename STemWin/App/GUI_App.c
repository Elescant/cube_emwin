  /**
  ******************************************************************************
  * @file    GUI_App.c
  * @author  MCD Application Team
  * @brief   Simple demo drawing "Hello world"  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright © 2018 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#include "GUI_App.h"
#include "GUI.h"
#include "DIALOG.h"

uint16_t IOE_ReadID(void);
void GRAPHICS_MainTask(void) {

/* USER CODE BEGIN GRAPHICS_MainTask */
	//CreateFramewin();
 /* User can implement his graphic application here */
  /* Hello Word example */
    GUI_Clear();
    GUI_SetColor(GUI_BLUE);
    GUI_SetFont(&GUI_Font32_1);
    GUI_DispStringAt("Hello world!", (LCD_GetXSize()-150)/2, (LCD_GetYSize()-20)/2);
     if( IOE_ReadID() != 0x0811 )
     {
       while(1);
     }
/* USER CODE END GRAPHICS_MainTask */
  while(1)
{
      GUI_Delay(100);
}
}

#define IOE_ADDR 0x82
extern I2C_HandleTypeDef hi2c3;

uint8_t I2C_ReadDeviceRegister(uint8_t addr)
{
  uint8_t tmp = 0;

  if(HAL_I2C_Master_Transmit_IT(&hi2c3,(uint16_t)IOE_ADDR,(uint8_t *)&addr,1) != HAL_OK)
  {
  }
  while(HAL_I2C_GetState(&hi2c3) != HAL_I2C_STATE_READY);
  if(HAL_I2C_Master_Receive_IT(&hi2c3,IOE_ADDR,&tmp,1) != HAL_OK)
  {

  }
  while(HAL_I2C_GetState(&hi2c3) != HAL_I2C_STATE_READY);
  return tmp;
}


uint16_t IOE_ReadID(void)
{
  uint16_t tmp = 0;

  /* Read device ID  */
  tmp = I2C_ReadDeviceRegister(0);
  tmp = (uint32_t)(tmp << 8);
  tmp |= (uint32_t)I2C_ReadDeviceRegister(1);
  
  /* Return the ID */
  return (uint16_t)tmp;
}
/*************************** End of file ****************************/
