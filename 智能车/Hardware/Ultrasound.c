#include "Ultrasound.h"

extern char Mode;

void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // 使能 GPIO 时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    // 配置 PB1 为推挽输出（Trigger）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    // 配置 PB0 为浮空输入（Echo）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

// EXTI0 中断处理程序
void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        // 处理中断（检测到障碍物）
        Mode = 3;
        // 清除中断标志
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

