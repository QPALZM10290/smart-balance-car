#include "Ultrasound.h"

extern char Mode;

void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // ʹ�� GPIO ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    // ���� PB1 Ϊ���������Trigger��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    // ���� PB0 Ϊ�������루Echo��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

// EXTI0 �жϴ������
void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        // �����жϣ���⵽�ϰ��
        Mode = 3;
        // ����жϱ�־
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

