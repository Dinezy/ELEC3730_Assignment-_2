/*
 * Ass-02-ADCTask.c
 *
 *  Created on: Apr 18, 2023
 *      Author: TobyD
 */

#include "Ass-02.h"

void StartADCTask(void const * argument)
{
  /* USER CODE BEGIN StartADCTask */
  /* Infinite loop */
  for(;;)
  {
	  if(currentState == IDLE)
	  {
		  	HAL_ADC_Start(&hadc1);
			HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);


			duration = (5 + (HAL_ADC_GetValue(&hadc1) - 0.0)*(15 - 5)/4095) * 1000;

			durationRemaining = duration;
	  }
	  osDelay(DELAY);
  }
  /* USER CODE END StartADCTask */
}
