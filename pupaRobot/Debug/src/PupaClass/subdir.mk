################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/PupaClass/gpioLib.cpp \
../src/PupaClass/pwmLib.cpp \
../src/PupaClass/serialLib.cpp 

OBJS += \
./src/PupaClass/gpioLib.o \
./src/PupaClass/pwmLib.o \
./src/PupaClass/serialLib.o 

CPP_DEPS += \
./src/PupaClass/gpioLib.d \
./src/PupaClass/pwmLib.d \
./src/PupaClass/serialLib.d 


# Each subdirectory must supply rules for building sources it contributes
src/PupaClass/%.o: ../src/PupaClass/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


