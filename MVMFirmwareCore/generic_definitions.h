#pragma once
#define DATA_BUFFER_SIZE 4
#include <stdint.h>
typedef enum { PWM_PV1 } hw_pwm;
typedef enum { GPIO_PV2, GPIO_BUZZER, GPIO_LED, GPIO_RELEALLARM } hw_gpio;
typedef enum { PRESSURE_VALVE, PRESSURE_PATIENT } t_pressure_selector;
typedef enum {  IIC_INVALID, 
				IIC_PS_0, 
				IIC_PS_1, 
				IIC_PS_2, 
				IIC_PS_3, 
				IIC_PS_4, 
				IIC_PS_5, 
				IIC_FLOW1, 
				IIC_FLOW2, 
				IIC_SUPERVISOR, 
				IIC_EEPROM, 
				IIC_MUX,
				IIC_GENERAL_CALL_SENSIRION} t_i2cdevices;
typedef struct
{
	t_i2cdevices t_device;
	uint8_t address;
	int8_t muxport; //USE -1 to indicate ANY
} t_i2cdev;


#define __ERROR_INPUT_PRESSURE_LOW 0
#define __ERROR_INPUT_PRESSURE_HIGH 1
#define __ERROR_INSIDE_PRESSURE_LOW 2
#define __ERROR_INSIDE_PRESSURE_HIGH 3
#define __ERROR_BATTERY_LOW 4
#define __ERROR_LEAKAGE 5
#define __ERROR_FULL_OCCLUSION 6
#define __ERROR_PARTIAL_OCCLUSION 7
#define __ERROR_ALARM_PI 29
#define __ERROR_WDOG_PI 30
#define __ERROR_SYSTEM_FALIURE 31