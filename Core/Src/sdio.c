/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    sdio.c
  * @brief   This file provides code for the configuration
  *          of the SDIO instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "sdio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

MMC_HandleTypeDef hmmc;
DMA_HandleTypeDef hdma_sdio;

/* SDIO init function */

void MX_SDIO_MMC_Init(void)
{

  /* USER CODE BEGIN SDIO_Init 0 */

  /* USER CODE END SDIO_Init 0 */

  /* USER CODE BEGIN SDIO_Init 1 */

  /* USER CODE END SDIO_Init 1 */
  hmmc.Instance = SDIO;
  hmmc.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
  hmmc.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;
  hmmc.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;
  hmmc.Init.BusWide = SDIO_BUS_WIDE_1B;
  hmmc.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_ENABLE;
  hmmc.Init.ClockDiv = 2;
  if (HAL_MMC_Init(&hmmc) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_MMC_ConfigWideBusOperation(&hmmc, SDIO_BUS_WIDE_8B) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SDIO_Init 2 */

  /* USER CODE END SDIO_Init 2 */

}

void HAL_MMC_MspInit(MMC_HandleTypeDef* mmcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(mmcHandle->Instance==SDIO)
  {
  /* USER CODE BEGIN SDIO_MspInit 0 */

  /* USER CODE END SDIO_MspInit 0 */
    /* SDIO clock enable */
    __HAL_RCC_SDIO_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**SDIO GPIO Configuration
    PB9     ------> SDIO_D5
    PB8     ------> SDIO_D4
    PD2     ------> SDIO_CMD
    PC11     ------> SDIO_D3
    PC10     ------> SDIO_D2
    PC12     ------> SDIO_CK
    PC9     ------> SDIO_D1
    PC7     ------> SDIO_D7
    PC8     ------> SDIO_D0
    PC6     ------> SDIO_D6
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_9
                          |GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* SDIO DMA Init */
    /* SDIO Init */
    hdma_sdio.Instance = DMA2_Channel4;
    hdma_sdio.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_sdio.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_sdio.Init.MemInc = DMA_MINC_ENABLE;
    hdma_sdio.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_sdio.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_sdio.Init.Mode = DMA_NORMAL;
    hdma_sdio.Init.Priority = DMA_PRIORITY_HIGH;
    if (HAL_DMA_Init(&hdma_sdio) != HAL_OK)
    {
      Error_Handler();
    }

    /* Several peripheral DMA handle pointers point to the same DMA handle.
     Be aware that there is only one channel to perform all the requested DMAs. */
    /* Be sure to change transfer direction before calling
     HAL_SD_ReadBlocks_DMA or HAL_SD_WriteBlocks_DMA. */
    __HAL_LINKDMA(mmcHandle,hdmarx,hdma_sdio);
    __HAL_LINKDMA(mmcHandle,hdmatx,hdma_sdio);

  /* USER CODE BEGIN SDIO_MspInit 1 */

  /* USER CODE END SDIO_MspInit 1 */
  }
}

void HAL_MMC_MspDeInit(MMC_HandleTypeDef* mmcHandle)
{

  if(mmcHandle->Instance==SDIO)
  {
  /* USER CODE BEGIN SDIO_MspDeInit 0 */

  /* USER CODE END SDIO_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SDIO_CLK_DISABLE();

    /**SDIO GPIO Configuration
    PB9     ------> SDIO_D5
    PB8     ------> SDIO_D4
    PD2     ------> SDIO_CMD
    PC11     ------> SDIO_D3
    PC10     ------> SDIO_D2
    PC12     ------> SDIO_CK
    PC9     ------> SDIO_D1
    PC7     ------> SDIO_D7
    PC8     ------> SDIO_D0
    PC6     ------> SDIO_D6
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_9|GPIO_PIN_8);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);

    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_9
                          |GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_6);

    /* SDIO DMA DeInit */
    HAL_DMA_DeInit(mmcHandle->hdmarx);
    HAL_DMA_DeInit(mmcHandle->hdmatx);
  /* USER CODE BEGIN SDIO_MspDeInit 1 */

  /* USER CODE END SDIO_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
