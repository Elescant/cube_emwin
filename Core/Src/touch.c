#include "main.h"
#include "touch.h"

uint16_t IOE_ReadID(void);

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