################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/colas.c \
../src/funcionesPCB.c \
../src/kernel.c \
../src/kernelSocket.c \
../src/manejoCPU.c \
../src/manejoIO.c \
../src/manejoSemaforos.c \
../src/planificador_corto_plazo.c \
../src/planificador_largo_plazo.c 

OBJS += \
./src/colas.o \
./src/funcionesPCB.o \
./src/kernel.o \
./src/kernelSocket.o \
./src/manejoCPU.o \
./src/manejoIO.o \
./src/manejoSemaforos.o \
./src/planificador_corto_plazo.o \
./src/planificador_largo_plazo.o 

C_DEPS += \
./src/colas.d \
./src/funcionesPCB.d \
./src/kernel.d \
./src/kernelSocket.d \
./src/manejoCPU.d \
./src/manejoIO.d \
./src/manejoSemaforos.d \
./src/planificador_corto_plazo.d \
./src/planificador_largo_plazo.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/utnso/workspace/tp-2014-1c-out-of-range/commons" -O0 -g3 -Wall -lrt -pthread -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


