#include "ir.h"


// ��ʼ�����⴫��������
void IR_Sensor_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // ʹ��GPIOʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);
    
    // ��������Ϊ����ģʽ
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // ��������ģʽ
    
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

// ��ȡ���⴫������״̬
uint8_t Read_IR_Sensors(void)
{
    uint8_t sensor_state = 0;
    
    // ��ȡÿ����������״̬���ϲ�Ϊһ���ֽ�
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
