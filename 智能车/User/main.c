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

float Pitch,Roll,Yaw;						//�Ƕ�
short gyrox,gyroy,gyroz;				//������--���ٶ�
short aacx,aacy,aacz;						//���ٶ�
int Encoder_Left,Encoder_Right;	//���������ݣ��ٶȣ�

int PWM_MAX=7200,PWM_MIN=-7200;	//PWM�޷�����
int MOTO1,MOTO2;								//���װ�ر���

char Mode = 1;//1���ֶ����� 2;����Ѱ�� 3��ֹͣ
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
				// ����������������
		GPIO_SetBits(GPIOB, GPIO_Pin_1);
		Delay_us(10); // 10us������
		GPIO_ResetBits(GPIOB, GPIO_Pin_1);
		
		if (Mode == 2) {
		// Ѱ��ģʽ�Ĵ���
		uint8_t sensor_state = Read_IR_Sensors();
		
		// ���ݴ�����״̬���п���
		switch(sensor_state)
		{
				case 0x01:
					ir_PWM = -250;
						// ��ת����
						break;
				case 0x02:
					ir_PWM = -100;
						// ��΢��ת����
						break;
				case 0x04:
					ir_PWM = 0;
						// ֱ�д���
						break;
				case 0x08:
					ir_PWM = 10;
						// ��΢��ת����
						break;
				case 0x10:
					ir_PWM = 250;
						// ��ת����
						break;
				default:
					ir_PWM = 0;
						// δ��⵽�ߵĴ���
						break;
		}
	}
}

}
