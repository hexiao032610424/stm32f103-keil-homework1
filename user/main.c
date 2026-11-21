#include "stm32f10x.h"
#include "braod_defind.h"
#include "led.h"
#include "button.h"

int main(void)
{
	braod_defind();
	LED_Flash_TIM2();
	while(1)
	{
		if(LED_Mode_Flag==0)
		{			
			EXTI_DISANBLE();
			LED_ToGPIO();        
			LED_Flash_Mode2();
		}
			if(LED_Mode_Flag==1)
		{
			EXTI_DISANBLE();
			LED_ToPWM();
		}
		if(LED_Mode_Flag==2)
		{
			EXTI_ENANBLE();
			LED_ToGPIO();
		}

		//LED_Flash_Mode1();
		//LED_Flash_Mode2();
		//LED_Flash_TIM1();
	}
}
