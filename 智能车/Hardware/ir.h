#ifndef IR_H_
#define IR_H_

#include "stm32f10x.h"

// 定义红外传感器的引脚
#define IR_SENSOR_1_PIN  GPIO_Pin_13
#define IR_SENSOR_1_PORT GPIOC
#define IR_SENSOR_2_PIN  GPIO_Pin_14
#define IR_SENSOR_2_PORT GPIOC
#define IR_SENSOR_3_PIN  GPIO_Pin_15
#define IR_SENSOR_3_PORT GPIOC
#define IR_SENSOR_4_PIN  GPIO_Pin_4
#define IR_SENSOR_4_PORT GPIOA
#define IR_SENSOR_5_PIN  GPIO_Pin_5
#define IR_SENSOR_5_PORT GPIOA

// 函数声明
void IR_Sensor_Init(void);
uint8_t Read_IR_Sensors(void);

#endif /* IR_H_ */
