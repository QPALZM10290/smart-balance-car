#include "ir.h"


// 初始化红外传感器引脚
void IR_Sensor_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // 使能GPIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);
    
    // 配置引脚为输入模式
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // 上拉输入模式
    
    GPIO_InitStructure.GPIO_Pin = IR_SENSOR_1_PIN;
    GPIO_Init(IR_SENSOR_1_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = IR_SENSOR_2_PIN;
    GPIO_Init(IR_SENSOR_2_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = IR_SENSOR_3_PIN;
    GPIO_Init(IR_SENSOR_3_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = IR_SENSOR_4_PIN;
    GPIO_Init(IR_SENSOR_4_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = IR_SENSOR_5_PIN;
    GPIO_Init(IR_SENSOR_5_PORT, &GPIO_InitStructure);
}

// 读取红外传感器的状态
uint8_t Read_IR_Sensors(void)
{
    uint8_t sensor_state = 0;
    
    // 读取每个传感器的状态并合并为一个字节
    if (GPIO_ReadInputDataBit(IR_SENSOR_1_PORT, IR_SENSOR_1_PIN) == Bit_RESET)
        sensor_state |= 0x01;
    if (GPIO_ReadInputDataBit(IR_SENSOR_2_PORT, IR_SENSOR_2_PIN) == Bit_RESET)
        sensor_state |= 0x02;
    if (GPIO_ReadInputDataBit(IR_SENSOR_3_PORT, IR_SENSOR_3_PIN) == Bit_RESET)
        sensor_state |= 0x04;
    if (GPIO_ReadInputDataBit(IR_SENSOR_4_PORT, IR_SENSOR_4_PIN) == Bit_RESET)
        sensor_state |= 0x08;
    if (GPIO_ReadInputDataBit(IR_SENSOR_5_PORT, IR_SENSOR_5_PIN) == Bit_RESET)
        sensor_state |= 0x10;
    
    return sensor_state;
}
