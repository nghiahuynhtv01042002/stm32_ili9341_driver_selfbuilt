################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ili9341/src/font.c \
../ili9341/src/ili9341.c \
../ili9341/src/image.c 

OBJS += \
./ili9341/src/font.o \
./ili9341/src/ili9341.o \
./ili9341/src/image.o 

C_DEPS += \
./ili9341/src/font.d \
./ili9341/src/ili9341.d \
./ili9341/src/image.d 


# Each subdirectory must supply rules for building sources it contributes
ili9341/src/%.o ili9341/src/%.su ili9341/src/%.cyclo: ../ili9341/src/%.c ili9341/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I"G:/stm32cubeide/workspace/TouchScreen/NoneOS/ili9341/inc" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Oz -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ili9341-2f-src

clean-ili9341-2f-src:
	-$(RM) ./ili9341/src/font.cyclo ./ili9341/src/font.d ./ili9341/src/font.o ./ili9341/src/font.su ./ili9341/src/ili9341.cyclo ./ili9341/src/ili9341.d ./ili9341/src/ili9341.o ./ili9341/src/ili9341.su ./ili9341/src/image.cyclo ./ili9341/src/image.d ./ili9341/src/image.o ./ili9341/src/image.su

.PHONY: clean-ili9341-2f-src

