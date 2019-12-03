#ifndef __STM32L476G_DISCOVERY_setupHeaders_H
#define __STM32L476G_DISCOVERY_setupHeaders_H

#include "stm32l476xx.h"

void LCD_Initialization(void);
void initADC(void);
void initIR(void);
void delay(uint32_t T);

#endif /* __STM32L476G_DISCOVERY_setupHeaders_H */
