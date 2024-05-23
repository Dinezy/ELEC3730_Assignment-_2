/*
 * Ass-02-PauseTimer.c
 *
 *  Created on: Apr 18, 2023
 *      Author: TobyD
 */

#include "Ass-02.h"

void PauseCallback(void const * argument)
{
  /* USER CODE BEGIN PauseCallback */
	osMessagePut(CtrlQueueHandle, PAUSE_EVENT,0);
  /* USER CODE END PauseCallback */
}
