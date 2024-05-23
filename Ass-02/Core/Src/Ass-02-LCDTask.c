/*
 * Ass-02-LCDTask.c
 *
 *  Created on: Apr 18, 2023
 *      Author: TobyD
 */

#include "Ass-02.h"
#include "touch_panel.h"
#include "openx07v_c_lcd.h"

void OFF_State_LCD_Handle();
void ON_State_LCD_Handle();
void PAUSE_State_LCD_Handle();
void TimeCounter();
uint32_t refresh = TRUE;
uint32_t PrevStateLCD = INIT;
uint32_t TensSec;
uint32_t Seconds;
uint32_t Tenths;
uint32_t durationPassed;

char ChrBuff[9] = {'0','0','.','0',' ','S','E','C',0};
char START[5]= {'S','T','A','R','T'};
char OFF[3] = {'O','F','F'};
char ON[2] = {'O','N'};
char PAUSE[5] = {'P','A','U','S','E'};
char RESUME[6] = {'R','E','S','U','M','E'};

void StartLCDTask(void const * argument)
{
  /* USER CODE BEGIN StartLCDTask */
	// Wait for semaphore
	while(!LESGO)
		osDelay(10);

  /* Infinite loop */
  for(;;)
  {
	  if(PrevStateLCD != currentState)
	  {
		  refresh = TRUE;
		  PrevStateLCD = currentState;
	  }else{
		  refresh = FALSE;
	  }

	  if(refresh){
		// State Machine
		switch(currentState){
			case IDLE:
				OFF_State_LCD_Handle();
				break;
			case GRINDING:
				ON_State_LCD_Handle();
				break;
			case PAUSED:
				PAUSE_State_LCD_Handle();
				break;
			default:
				printf("**State NULL Error!**\n");
				break;
			}
		refresh = 0;
	  }

	  TimeCounter();

	  osDelay(DELAY);
  }
  /* USER CODE END StartLCDTask */
}

void OFF_State_LCD_Handle()
{
	BSP_LCD_Clear(LCD_COLOR_BLACK);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillCircle(BUTTONCENTX, BUTTONCENTY, BUTTONRADI);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(5, BUTTONCENTY-8,(uint8_t*)START,CENTER_MODE);
}

void ON_State_LCD_Handle()
{
	BSP_LCD_Clear(LCD_COLOR_GREEN);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillCircle(BUTTONCENTX+BUTTONSEPERATE, BUTTONCENTY, (uint16_t)BUTTONRADI/2);
	BSP_LCD_FillCircle(BUTTONCENTX-BUTTONSEPERATE, BUTTONCENTY, (uint16_t)BUTTONRADI/2);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(-BUTTONCENTX/2+13, BUTTONCENTY-10,(uint8_t*)OFF,CENTER_MODE);
	BSP_LCD_DisplayStringAt(BUTTONCENTX/2+3, BUTTONCENTY-10,(uint8_t*)PAUSE,CENTER_MODE);
}

void PAUSE_State_LCD_Handle()
{
	BSP_LCD_Clear(LCD_COLOR_ORANGE);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillCircle(BUTTONCENTX+BUTTONSEPERATE, BUTTONCENTY, (uint16_t)BUTTONRADI/2);
	BSP_LCD_FillCircle(BUTTONCENTX-BUTTONSEPERATE, BUTTONCENTY, (uint16_t)BUTTONRADI/2);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(-BUTTONCENTX/2+13, BUTTONCENTY-10,(uint8_t*)OFF,CENTER_MODE);
	BSP_LCD_DisplayStringAt(BUTTONCENTX/2+3, BUTTONCENTY-10,(uint8_t*)RESUME,CENTER_MODE);
}

void TimeCounter()
{
	durationPassed = durationRemaining;
	TensSec = (uint32_t)durationPassed/10000;
	Seconds = (uint32_t)((durationPassed-10000*TensSec)/1000);
	Tenths = (uint32_t)((durationPassed-1000*Seconds)/100);

	if(TensSec == 0){
		ChrBuff[0] = ' ';
	}else{
		ChrBuff[0] = TensSec + 48;
	}
	ChrBuff[1] = Seconds + 48;
	ChrBuff[3] = (Tenths % 10) + 48;
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(0, BUTTONCENTY+110,(uint8_t*)ChrBuff,CENTER_MODE);
}
