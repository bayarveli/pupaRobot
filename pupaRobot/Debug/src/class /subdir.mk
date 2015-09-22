################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/class\ /IMGPIO.cpp \
../src/class\ /PWM.cpp 

OBJS += \
./src/class\ /IMGPIO.o \
./src/class\ /PWM.o 

CPP_DEPS += \
./src/class\ /IMGPIO.d \
./src/class\ /PWM.d 


# Each subdirectory must supply rules for building sources it contributes
src/class\ /IMGPIO.o: ../src/class\ /IMGPIO.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/class /IMGPIO.d" -MT"src/class\ /IMGPIO.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/class\ /PWM.o: ../src/class\ /PWM.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/class /PWM.d" -MT"src/class\ /PWM.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


