/*
 * Ass-02-TouchPanelTask.c
 *
 *  Created on: Apr 18, 2023
 *      Author: TobyD
 */

#include "Ass-02.h"
#include "touch_panel.h"
#include "openx07v_c_lcd.h"

#define TOUCHDELAY 500

void OFF_State_Touch_Handle();
void ON_State_Touch_Handle();
void PAUSE_State_Touch_Handle();

//Semaphore
uint32_t LESGO = FALSE;

// Buffer Var
uint32_t BuffVar = 0;

void StartTouchPanelTask(void const * argument)
{
  /* USER CODE BEGIN StartTouchPanelTask */
	// Initialize touch panel
	BSP_LCD_Init();
	BSP_LCD_DisplayOn();
	TouchPanel_Calibrate();
	BSP_LCD_Clear(LCD_COLOR_BLACK);
	BSP_LCD_SetFont(&Font8);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

	// Flag Semaphore
	LESGO = TRUE;

  /* Infinite loop */
  for(;;)
  {
	getDisplayPoint(&display, Read_Ads7846(), &matrix );// Get Touch Sample point

	// State Machine
	switch(currentState){
			case IDLE:
				OFF_State_Touch_Handle();
				break;
			case GRINDING:
				ON_State_Touch_Handle();
				break;
			case PAUSED:
				PAUSE_State_Touch_Handle();
				break;
			default:
				printf("**State NULL Error!**\n");
				break;
		}
    osDelay(DELAY);
  }
  /* USER CODE END StartTouchPanelTask */
}

void OFF_State_Touch_Handle()
{
	// One Big Button to turn on
	if((display.y > (BUTTONCENTY-BUTTONRADI) && (display.y < (BUTTONCENTY+BUTTONRADI)) && (display.x > (BUTTONCENTX-BUTTONRADI)) && (display.x < (BUTTONCENTX+BUTTONRADI)))){
		osMessagePut(CtrlQueueHandle, LCD_EVENT_START,0);
		osDelay(TOUCHDELAY);
	}
}

void ON_State_Touch_Handle()
{
	// Two Buttons @ BUTTONCENTX +/- BUTTONSEPERATE, BUTTONCENTY at BUTTONRAADI/2

	BuffVar = (uint32_t)BUTTONRADI/2;

	// Button 1 to OFF state, Button 2 to Pause state.
	if((display.y > (BUTTONCENTY-BuffVar) && (display.y < (BUTTONCENTY+BuffVar)) && (display.x > (BUTTONCENTX-BUTTONSEPERATE-BuffVar)) && (display.x < (BUTTONCENTX-BUTTONSEPERATE+BuffVar))))
	{
		osMessagePut(CtrlQueueHandle, LCD_EVENT_OFF,0);
		osDelay(TOUCHDELAY);
	}else if((display.y > (BUTTONCENTY-BuffVar) && (display.y < (BUTTONCENTY+BuffVar)) && (display.x > (BUTTONCENTX+BUTTONSEPERATE-BuffVar)) && (display.x < (BUTTONCENTX+BUTTONSEPERATE+BuffVar))))
	{
		osMessagePut(CtrlQueueHandle, LCD_EVENT_PAUSE,0);
		osDelay(TOUCHDELAY);
	}
}

void PAUSE_State_Touch_Handle()
{
	// Two Buttons @ BUTTONCENTX +/- BUTTONSEPERATE, BUTTONCENTY at BUTTONRAADI/2

	BuffVar = (uint32_t)BUTTONRADI/2;

	// Button 1 to OFF state, Button 2 to ON state
	if((display.y > (BUTTONCENTY-BuffVar) && (display.y < (BUTTONCENTY+BuffVar)) &&	(display.x > (BUTTONCENTX-BUTTONSEPERATE-BuffVar)) && (display.x < (BUTTONCENTX-BUTTONSEPERATE+BuffVar))))
	{
		osMessagePut(CtrlQueueHandle, LCD_EVENT_OFF,0);
		osDelay(TOUCHDELAY);
	}else if((display.y > (BUTTONCENTY-BuffVar) && (display.y < (BUTTONCENTY+BuffVar)) && (display.x > (BUTTONCENTX+BUTTONSEPERATE-BuffVar)) && (display.x < (BUTTONCENTX+BUTTONSEPERATE+BuffVar))))
	{
		osMessagePut(CtrlQueueHandle, LCD_EVENT_RESUME,0);
		osDelay(TOUCHDELAY);
	}
}
