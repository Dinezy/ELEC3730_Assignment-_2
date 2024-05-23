/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Ass-02.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
/* USER CODE END Variables */
osThreadId InitTaskHandle;
osThreadId ControlTaskHandle;
osThreadId TouchPanelTaskHandle;
osThreadId ADCTaskHandle;
osThreadId GrinderTimTaskHandle;
osThreadId LCDTaskHandle;
osMessageQId CtrlQueueHandle;
osTimerId PauseTimerHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartInitTask(void const * argument);
void StartControlTask(void const * argument);
void StartTouchPanelTask(void const * argument);
void StartADCTask(void const * argument);
void StartGrinderTimerTask(void const * argument);
void StartLCDTask(void const * argument);
void PauseCallback(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )
{
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = &xTimerStack[0];
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
  /* place for user code */
}
/* USER CODE END GET_TIMER_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* definition and creation of PauseTimer */
  osTimerDef(PauseTimer, PauseCallback);
  PauseTimerHandle = osTimerCreate(osTimer(PauseTimer), osTimerOnce, NULL);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of CtrlQueue */
  osMessageQDef(CtrlQueue, 16, uint32_t);
  CtrlQueueHandle = osMessageCreate(osMessageQ(CtrlQueue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of InitTask */
  osThreadDef(InitTask, StartInitTask, osPriorityHigh, 0, 128);
  InitTaskHandle = osThreadCreate(osThread(InitTask), NULL);

  /* definition and creation of ControlTask */
  osThreadDef(ControlTask, StartControlTask, osPriorityIdle, 0, 128);
  ControlTaskHandle = osThreadCreate(osThread(ControlTask), NULL);

  /* definition and creation of TouchPanelTask */
  osThreadDef(TouchPanelTask, StartTouchPanelTask, osPriorityIdle, 0, 128);
  TouchPanelTaskHandle = osThreadCreate(osThread(TouchPanelTask), NULL);

  /* definition and creation of ADCTask */
  osThreadDef(ADCTask, StartADCTask, osPriorityIdle, 0, 128);
  ADCTaskHandle = osThreadCreate(osThread(ADCTask), NULL);

  /* definition and creation of GrinderTimTask */
  osThreadDef(GrinderTimTask, StartGrinderTimerTask, osPriorityIdle, 0, 128);
  GrinderTimTaskHandle = osThreadCreate(osThread(GrinderTimTask), NULL);

  /* definition and creation of LCDTask */
  osThreadDef(LCDTask, StartLCDTask, osPriorityIdle, 0, 128);
  LCDTaskHandle = osThreadCreate(osThread(LCDTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartInitTask */
/**
  * @brief  Function implementing the InitTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartInitTask */
__weak void StartInitTask(void const * argument)
{
  /* USER CODE BEGIN StartInitTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartInitTask */
}

/* USER CODE BEGIN Header_StartControlTask */
/**
* @brief Function implementing the ControlTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartControlTask */
__weak void StartControlTask(void const * argument)
{
  /* USER CODE BEGIN StartControlTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartControlTask */
}

/* USER CODE BEGIN Header_StartTouchPanelTask */
/**
* @brief Function implementing the TouchPanelTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTouchPanelTask */
__weak void StartTouchPanelTask(void const * argument)
{
  /* USER CODE BEGIN StartTouchPanelTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTouchPanelTask */
}

/* USER CODE BEGIN Header_StartADCTask */
/**
* @brief Function implementing the ADCTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartADCTask */
__weak void StartADCTask(void const * argument)
{
  /* USER CODE BEGIN StartADCTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartADCTask */
}

/* USER CODE BEGIN Header_StartGrinderTimerTask */
/**
* @brief Function implementing the GrinderTimTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartGrinderTimerTask */
__weak void StartGrinderTimerTask(void const * argument)
{
  /* USER CODE BEGIN StartGrinderTimerTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartGrinderTimerTask */
}

/* USER CODE BEGIN Header_StartLCDTask */
/**
* @brief Function implementing the LCDTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLCDTask */
__weak void StartLCDTask(void const * argument)
{
  /* USER CODE BEGIN StartLCDTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartLCDTask */
}

/* PauseCallback function */
__weak void PauseCallback(void const * argument)
{
  /* USER CODE BEGIN PauseCallback */

  /* USER CODE END PauseCallback */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
