################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/class/IMGPIO.cpp \
../src/class/PWM.cpp 

OBJS += \
./src/class/IMGPIO.o \
./src/class/PWM.o 

CPP_DEPS += \
./src/class/IMGPIO.d \
./src/class/PWM.d 


# Each subdirectory must supply rules for building sources it contributes
src/class/%.o: ../src/class/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


