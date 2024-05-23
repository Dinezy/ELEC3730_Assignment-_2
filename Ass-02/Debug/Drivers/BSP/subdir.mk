################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/ili9325.c \
../Drivers/BSP/openx07v_c_lcd.c \
../Drivers/BSP/touch_panel.c 

OBJS += \
./Drivers/BSP/ili9325.o \
./Drivers/BSP/openx07v_c_lcd.o \
./Drivers/BSP/touch_panel.o 

C_DEPS += \
./Drivers/BSP/ili9325.d \
./Drivers/BSP/openx07v_c_lcd.d \
./Drivers/BSP/touch_panel.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/%.o Drivers/BSP/%.su: ../Drivers/BSP/%.c Drivers/BSP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP

clean-Drivers-2f-BSP:
	-$(RM) ./Drivers/BSP/ili9325.d ./Drivers/BSP/ili9325.o ./Drivers/BSP/ili9325.su ./Drivers/BSP/openx07v_c_lcd.d ./Drivers/BSP/openx07v_c_lcd.o ./Drivers/BSP/openx07v_c_lcd.su ./Drivers/BSP/touch_panel.d ./Drivers/BSP/touch_panel.o ./Drivers/BSP/touch_panel.su

.PHONY: clean-Drivers-2f-BSP

