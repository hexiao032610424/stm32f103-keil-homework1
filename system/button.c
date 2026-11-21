#include "stm32f10x.h"
#include "braod_defind.h"


void TIM1_UP_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1, TIM_IT_Update)==SET) 
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
        TIM_ITConfig(TIM1, TIM_IT_Update, DISABLE);
        TIM_Cmd(TIM1, DISABLE);
		if(LED_Debounce_Flag==0)
		{	
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==SET&&LED_Mode_Flag!=2)
			{
			LED_Mode_Flag++;
			}
			else
			{
			LED_Mode_Flag=0;
			}
		}
		if(LED_Debounce_Flag==1)
		{
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==SET&&LED_Mode_Flag!=0)
			{
				LED_Mode_Flag--;
			}
			else
			{
				LED_Mode_Flag=2;
			}
		}
		if(LED_Debounce_Flag==2)
		{
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

void EXTI2_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line2)==SET) 
	{
		LED_Debounce_Flag=2;
		TIM1_Debounce_ENABLE();
        EXTI_ClearITPendingBit(EXTI_Line2);
    }
}

void EXTI0_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line0)==SET) 
	{
		LED_Debounce_Flag=0;
		TIM1_Debounce_ENABLE();
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

void EXTI1_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line1)==SET) 
	{
		LED_Debounce_Flag=1;
		TIM1_Debounce_ENABLE();
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}

/*void Button_Mode_Change(void)
{
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==SET&&LED_Mode_Flag!=2)
	{
		LED_Mode_Flag++;
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==SET)
		{
			
		}
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==SET&&LED_Mode_Flag==2)
	{
		LED_Mode_Flag=0;
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==SET)
		{
			
		}
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==SET&&LED_Mode_Flag!=0)
	{
		LED_Mode_Flag--;LED_Mode_Flag=2;
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==SET)
		{
			
		}
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)==SET&&LED_Mode_Flag==0)
	{
		LED_Mode_Flag=2;
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==SET)
		{
			
		}
	}
}*/

/*void Button_LED_Change(void)
{
	EXTI1_IRQHandler();
}*/
//触发中断后直接进中断程序，不用这个//
