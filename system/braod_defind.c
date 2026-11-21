#include "stm32f10x.h"

void TIM2_1ms_Init(void)
{
    TIM_TimeBaseInitTypeDef t2;
    t2.TIM_Prescaler = 72 - 1;   
    t2.TIM_Period = 1000 - 1;     
    t2.TIM_CounterMode = TIM_CounterMode_Up;
    t2.TIM_ClockDivision = TIM_CKD_DIV1;
    t2.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &t2);
    TIM_Cmd(TIM2, ENABLE);
}

void TIM1_Debounce_Init(void)
{
	NVIC_InitTypeDef nt;				
	nt.NVIC_IRQChannel=TIM1_UP_IRQn;
	nt.NVIC_IRQChannelPreemptionPriority=1;
	nt.NVIC_IRQChannelSubPriority=0;
	nt.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&nt);
	
    TIM_TimeBaseInitTypeDef t1;
    t1.TIM_Prescaler = 72 - 1;   
    t1.TIM_Period = 20000 - 1;     
    t1.TIM_CounterMode = TIM_CounterMode_Up;
    t1.TIM_ClockDivision = TIM_CKD_DIV1;
    t1.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &t1);
    TIM_Cmd(TIM1, DISABLE);
	
	
}

void TIM1_Debounce_ENABLE(void)
{
	TIM_Cmd(TIM1, DISABLE);
    TIM_SetCounter(TIM1, 0);
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM1, ENABLE); 
}

volatile uint8_t LED_Mode_Flag=0;
volatile uint8_t LED_Debounce_Flag=0;		//防抖标志位，0=模式加，1=模式减，2=切电平//

void braod_defind(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2|RCC_APB1Periph_TIM3, ENABLE);
	
	GPIO_InitTypeDef B0;				//使能B0
	B0.GPIO_Mode=GPIO_Mode_Out_PP;
	B0.GPIO_Pin= GPIO_Pin_0;
	B0.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&B0);
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	
	GPIO_InitTypeDef A0;				//使能A0
	A0.GPIO_Mode=GPIO_Mode_IPD;
	A0.GPIO_Pin= GPIO_Pin_0;
	A0.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&A0);
	
	NVIC_InitTypeDef n0;				//A0中断
	n0.NVIC_IRQChannel=EXTI0_IRQn;
	n0.NVIC_IRQChannelPreemptionPriority=3;
	n0.NVIC_IRQChannelSubPriority=0;
	n0.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&n0);
	
	GPIO_InitTypeDef A1;				//使能A1
	A1.GPIO_Mode=GPIO_Mode_IPD;
	A1.GPIO_Pin= GPIO_Pin_1;
	A1.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&A1);
		
	NVIC_InitTypeDef n1;				//A1中断
	n1.NVIC_IRQChannel=EXTI1_IRQn;
	n1.NVIC_IRQChannelPreemptionPriority=4;
	n1.NVIC_IRQChannelSubPriority=0;
	n1.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&n1);
	
	GPIO_InitTypeDef A2;				//使能A2
	A2.GPIO_Mode=GPIO_Mode_IPD;
	A2.GPIO_Pin= GPIO_Pin_2;
	A2.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&A2);
	
	NVIC_InitTypeDef n2;				//A2中断
	n2.NVIC_IRQChannel=EXTI2_IRQn;
	n2.NVIC_IRQChannelPreemptionPriority=2;
	n2.NVIC_IRQChannelSubPriority=0;
	n2.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&n2);
	
	/*NVIC_InitTypeDef n;			我也不知档笔崩为什么写了TIM2，先注释掉把
	n.NVIC_IRQChannel=TIM2_IRQn;
	n.NVIC_IRQChannelPreemptionPriority=2;
	n.NVIC_IRQChannelSubPriority=0;
	n.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&n);*/
	
	
	EXTI_InitTypeDef exti1;				//三个A的中断
	exti1.EXTI_Line=EXTI_Line1;
	exti1.EXTI_Mode=EXTI_Mode_Interrupt;
	exti1.EXTI_Trigger=EXTI_Trigger_Rising;
	exti1.EXTI_LineCmd=ENABLE;
	EXTI_Init(&exti1);
	
	EXTI_InitTypeDef exti0;
	exti0.EXTI_Line=EXTI_Line0;
	exti0.EXTI_Mode=EXTI_Mode_Interrupt;
	exti0.EXTI_Trigger=EXTI_Trigger_Rising;
	exti0.EXTI_LineCmd=ENABLE;
	EXTI_Init(&exti0);
	
	EXTI_InitTypeDef exti2;
	exti2.EXTI_Line=EXTI_Line2;
	exti2.EXTI_Mode=EXTI_Mode_Interrupt;
	exti2.EXTI_Trigger=EXTI_Trigger_Rising;
	exti2.EXTI_LineCmd=DISABLE;
	EXTI_Init(&exti2);
	
	//唐人配了总线，忘了写中断
	
	TIM2_1ms_Init();
	TIM1_Debounce_Init();
} 

void LED_ToGPIO(void)
{
    GPIO_InitTypeDef g;
    TIM_Cmd(TIM3,DISABLE);
    g.GPIO_Pin=GPIO_Pin_0;
    g.GPIO_Mode=GPIO_Mode_Out_PP;
    g.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&g);
}

void LED_ToPWM(void)
{
    GPIO_InitTypeDef g;
    g.GPIO_Pin=GPIO_Pin_0;
    g.GPIO_Mode=GPIO_Mode_AF_PP;
    g.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&g);
    TIM_Cmd(TIM3,ENABLE);
}

void EXTI_ENANBLE(void)
{
	EXTI_InitTypeDef exti2;
	exti2.EXTI_Line=EXTI_Line2;
	exti2.EXTI_Mode=EXTI_Mode_Interrupt;
	exti2.EXTI_Trigger=EXTI_Trigger_Rising;
	exti2.EXTI_LineCmd=ENABLE;
	EXTI_Init(&exti2);
}

void EXTI_DISANBLE(void)
{
	EXTI_InitTypeDef exti2;
	exti2.EXTI_Line=EXTI_Line2;
	exti2.EXTI_Mode=EXTI_Mode_Interrupt;
	exti2.EXTI_Trigger=EXTI_Trigger_Rising;
	exti2.EXTI_LineCmd=DISABLE;
	EXTI_Init(&exti2);
}

void Delay_ms_Mode2(uint32_t count)			//定时器延时//
{
    while (count--) {
        TIM_SetCounter(TIM2, 0);
        TIM_ClearFlag(TIM2, TIM_FLAG_Update);
        while (TIM_GetFlagStatus(TIM2, TIM_FLAG_Update) == RESET);
    }
}

void Delay_ms_Mode1(uint32_t count)			//循环延时//
{
    volatile uint32_t i;          
    for (i = 0; i < count; i++) {
		volatile uint32_t k = 65;
		volatile uint32_t j = 100;
		while(k>0)
		{
			while(j>0)
			{
				j--;
			}
			k--;
			j=100;
		}
    }
}

/*这个循环每跑一次是11此计算，由汇编语言得到*/
