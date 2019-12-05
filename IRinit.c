#include "stm32l476xx.h"
#include "setupHeaders.h"

////Ues GPIOE 12,13,14,15 for the IR sensors 

volatile uint32_t msTicks;	//Used for counting # of sysTick interrupts 

////SysTick Interrupt Handler
void SysTick_Handler(void){
	msTicks++;
}


////Initlize GPIOE 12-15 for IR sensor operation 
void PE_Init(void) {
/* Enable GPIOs clock */ 	
	RCC->AHB2ENR |=   RCC_AHB2ENR_GPIOEEN;

	//GPIO Mode: Input(00, reset), Output(01), AlterFunc(10), Analog(11, reset)
	GPIOE->MODER &= ~(3U<<(2*15) | 3U<<28 | 3U<<26 | 3U<<24);  
	GPIOE->MODER |= 1U<<(2*15) | 1U<<28 | 1U<<26 | 1U<<24;      //Output(01)

	//GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	GPIOE->OSPEEDR &= ~(3U<<(2*15) | 3U<<28 | 3U<<26 | 3U<<24);
	GPIOE->OSPEEDR |= 3U<<(2*15) | 3U<<28 | 3U<<26 | 3U<<24;   	//High speed (11)
	
	//GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	GPIOE->OTYPER &= ~(1U<<15 | 1U<<14 | 1U<<13 | 1U<<12);      //Push-pull (0)

	//GPIO Pull up/Pull down: No pull-up/pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	GPIOE->PUPDR   &= ~(3U<<(2*15) | 3U<<28 | 3U<<26 | 3U<<24);  //No pull-up, no pull-down (00)
}


////Initialize SysTick for 1ms interval 
void SysTick_Init(void){
	
	//SysTick Control and Status Register
	SysTick->CTRL = 0;										//Disable SysTick IRQ and SysTick Counter
	
	//SysTick Reload Value Register
	SysTick->LOAD = 10000 - 1;    				//~1ms for 80MHz CLK 
	
	//SysTick Current Value Register
	SysTick->VAL = 0;

	NVIC_SetPriority(SysTick_IRQn, 1);		//Set Priority to 1
	NVIC_EnableIRQ(SysTick_IRQn);					//Enable EXTI0_1 interrupt in NVIC

	//Enables SysTick exception request
	// 1 = counting down to zero asserts the SysTick exception request
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	
	//Select processor clock
	SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;	//CLKSOURCE = 1, processor clock used [80MHz] 
	
	//Enable SysTick IRQ and SysTick Timer
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  
}

////Generates a delay in ms
void delay (uint32_t T)
{
  msTicks = 0;
	
  while (msTicks< T);
}

////Master caller for setup 
void initIR()
{
	PE_Init();						//Initilize GOPIE for IR sensors 
	SysTick_Init();				//Setup sysTick for 1ms duration 
}
