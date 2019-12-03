#include "stm32l476xx.h"
#include "setupHeaders.h"

void initADC()
{
	//Use GPIOA 1,2 for ADC, Independent, continuous conversio, 12bit resolution  
	//Ues GPIOE 12,13,14,15 for the IR sensors 

////Enable ADC CLK
	RCC->AHB2ENR  |= RCC_AHB2ENR_ADCEN;
////Resets ADC Interface
	RCC->AHB2RSTR	|=  RCC_AHB2RSTR_ADCRST;		 
	(void)RCC->AHB2RSTR; 												//Short delay
	RCC->AHB2RSTR	&= ~RCC_AHB2RSTR_ADCRST;
	
////Enable GPIOE and A CLK  [GPIOA is already enabled in initLCD] 
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN; 		
	
////ADC Pin init - GPIOA pins 1 & 2 
	GPIOA->MODER |=  3U<<(2*1) | 3U<<(2*2);  		//Mode 11 = Analog
	GPIOA->PUPDR &= ~( 3U<<(2*1) | 3U<<(2*2)); 	//No pull-up, no pull-down
	GPIOA->ASCR |= GPIO_ASCR_EN_1 | GPIO_ASCR_EN_2;	//Connect GPIOA pins 1 & 2 to the ADC input
	
////ADC 1 specific enables 
	//EN internal voltage booster to correct for analog sw resistance increase w/low voltage
	SYSCFG->CFGR1 |= SYSCFG_CFGR1_BOOSTEN; 
	

////V_REFINT enable
//	ADC123_COMMON->CCR |= ADC_CCR_VREFEN;  		//ENABLES Vbat channel for ADC to run off battery!!!!!!!!!!!!!!!!!!!!  pg153 of 3560
	
////ADC Clock Source: System Clock, PLLSAI1, PLLSAI2. Maximum ADC Clock: 80 MHz	
	//ADC CLK prescaler seutp
	ADC123_COMMON->CCR &= ~ADC_CCR_PRESC;   		//0000, Reset, input ADC clock not divided
	
	//ADC clock mode select
	ADC123_COMMON->CCR &= ~ADC_CCR_CKMODE;  		//HCLK = 80MHz
	ADC123_COMMON->CCR |=  ADC_CCR_CKMODE_0;		//HCLK/1 (Synchronous clock mode).

////ADC Operating mode 
	ADC123_COMMON->CCR &= ~ADC_CCR_DUAL; 				//Independent mode //pg 568 of 3560
	//ADC123_COMMON->CCR |= 6U;  // 00110: Regular simultaneous mode only
	
	
	
////ADC Wakeup 
	int wait_time;
	
	//Disbale ADC deep power down mode if in that state. DEEPPWD = 1: ADC in deep-power-down (default reset state)
	if ((ADC1->CR & ADC_CR_DEEPPWD) == ADC_CR_DEEPPWD)
		ADC1->CR &= ~ADC_CR_DEEPPWD; 
	
////EN ADC internal voltage regulator
	ADC1->CR |= ADC_CR_ADVREGEN;	
	
	//Delay for ADC internal voltage regulator start-up time. (T_ADCVREG_STUP) = 20us 
	wait_time = 20 * (80000000 / 1000000);
	while(wait_time != 0) 
		wait_time--;   
	
	
////Initialize ADC		
////ADC control register 1 (ADC_CR1)
	ADC1->CFGR &= 0100; 							//Set bits 3-4 and resolution to 10bit // ~ADC_CFGR_RES; // Resolution, (00 = 12-bit, 01 = 10-bit, 10 = 8-bit, 11 = 6-bit)
	ADC1->CFGR &= ~ADC_CFGR_ALIGN;   	//Right aligned data //Data Alignment (0 = Right alignment, 1 = Left alignment)
	ADC1->CFGR &= ~ADC_CFGR_CONT;     // ADC Single Conversion mode 		
	//External hardware trigger polarity
	//00: Disabled [software trigger] | 01: Rising edge | 10: Falling edge | 11: Rising and Falling edge
	ADC1->CFGR &= ~ADC_CFGR_EXTEN; //Hardware Trigger detection disabled, software used 
	
////ADC regular sequence register 1 (ADC_SQR1)
	ADC1->SQR1 &= ~ADC_SQR1_L;       	//1 ADC Conversion  //0000: 1 conversion in the regular channel conversion sequence	
	//Specificy the channel number of the 1st conversion in regular sequence
	//SQ1[4:0] bits (1st conversion in regular sequence)					
	ADC1->SQR1 &= ~ADC_SQR1_SQ1;
	ADC1->SQR1 |=  ( 6U << 6 );  //WHY THE HELL ARE WE USING in6? Why aren't we using ADC123_IN1? // PA1: ADC12_IN6 !!!!!!!!!!!!!!!
	
////ADC Differential mode Selection Register
	ADC1->DIFSEL &= ~ADC_DIFSEL_DIFSEL_6;	//Single-ended/pin mode selected 			// Single-ended for PA1: ADC12_IN6 
	
////ADC Sample Time
	// This sampling time must be enough for the input voltage source to charge the embedded
	// capacitor to the input voltage level.
	// Software is allowed to write these bits only when ADSTART=0 and JADSTART=0
	//   000: 2.5 ADC clock cycles      001: 6.5 ADC clock cycles
	//   010: 12.5 ADC clock cycles     011: 24.5 ADC clock cycles
	//   100: 47.5 ADC clock cycles     101: 92.5 ADC clock cycles
	//   110: 247.5 ADC clock cycles    111: 640.5 ADC clock cycles	
	//ADC_SMPR3_SMP5 = Channel 5 Sample time selection
	//Sample time for first channel, NOTE: These bits must be written only when ADON=0. 
	ADC1->SMPR1  &= ~ADC_SMPR1_SMP6;      //Clear ch6 ADC Sample Time setting 
	ADC1->SMPR1  |= 3U << 18;             //Set ch6 sample time to: 0011: 24.5 ADC clock cycles. [24.5*80MHz = 0.3 us]
	
////Enable ADC1     
	ADC1->CR |= ADC_CR_ADEN;  	//EN conversion	
	while((ADC1->ISR & ADC_ISR_ADRDY) == 0); 
}
