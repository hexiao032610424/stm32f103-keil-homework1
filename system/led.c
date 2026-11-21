#include "stm32f10x.h"
#include "braod_defind.h"


	
void LED_Flash_Mode1(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	Delay_ms_Mode1(250);
	GPIO_SetBits(GPIOB,GPIO_Pin_0);
	Delay_ms_Mode1(250);
}

void LED_Flash_Mode2(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	Delay_ms_Mode2(250);
	GPIO_SetBits(GPIOB,GPIO_Pin_0);
	Delay_ms_Mode2(250);
}

void LED_Flash_TIM1(void)		//定时器计数//
{
	static uint16_t cnt=0;
	if(TIM_GetFlagStatus(TIM2,TIM_FLAG_Update)==SET)
	{
		TIM_ClearFlag(TIM2,TIM_FLAG_Update);
		cnt++;
		if(cnt>=500)
		{
			cnt = 0;
            if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_0))
			{
                GPIO_ResetBits(GPIOB,GPIO_Pin_0);
			}
            else
			{
                GPIO_SetBits(GPIOB,GPIO_Pin_0); 
			}
		}
	}
		
}

void LED_Flash_TIM2(void)		//定时器方波//
{
	GPIO_InitTypeDef B0;
	B0.GPIO_Mode=GPIO_Mode_AF_PP;
	B0.GPIO_Pin= GPIO_Pin_0;
	B0.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&B0);
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	
	TIM_TimeBaseInitTypeDef t;		//使能TIM3//
	t.TIM_Prescaler=7200-1;
    t.TIM_Period=10000-1;
    t.TIM_CounterMode=TIM_CounterMode_Up;
    t.TIM_ClockDivision=TIM_CKD_DIV1;
    t.TIM_RepetitionCounter=0;
    TIM_TimeBaseInit(TIM3,&t);
	
	TIM_OCInitTypeDef op;		//使能CH3，输出方波//
	op.TIM_OCMode=TIM_OCMode_PWM1;
    op.TIM_OutputState=TIM_OutputState_Enable;
    op.TIM_OCPolarity=TIM_OCPolarity_High;
    op.TIM_Pulse=5000;
    TIM_OC3Init(TIM3,&op);
    TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_Cmd(TIM3, ENABLE);
}
