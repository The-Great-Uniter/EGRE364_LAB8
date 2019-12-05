#include "stm32l476xx.h"
#include "LCD_structures.h"
#include "setupHeaders.h"

////Sensor data storage vars 
volatile uint32_t result, LLresult, LCresult, RCresult, RRresult;
int upper,lower,numBars; 

////Interrupt Handlers
//Interrupt Handler for ADC 1/2 
void ADC1_2_IRQHandler(void)
{
	NVIC_ClearPendingIRQ(ADC1_2_IRQn);
	
	//ADC End of Conversion (EOC)
	if ((ADC1->ISR & ADC_ISR_EOC) == ADC_ISR_EOC) {
		ADC1->ISR |= ADC_ISR_EOC;	//Cearb by writing 1 to it 
	}
	
	//ADC End of Injected Sequence of Conversions  (JEOS)
	if ((ADC1->ISR & ADC_ISR_EOS) == ADC_ISR_EOS) {
		ADC1->ISR |= ADC_ISR_EOS;		//Cear JEOS by writing 1 to it.
	}
}


////Functions to convert sensor data into LCD readable commands 
//Converts a uint16_t number to int and splits it into 10's and 1's place
void ADCtoDisp(uint16_t result) 
{
	//int distance = (36.1/((result)/1000.0))-1.0; 	//Apply linear equation to input 
	//int distance = 125.0/(((result*3.0)/1024.0)-0.1607)-1;
	//int distance = 34.0/(result/1024.0);
	
	int distance = 29.0/((result*3.0)/1024.0);	//Apply linear equation to input
	//int distance = ((result*3.0)/102.4);//409.60);
	
	upper = distance/10;											//Isolate 10's place
	lower = distance%10; 											//Isolate 1's place

	//Determines % of sensor's distance 
	if (distance <= 20)												//0-25% of max range
		numBars  = 4;
	else if(distance <= 40)										//25-50% of max range
		numBars  = 3;
	else if(distance <= 60)										//50-75% of max range
		numBars  = 2;
	else if(distance <= 80)										//75-100% of max range
		numBars  = 1;
	else 																			//Out of accurate range
		numBars = 0; 
}


////LCD Update routine 
encoding characters_to_display[7] = {0};

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
	char2mem(digit_bar, characters_to_display[6]);
	
	LCD->SR |= LCD_SR_UDR; 											//Request update display
	
	while ((LCD->SR&LCD_SR_UDD) == 0); 					//Wait for update display done
	
	LCD->CLR |= 1<<3; 													//ACK LCD updated 
	
	delay(70);
}


////Reads sensor data and sends results to LCD                      
void collector()
{
	int  LLsensor = 1, LCsensor = 0, RCsensor = 0, RRsensor = 0;
	
	//Starts ADC Conversion and collects the result 
	ADC1->CR |= ADC_CR_ADSTART;				
	while ( (ADC123_COMMON->CSR | ADC_CSR_EOC_MST) == 0);
	result = ADC1->DR;
	
	//IR sensor controller 
	int32_t counter = 0;
	int32_t threshold = 10;
	
	GPIOE->MODER |= 1U<<(2*15) | 1U<<28 | 1U<<26 | 1U<<24; 	//Set pins 12-15 as Output(01)
	GPIOE->ODR |= 1U<<15 | 1U<<14 | 1U<<13 | 1U<<12;				//Set ODR pins high 
	delay(10);																							//Wait for 10ms 
	GPIOE->MODER &= ~(3U<<(2*15) | 3U<<28 | 3U<<26 | 3U<<24);//Set pins 12-15 as Input(00)
	
	//Delay for cap to discharge 
	for (counter = 0; counter <= threshold ; counter++) 
	{
		delay(1);
	};
	
	//Calls to convet raw sensor data into LCD interpretable commands 
	//Convert uint16_t result to int and split into 10's and 1's place
	ADCtoDisp(result); 			
	//Convert IR sensor input data to int corresponding to LCD char 'B' or 'W'	
	LLsensor = (GPIOE->IDR & 0x8000)? 1 : 22;		
	LCsensor = (GPIOE->IDR & 0x4000)? 1 : 22;
	RCsensor = (GPIOE->IDR & 0x2000)? 1 : 22;
	RRsensor = (GPIOE->IDR & 0x1000)? 1 : 22;
	
	//Display current sensor readings on LCD
	if(lower < 10 & upper <10){									//Ensure that distance is less than 100cm
	characters_to_display[0] = numbers[upper];
	characters_to_display[1] = numbers[lower];
	}
	else {																			//If distance over 100cm display FF 
	characters_to_display[0] = alpha[5];
	characters_to_display[1] = alpha[5];
	}
	characters_to_display[6] = special[numBars+2];
	characters_to_display[2] = alpha[LLsensor];
	characters_to_display[3] = alpha[LCsensor];
	characters_to_display[4] = alpha[RCsensor];
	characters_to_display[5] = alpha[RRsensor];
	LCDupdate();
}


////Initialize all components and read sensor inputs continuously
int main(void)
{
	System_Clock_Init();	//Start and initlize sys CLK
	LCD_Initialization();	//Initlize all LCD related registers and clocks
	initADC();						//Initlize all ADC related registers and clocks
	initIR();							//Initlize all IR sensor related registers and clocks
	
	while(1){
	collector();					//'main' function; collects data and updates LCD indefinitely
	}
  //EOP
}
