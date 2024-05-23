/*
 * Ass-02-ControlTask.c
 *
 *  Created on: Apr 18, 2023
 *      Author: TobyD
 */

#include "Ass-02.h"

#define LETSAGO 1
#define LETSANO 0
#define BUFFSIZE 11

void InitCoffeeMachine();
void OFF_State_Handle();
void ON_State_Handle();
void PAUSE_State_Handle();
void Grinder_ON(void);
void Grinder_OFF(void);

uint32_t currentState = IDLE;
uint32_t PrevState = INIT;
uint32_t Init = LETSAGO;

// Grinder Var
uint32_t DACBuffer[11] = {0, 50, 100, 150, 200, 250, 200, 150, 100, 50, 0};
uint32_t DACBuffer_Silent[1] = {0};

// Grinder Timer Management
uint32_t duration;
uint32_t durationRemaining;

// ADC Read
//uint32_t ADC_Read;

// Message Buffer
osEvent PopedEvent;

void StartControlTask(void const * argument)
{
  /* Machine Init */
  InitCoffeeMachine();
  /* Infinite loop */
  for(;;)
  {
	if(PrevState != currentState){
		Init = LETSAGO;
		PrevState = currentState;
	}else{
		Init = LETSANO;
	}

	switch(currentState){
		case IDLE:
			OFF_State_Handle();
			break;
		case GRINDING:
			ON_State_Handle();
			break;
		case PAUSED:
			PAUSE_State_Handle();
			break;
		default:
			printf("**State NULL Error!**\n");
			break;
	}
    osDelay(1);
  }
  /* USER CODE END StartControlTask */
}

void InitCoffeeMachine()
{
	// Initialise the timer for DAC DMA
	if(HAL_TIM_Base_Start(&htim2)!=HAL_OK)
		printf("INIT HAL_TIM2 ERROR");
	if(HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, DACBuffer_Silent, 1, DAC_ALIGN_12B_R)!=HAL_OK)
		printf("INIT HAL_DAC_DMA ERROR");

}

void OFF_State_Handle()
{
	if(Init)
	{
		osTimerStop(PauseTimerHandle);
		Grinder_OFF();
	}

	if(osMessageGet(CtrlQueueHandle, 0).value.v == LCD_EVENT_START)
		currentState = GRINDING;
}

void ON_State_Handle()
{
	if(Init)
	{
		osTimerStop(PauseTimerHandle);
		Grinder_ON();
	}

	PopedEvent = osMessageGet(CtrlQueueHandle, 0);
	if (PopedEvent.value.v == LCD_EVENT_PAUSE){
		currentState = PAUSED;
	}else if((PopedEvent.value.v == GRIND_EVENT) || (PopedEvent.value.v == LCD_EVENT_OFF)){
		currentState = IDLE;
	}
}


void PAUSE_State_Handle()
{
	if(Init)
	{
		osTimerStart(PauseTimerHandle, PAUSEDURATION);
		Grinder_OFF();
	}

	PopedEvent = osMessageGet(CtrlQueueHandle, 0);
	if (PopedEvent.value.v == LCD_EVENT_RESUME){
		currentState = GRINDING;
	}
	if((PopedEvent.value.v == PAUSE_EVENT) || (PopedEvent.value.v == LCD_EVENT_OFF)){
		currentState = IDLE;
	}
}

void Grinder_ON(void)
{
	if(HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1)!= HAL_OK){
		printf("DAC_STOP_DMA ERROR\n");
	}
	if(HAL_DAC_Start_DMA(&hdac,DAC_CHANNEL_1, DACBuffer, BUFFSIZE, DAC_ALIGN_12B_R)!= HAL_OK){
		printf("DAC_START_DMA ERROR\n");
	}

}

void Grinder_OFF(void)
{
	if(HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1)!= HAL_OK){
		printf("DAC_STOP_DMA ERROR\n");
	}
	if(HAL_DAC_Start_DMA(&hdac,DAC_CHANNEL_1, DACBuffer_Silent, 1, DAC_ALIGN_12B_R)!= HAL_OK){
		printf("DAC_START_DMA ERROR\n");
	}
}

