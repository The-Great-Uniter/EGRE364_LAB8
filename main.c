#include "stm32l476xx.h"
#include "LCD_structures.h"
#include "setupHeaders.h"

////Sensor data storage vars 
volatile uint32_t result, LLresult, LCresult, RCresult, RRresult;


////Interrupt Handlers
//Interrupt Handler for ADC 1/2 
void ADC1_2_IRQHandler(void)
{
	NVIC_ClearPendingIRQ(ADC1_2_IRQn);
	
	//ADC End of Conversion (EOC)
	if ((ADC1->ISR & ADC_ISR_EOC) == ADC_ISR_EOC) {
		ADC1->ISR |= ADC_ISR_EOC;	//Cear by writing 1 to it or by reading the corresponding ADCx_JDRy register
	}
	
	//ADC End of Injected Sequence of Conversions  (JEOS)
	if ((ADC1->ISR & ADC_ISR_EOS) == ADC_ISR_EOS) {
		ADC1->ISR |= ADC_ISR_EOS;		//Cear JEOS by writing 1 to it.
	}
}


////Functions to convert sensor data into LCD readable commands 
//Converts a uint16_t number to int and splits it into 10's and 1's place
void ADCtoDisp(uint16_t result, int upper, int lower, int bar) 
{
	int intResult = result; 	//Cast to int 
	
	switch (intResult)
	{
		case 3000:			//MAX range 
			upper = 8; 		//Get digit for LCD position[0]; 10's place
			lower = 0;		//Get digit for LCD position[1]; 1's place
			bar = 0; 			//100%  of sensor range used 
			break; 
		case 2000:			
			upper = 7; 		//Get digit for LCD position[0]; 10's place
			lower = 0;		//Get digit for LCD position[1]; 1's place
			bar = 1; 			//75%  of sensor range used 
			break; 
		case 1000:			 
			upper = 6; 		//Get digit for LCD position[0]; 10's place
			lower = 0;		//Get digit for LCD position[1]; 1's place
			bar = 2; 			//50%  of sensor range used 
			break; 
		case 500:			 
			upper = 5; 		//Get digit for LCD position[0]; 10's place
			lower = 0;		//Get digit for LCD position[1]; 1's place
			bar = 2; 			//50%  of sensor range used 
			break; 
		case 250:			 
			upper = 4; 		//Get digit for LCD position[0]; 10's place
			lower = 0;		//Get digit for LCD position[1]; 1's place
			bar = 3; 			//25%  of sensor range used 
			break; 
		case 125:			 
			upper = 3; 		//Get digit for LCD position[0]; 10's place
			lower = 0;		//Get digit for LCD position[1]; 1's place
			bar = 3; 			//25%  of sensor range used 
			break; 
		case 75:			 
			upper = 2; 		//Get digit for LCD position[0]; 10's place
			lower = 0;		//Get digit for LCD position[1]; 1's place
			bar = 4; 			//0%  of sensor range used 
			break; 
		case 25:				//MIN range
			upper = 1; 		//Get digit for LCD position[0]; 10's place
			lower = 0;		//Get digit for LCD position[1]; 1's place
			bar = 4; 			//0%  of sensor range used 
			break; 
	}
}

//Converts a uint16_t number into to an int value corresponding to 'B' [2] or 'W' [21] on the LCD
int IRtoDisp(uint16_t IRresult) //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!MAY need to change input type!!!!!!!!!!!!!!!!!!!!!!
{
	if (IRresult == 1)
		return 2; 
	else
		return 1;
}


////LCD Update routine 
encoding characters_to_display[6] = {0};

//Decodes and sends char data to the LCD RAM
void LCDupdate()
{
	//LCD->SR |= LCD_SR_UDR; 	
	while ((LCD->SR&LCD_SR_UDR) != 0); 					//Wait for Update Display Request Bit
	
	//LCD->RAM[0] = 0xffffffff; 
	
	char2mem(digit_1, characters_to_display[0]);
	char2mem(digit_2, characters_to_display[1]);
	char2mem(digit_3, characters_to_display[2]);
	char2mem(digit_4, characters_to_display[3]);
	char2mem(digit_5, characters_to_display[4]);
	char2mem(digit_6, characters_to_display[5]);
	LCD->SR |= LCD_SR_UDR; 											//Request update display
	
	while ((LCD->SR&LCD_SR_UDD) == 0); 					//Wait for update display done
	
	LCD->CLR |= 1<<3; 													//
}


////Reads sensor data and sends results to LCD                      
void collector()
{
	int upper = 0, lower = 0, numBars = 0, LLsensor = 0, LCsensor = 0, RCsensor = 0, RRsensor = 0;
	
	//Starts ADC Conversion and collects the result 
	ADC1->CR |= ADC_CR_ADSTART;				
		while ( (ADC123_COMMON->CSR | ADC_CSR_EOC_MST) == 0);
		result = ADC1->DR;
	
	//IR sensor controller 
	int32_t counter = 0;
	int32_t threshold = 0x2000;
	
	GPIOE->MODER |= 1U<<(2*15) | 1U<<28 | 1U<<26 | 1U<<24; 	//Set pins 12-15 as Output(01)
	GPIOE->ODR |= 1U<<15 | 1U<<14 | 1U<<13 | 1U<<12;				//Set ODR pins high 
	delay(10);																							//Wait for 10ms 
	GPIOE->MODER &= ~(3U<<(2*15) | 3U<<28 | 3U<<26 | 3U<<24);//Set pins 12-15 as Input(00)
	
	//
	while (GPIOE->IDR & 0x8000) counter++;									
	
	//
	if (counter>threshold)										
		GPIOE->ODR |= 1U<<8;
	else 
		GPIOE->ODR &= ~(1U<<8);
	counter =0;
	//STILL NEED TO COLLECT THE DATA CORRECTLY 
	
	//Calls to convet raw sensor data into LCD interpretable commands 
	ADCtoDisp(result, upper, lower, numBars); 	//Convert uint16_t result to int and split into 10's and 1's place
	LLsensor = IRtoDisp(LLresult);		//Convert IR sensor input data to int corresponding to LCD char 'B' or 'W'
	LCsensor = IRtoDisp(LCresult);
	RCsensor = IRtoDisp(RCresult);
	RRsensor = IRtoDisp(RRresult);
	
	//Display current sensor readings on LCD
	characters_to_display[0] = numbers[upper];
	characters_to_display[1] = numbers[lower];
	characters_to_display[2] = alpha[LLsensor];
	characters_to_display[3] = alpha[LCsensor];
	characters_to_display[4] = alpha[RCsensor];
	characters_to_display[5] = alpha[RRsensor];
	//STILL NEED TO FILL LCD BARS BASED ON DISTANCE % OF RANGE SENSOR 
	LCDupdate();
}


////Initialize all components and read sensor inputs continuously
int main(void)
{
	System_Clock_Init();	//Start and initlize sys CLK
	LCD_Initialization();	//Initlize all LCD related registers and clocks
	initADC();						//Initlize all ADC related registers and clocks
	initIR();							//Initlize all IR sensor related registers and clocks
	//initInterrupt();			//Initlize all Interrupt related registers
	
	while(1){
	collector();					//'main' function; collects data and updates LCD
	}
  //EOP
}
