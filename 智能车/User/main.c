#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "MPU6050.h"
#include "inv_mpu.h"
#include "exti.h"
#include "motor.h"
#include "encoder.h"
#include "pwm.h"
#include "ir.h"
#include "Serial.h"
#include "Ultrasound.h"

float Pitch,Roll,Yaw;						//角度
short gyrox,gyroy,gyroz;				//陀螺仪--角速度
short aacx,aacy,aacz;						//加速度
int Encoder_Left,Encoder_Right;	//编码器数据（速度）

int PWM_MAX=7200,PWM_MIN=-7200;	//PWM限幅变量
int MOTO1,MOTO2;								//电机装载变量

char Mode = 1;//1：手动控制 2;红外寻迹 3：停止
int ir_PWM;

extern int Vertical_out,Velocity_out,Turn_out;
extern float Med_Angle;	
extern float Target_Speed;

int main(void)
{
	
	MPU6050_Init();
	MPU6050_DMP_Init();
	MPU6050_EXTI_Init();
	NVIC_Config();
	Motor_Init();
	Encoder_TIM3_Init();
	Encoder_TIM4_Init();
	PWM_Init();
	IR_Sensor_Init();
	GPIO_Config();
	EXTI_Config();
	while (1)
	{
				// 触发超声波传感器
		GPIO_SetBits(GPIOB, GPIO_Pin_1);
		Delay_us(10); // 10us的脉冲
		GPIO_ResetBits(GPIOB, GPIO_Pin_1);
		
		if (Mode == 2) {
		// 寻迹模式的代码
		uint8_t sensor_state = Read_IR_Sensors();
		
		// 根据传感器状态进行控制
		switch(sensor_state)
		{
				case 0x01:
					ir_PWM = -250;
						// 左转代码
						break;
				case 0x02:
					ir_PWM = -100;
						// 稍微左转代码
						break;
				case 0x04:
					ir_PWM = 0;
						// 直行代码
						break;
				case 0x08:
					ir_PWM = 10;
						// 稍微右转代码
						break;
				case 0x10:
					ir_PWM = 250;
						// 右转代码
						break;
				default:
					ir_PWM = 0;
						// 未检测到线的代码
						break;
		}
	}
}

}
