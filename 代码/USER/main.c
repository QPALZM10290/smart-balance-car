/*
B站：天下行走?_?（B站起的名字在MDK里显示不全，若要了解，在大文件的word文档的最后可以找到）		
知乎：天下行走							
CSDN：技术创造无限可能				
闲鱼：抉择之刃银

新创建QQ群：822263013
有兴趣的同学请加群交流。
*/

/*
【未推导的串级PID控制器】版本的平衡小车控制。
现在只需要在"control.c"里面修改机械中值角度就可以了。
*/




#include "stm32f10x.h"
#include "sys.h" 

float Pitch,Roll,Yaw;						//角度
short gyrox,gyroy,gyroz;				//陀螺仪--角速度
short aacx,aacy,aacz;						//加速度
int Encoder_Left,Encoder_Right;	//编码器数据（速度）

int PWM_MAX=7200,PWM_MIN=-7200;	//PWM限幅变量
int MOTO1,MOTO2;								//电机装载变量

extern int Vertical_out,Velocity_out,Turn_out;
extern float Med_Angle;	
extern float Target_Speed;

int main(void)	
{
	delay_init();
	NVIC_Config();
	uart1_init(115200);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE); 
	
	
	MPU_Init();
	mpu_dmp_init();
	
	Encoder_TIM3_Init();
	Encoder_TIM4_Init();
	Motor_Init();
  PWM_Init();
	
  while(1)	
	{
  int PWM_out;
			//1.采集编码器数据&MPU6050角度信息。
			Encoder_Left=-Read_Speed(3);//电机是相对安装，刚好相差180度，为了编码器输出极性一致，就需要对其中一个取反。
			Encoder_Right=Read_Speed(4);
			
			mpu_dmp_get_data(&Pitch,&Roll,&Yaw);			//角度
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//陀螺仪
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//加速度
			//2.将数据压入闭环控制中，计算出控制输出量。
			
			/*
			【一】
			问：
				当我在小车前侧绑一块小铁块，这会使得机械中值后倾，=-27度，然后我将车子扶在机械中值的角度位置然后开机，但车子一开机就往前跑。为什么？
			答：
				问题分析：
								起始速度偏差=0（因为没有动轮子呀）——>外环输出=0（即内环期望角度=0）
								But：开局实际角度= -27度——>开局内环输出就等于(-27-0)*(-1) = +27  //Kp为负数，这里设为-1
								即根本是因为开局时 外环输出！=机械中值(这里机械中值可以等效说成实际角度，但不是任何时候都可以等效说成的。譬如我开机时小车不摆在机械中值位置时就不能等效说成。)
								=====>>>>所以开局时车子肯定往前跑！！！			
				解决思想：
								起始Target=Real就可以了。
				解决方法：
								测机械中值譬如 = -27度，则使得内环期望角度=外环输出 + 机械中值。	
								
			【二】
			若：外环输出==机械中值，即开局速度偏差=0时，机械中值=0则外环输出=0，即内环输入=0。
			又有内环反馈=0，所以这时候开局内环输出就等于(0-0)*(-1) = 0===>车子必然直立静止在原地。
			
			【三】
			若：外环输出！=机械中值，即开局速度偏差=0时，机械中值!=0，但我开局不把车子摆在机械中值位置。譬如举例当机械中值=-27度，我开机将车子实际角度摆在0度位置。则此时
			速度偏差=0则外环输出=0，即内环输入=0。
			又有内环反馈=0===>理论上小车直立静止，BUT！车子根本不在机械中值位置，又谈何直立静止，车子会根据重心向前倒下，直立环立刻发挥作用-->
			-->若小铁快非常非常轻，还有可能救回来；若铁块不轻，则必然车子一直不断向前跑不会停下；若小铁块过重，系统来不及响应，车子会直接向前倒下；
			这，就是结果。
			*/			
			Velocity_out=Velocity(Target_Speed,Encoder_Left,Encoder_Right);	//速度环
			Vertical_out=Vertical(Velocity_out+Med_Angle,Pitch,gyroy);			//直立环
			Turn_out=Turn(gyroz);																						//转向环
			
			PWM_out=Vertical_out;//最终输出
			//3.把控制输出量加载到电机上，完成最终的的控制。
			MOTO1=PWM_out-Turn_out;//左电机
			MOTO2=PWM_out+Turn_out;//右电机
			Limit(&MOTO1,&MOTO2);	 //PWM限幅			
			Load(MOTO1,MOTO2);		 //加载到电机上。
			
//			Stop(&Med_Angle,&Pitch);
			
		
	
	} 	
}



