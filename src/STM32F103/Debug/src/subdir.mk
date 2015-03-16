################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Commands.cpp \
../src/Communication.cpp \
../src/Eeprom.cpp \
../src/Extruder.cpp \
../src/GPIO.cpp \
../src/HAL.cpp \
../src/Printer.cpp \
../src/Serial.cpp \
../src/delay.cpp \
../src/gcode.cpp \
../src/main.cpp \
../src/motion.cpp \
../src/ui.cpp 

OBJS += \
./src/Commands.o \
./src/Communication.o \
./src/Eeprom.o \
./src/Extruder.o \
./src/GPIO.o \
./src/HAL.o \
./src/Printer.o \
./src/Serial.o \
./src/delay.o \
./src/gcode.o \
./src/main.o \
./src/motion.o \
./src/ui.o 

CPP_DEPS += \
./src/Commands.d \
./src/Communication.d \
./src/Eeprom.d \
./src/Extruder.d \
./src/GPIO.d \
./src/HAL.d \
./src/Printer.d \
./src/Serial.d \
./src/delay.d \
./src/gcode.d \
./src/main.d \
./src/motion.d \
./src/ui.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m3 -mthumb -mlittle-endian -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


