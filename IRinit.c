#include "stm32l476xx.h"
#include "setupHeaders.h"

uint32_t msTicks;

////SysTick Interrupt Handler
void SysTick_Handler(void){
	msTicks++;
}


////Initlize GPIOE 12-15 for IR sensor operation 
void PE_Init(void) {
/* Enable GPIOs clock */ 	
	RCC->AHB2ENR |=   RCC_AHB2ENR_GPIOEEN;
	
	//////////////////////////////////////////////////////////////////////////////////////////
	// PE8 and PE15
	//////////////////////////////////////////////////////////////////////////////////////////
	// GPIO Mode: Input(00, reset), Output(01), AlterFunc(10), Analog(11, reset)
	GPIOE->MODER &= ~(3U<<(2*15));  
	GPIOE->MODER |= 1U<<(2*15);      //  Output(01)

	GPIOE->MODER &= ~(3U<<(2*8));  
	GPIOE->MODER |= 1U<<(2*8);      //  Output(01)

	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	GPIOE->OSPEEDR &= ~(3U<<(2*15));
	GPIOE->OSPEEDR |=   3U<<(2*15);  // High speed

	GPIOE->OSPEEDR &= ~(3U<<(2*8));
	GPIOE->OSPEEDR |=   3U<<(2*8);  // High speed

	
	// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	GPIOE->OTYPER &= ~(1U<<15);       // Push-pull
	GPIOE->OTYPER &= ~(1U<<8);       // Push-pull

	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	GPIOE->PUPDR   &= ~(3U<<(2*15));  // No pull-up, no pull-down
	GPIOE->PUPDR   &= ~(3U<<(2*8));  // No pull-up, no pull-down
}


// Initialize SysTick	
void SysTick_Init(void){
	
	//  SysTick Control and Status Register
	SysTick->CTRL = 0;										// Disable SysTick IRQ and SysTick Counter
	
	// SysTick Reload Value Register
	SysTick->LOAD = 1000 - 1;    // 1ms, Default clock
	
	// SysTick Current Value Register
	SysTick->VAL = 0;

	NVIC_SetPriority(SysTick_IRQn, 1);		// Set Priority to 1
	NVIC_EnableIRQ(SysTick_IRQn);					// Enable EXTI0_1 interrupt in NVIC

	// Enables SysTick exception request
	// 1 = counting down to zero asserts the SysTick exception request
	// 0 = counting down to zero does not assert the SysTick exception request
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	
	// Select processor clock
	// If CLKSOURCE = 0, the external clock is used. The frequency of SysTick clock is the frequency of the AHB clock divided by 8.
	// If CLKSOURCE = 1, the processor clock is used.
	SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;		
	
	// Enable SysTick IRQ and SysTick Timer
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  
}

////Delay in ms
void delay (uint32_t T)
{
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < T);
	
	msTicks = 0;
}

////Master caller for setup 
void initIR()
{
	PE_Init();						//Initilize GOPIE for IR sensors 
	SysTick_Init();				//Setup sysTick for 1ms duration 
}
