/*
 * Ass-02.h
 *
 *  Created on: Apr 18, 2023
 *      Author: TobyD
 */

#ifndef _ASS-02_H_
#define INC_ASS-02_H_

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include <stdio.h>

extern osTimerId myTimer01Handle;

//LCD DOOODS
#define NULL_EVENT 0
#define LCD_EVENT_OFF 1
#define LCD_EVENT_PAUSE 2
#define LCD_EVENT_RESUME 3
#define LCD_EVENT_START 3

#define GRIND_EVENT 4
#define PAUSE_EVENT 5

#define BUTTONCENTX 160
#define BUTTONCENTY 100
#define BUTTONRADI 100
#define BUTTONSEPERATE 75

#define TRUE 1
#define FALSE 0

// Queue
extern osMessageQId CtrlQueueHandle;


// State Machine
#define IDLE 0
#define GRINDING 1
#define PAUSED 2
#define INIT 3
extern uint32_t currentState;

//Delay and tick cntrl
#define DELAY 50
extern uint32_t durationRemaining;
extern uint32_t duration;

// ADC DOOD
extern ADC_HandleTypeDef hadc1;

// Pause Timer
extern osTimerId PauseTimerHandle;
#define PAUSEDURATION 20000

extern TIM_HandleTypeDef htim2;
extern DAC_HandleTypeDef hdac;

extern uint32_t LESGO;

#endif /* SRC_ASS_02_H_ */
