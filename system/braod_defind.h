#ifndef __BRAOD_DEFIND_H
#define __BRAOD_DEFIND_H

#include "stm32f10x.h"


extern volatile uint8_t LED_Mode_Flag;
extern volatile uint8_t LED_Debounce_Flag;

void braod_defind(void);
void Delay_ms_Mode1(uint32_t count);
void Delay_ms_Mode2(uint32_t count);
void LED_Flash_TIM2(void);
void EXTI_ENANBLE(void);
void EXTI_DISANBLE(void);
void LED_ToGPIO(void);
void LED_ToPWM(void);
void TIM1_Debounce_ENABLE(void);

#endif
