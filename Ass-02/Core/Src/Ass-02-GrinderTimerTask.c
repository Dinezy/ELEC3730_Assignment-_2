/*
 * Ass-02-GrinderTimerTask.c
 *
 *  Created on: Apr 18, 2023
 *      Author: TobyD
 */

#include "Ass-02.h"

void StartGrinderTimerTask(void const * argument)
{
  /* USER CODE BEGIN StartGrinderTimerTask */

  /* Infinite loop */
  for(;;)
  {
	osDelay(DELAY);
	if(currentState == GRINDING)
	{
		durationRemaining = durationRemaining-DELAY;		//keeping track of ticks

		if((int)durationRemaining < 1)
			osMessagePut(CtrlQueueHandle, GRIND_EVENT,0);	//ONESHOT
	}
  }
  /* USER CODE END StartGrinderTimerTask */
}
