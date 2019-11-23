#include "stm32l476xx.h"
#include "LCD_structures.h"

//The following three Methods do the register setup for their respective jurisdictions
	/*  =========================================================================
                                 LCD MAPPING
    =========================================================================
LCD allows to display informations on six 14-segment digits and 4 bars:

  1       2       3       4       5       6
-----   -----   -----   -----   -----   -----   
|\|/| o |\|/| o |\|/| o |\|/| o |\|/|   |\|/|   BAR3
-- --   -- --   -- --   -- --   -- --   -- --   BAR2
|/|\| o |/|\| o |/|\| o |/|\| o |/|\|   |/|\|   BAR1
----- * ----- * ----- * ----- * -----   -----   BAR0

LCD segment mapping:
--------------------
  -----A-----        _ 
  |\   |   /|   COL |_|
  F H  J  K B          
  |  \ | /  |        _ 
  --G-- --M--   COL |_|
  |  / | \  |          
  E Q  P  N C          
  |/   |   \|        _ 
  -----D-----   DP  |_|

 An LCD character coding is based on the following matrix:
COM           0   1   2     3
SEG(n)      { E , D , P ,   N   }
SEG(n+1)    { M , C , COL , DP  }
SEG(23-n-1) { B , A , K ,   J   }
SEG(23-n)   { G , F , Q ,   H   }
with n positive odd number.

 The character 'A' for example is:
  -------------------------------
LSB   { 1 , 0 , 0 , 0   }
      { 1 , 1 , 0 , 0   }
      { 1 , 1 , 0 , 0   }
MSB   { 1 , 1 , 0 , 0   }
      -------------------
  'A' =  F    E   0   0 hexa

  @endverbati

 LCD (24 segments, 4 commons, multiplexed 1/4 duty, 1/3 bias) on DIP28 connector
 VLCD = PC3

*/

void LCD_PIN_Init(void){
	// LCD (24 segments, 4 commons, multiplexed 1/4 duty, 1/3 bias) on DIP28 connector
	//   VLCD = PC3
	//
	//   COM0 = PA8     COM1  = PA9      COM2  = PA10    COM3  = PB9
	//
	//   SEG0 = PA7     SEG6  = PD11     SEG12 = PB5     SEG18 = PD8
	//   SEG1 = PC5     SEG7  = PD13     SEG13 = PC8     SEG19 = PB14
	//   SEG2 = PB1     SEG8  = PD15     SEG14 = PC6     SEG20 = PB12
	//   SEG3 = PB13    SEG9  = PC7      SEG15 = PD14    SEG21 = PB0
	//   SEG4 = PB15    SEG10 = PA15     SEG16 = PD12    SEG22 = PC4
	//   SEG5 = PD9     SEG11 = PB4      SEG17 = PD10    SEG23 = PA6	
	
	/* Enable GPIOs clock */ 	
	RCC->AHB2ENR |=   RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN | RCC_AHB2ENR_GPIODEN;
	
	// GPIO Mode: Input(00, reset), Output(01), AlterFunc(10), Analog(11, reset)
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	// GPIO Output Type: Output push-pull (0, reset), Output open drain (1)
	
  /* Configure PA 6, 7, 8, 9, 10, 15 as Alternative Function 11 (0x0B)*/	
	GPIOA->MODER   &= ~(3U<<(2*6) | 3U<<(2*7) | 3U<<(2*8) | 3U<<(2*9) | 3U<<(2*10) | 3U<<(2*15));
	GPIOA->MODER   |=   2U<<(2*6) | 2U<<(2*7) | 2U<<(2*8) | 2U<<(2*9) | 2U<<(2*10) | 2U<<(2*15) ;
	GPIOA->AFR[0]  |= 0xBB000000;  
	GPIOA->AFR[1]  |= 0xB0000BBB; 
	GPIOA->OSPEEDR &= ~(3U<<(2*6) | 3U<<(2*7) | 3U<<(2*8) | 3U<<(2*9) | 3U<<(2*10) | 3U<<(2*15));
	GPIOA->OSPEEDR |=   2U<<(2*6) | 2U<<(2*7) | 2U<<(2*8) | 2U<<(2*9) | 2U<<(2*10) | 2U<<(2*15) ;
	GPIOA->PUPDR   &= ~(3U<<(2*6) | 3U<<(2*7) | 3U<<(2*8) | 3U<<(2*9) | 3U<<(2*10) | 3U<<(2*15));
  
	/* Configure PB 0, 1, 4, 5, 9, 12, 13, 14, 15 as Alternative Function 11 (0x0B)*/
	GPIOB->MODER   &= ~(3U<<(2*0) | 3U<<(2*1) | 3U<<(2*4) | 3U<<(2*5) | 3U<<(2*9) | 3U<<(2*12)| 3U<<(2*13)| 3U<<(2*14)| 3U<<(2*15));
	GPIOB->MODER   |=   2U<<(2*0) | 2U<<(2*1) | 2U<<(2*4) | 2U<<(2*5) | 2U<<(2*9) | 2U<<(2*12)| 2U<<(2*13)| 2U<<(2*14)| 2U<<(2*15);
	GPIOB->AFR[0]  |= 0x00BB00BB;  
	GPIOB->AFR[1]  |= 0xBBBB00B0; 
	GPIOB->OSPEEDR &= ~(3U<<(2*0) | 3U<<(2*1) | 3U<<(2*4) | 3U<<(2*5) | 3U<<(2*9) | 3U<<(2*12)| 3U<<(2*13)| 3U<<(2*14)| 3U<<(2*15));
	GPIOB->OSPEEDR |=   2U<<(2*0) | 2U<<(2*1) | 2U<<(2*4) | 2U<<(2*5) | 2U<<(2*9) | 2U<<(2*12)| 2U<<(2*13)| 2U<<(2*14)| 2U<<(2*15);
	GPIOB->PUPDR   &= ~(3U<<(2*0) | 3U<<(2*1) | 3U<<(2*4) | 3U<<(2*5) | 3U<<(2*9) | 3U<<(2*12)| 3U<<(2*13)| 3U<<(2*14)| 3U<<(2*15));

	
  /* Configure PC 3, 4, 5, 6, 7, 8 as Alternative Function 11 (0x0B)*/  	
	// Note: PC3 = V_LCD
	GPIOC->MODER   &= ~(3U<<(2*3) | 3U<<(2*4) | 3U<<(2*5) | 3U<<(2*6)  | 3U<<(2*7) | 3U<<(2*8));
	GPIOC->MODER   |=   2U<<(2*3) | 2U<<(2*4) | 2U<<(2*5) | 2U<<(2*6)  | 2U<<(2*7) | 2U<<(2*8);
	GPIOC->AFR[0]  |= 0xBBBBB000;   
	GPIOC->AFR[1]  |= 0x0000000B; 
	GPIOC->OSPEEDR &= ~(3U<<(2*3) | 3U<<(2*4) | 3U<<(2*5) | 3U<<(2*6)  | 3U<<(2*7) | 3U<<(2*8));
	GPIOC->OSPEEDR |=   2U<<(2*3) | 2U<<(2*4) | 2U<<(2*5) | 2U<<(2*6)  | 2U<<(2*7) | 2U<<(2*8);
	GPIOC->PUPDR   &= ~(3U<<(2*3) | 3U<<(2*4) | 3U<<(2*5) | 3U<<(2*6)  | 3U<<(2*7) | 3U<<(2*8));

	
	/* Configure PD 8, 9, 10, 11, 12, 13, 14, 15 as Alternative Function 11 (0x0B) */
	GPIOD->MODER   &= ~0xFFFF0000; // ~(3U<<(2*8) | 3U<<(2*9) | 3U<<(2*10)  | 3U<<(2*11) | 3U<<(2*12) | 3U<<(2*13)| 3U<<(2*14) | 3U<<(2*15));
	GPIOD->MODER   |= 0xAAAA0000;  // 2U<<(2*8) | 2U<<(2*9) | 2U<<(2*10)  | 2U<<(2*11) | 2U<<(2*12) | 2U<<(2*13)| 2U<<(2*14) | 2U<<(2*15);
	GPIOD->AFR[1]  |= 0xBBBBBBBB; 
	GPIOD->OSPEEDR &= 0xFFFF0000;  // ~(3U<<(2*8) | 3U<<(2*9) | 3U<<(2*10)  | 3U<<(2*11) | 3U<<(2*12) | 3U<<(2*13)| 3U<<(2*14) | 3U<<(2*15));
	GPIOD->OSPEEDR |= 0xAAAA0000;  // 2U<<(2*8) | 2U<<(2*9) | 2U<<(2*10)  | 2U<<(2*11) | 2U<<(2*12) | 2U<<(2*13)| 2U<<(2*14) | 2U<<(2*15);	
	GPIOD->PUPDR   &= 0xFFFF0000;  // ~(3U<<(2*8) | 3U<<(2*9) | 3U<<(2*10)  | 3U<<(2*11) | 3U<<(2*12) | 3U<<(2*13)| 3U<<(2*14) | 3U<<(2*15));

}

void LCD_Clock_Init(void){
	// Enable write access to Backup domain
	if ( (RCC->APB1ENR1 & RCC_APB1ENR1_PWREN) == 0)
		RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;	// Power interface clock enable
	(void) RCC->APB1ENR1;  // Delay after an RCC peripheral clock enabling
	
	// Select LSE as RTC clock soucre 
	if ( (PWR->CR1 & PWR_CR1_DBP) == 0) {
		PWR->CR1  |= PWR_CR1_DBP;				  			// Enable write access to Backup domain
		while((PWR->CR1 & PWR_CR1_DBP) == 0);  	// Wait for Backup domain Write protection disable
	}
	
	// Reset LSEON and LSEBYP bits before configuring the LSE
	RCC->BDCR &= ~(RCC_BDCR_LSEON | RCC_BDCR_LSEBYP);

	// RTC Clock selection can be changed only if the Backup Domain is reset
	RCC->BDCR |=  RCC_BDCR_BDRST;
	RCC->BDCR &= ~RCC_BDCR_BDRST;
	
	// Note from STM32L4 Reference Manual: 	
  // RTC/LCD Clock:  (1) LSE is in the Backup domain. (2) HSE and LSI are not.	
	while((RCC->BDCR & RCC_BDCR_LSERDY) == 0){  // Wait until LSE clock ready
		RCC->BDCR |= RCC_BDCR_LSEON;
	}
	
	// Select LSE as RTC clock source
	// BDCR = Backup Domain Control Register 
	RCC->BDCR	&= ~RCC_BDCR_RTCSEL;	  // RTCSEL[1:0]: 00 = No Clock, 01 = LSE, 10 = LSI, 11 = HSE
	RCC->BDCR	|= RCC_BDCR_RTCSEL_0;   // Select LSE as RTC clock	
	
	RCC->APB1ENR1 &= ~RCC_APB1ENR1_PWREN;	// Power interface clock disable
	
	// Wait for the external capacitor Cext which is connected to the VLCD pin is charged (approximately 2ms for Cext=1uF) 
	
	// Enable LCD peripheral Clock
	RCC->APB1ENR1 |= RCC_APB1ENR1_LCDEN;
	
	// Enable SYSCFG 
	// RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
}

void LCD_Configure(void){
	
	LCD->CR &= ~LCD_CR_LCDEN;	 // Disable LCD
	
	// LCD frame control register (FCR)
	// Set clock divider 
	LCD->FCR |=  0xF<<18;       // DIV[3:0] = 1111, ck_div = ck_ps/31
		
	// Set CLKPS = LCDCLK
	LCD->FCR &= ~LCD_FCR_PS;    // 0000: ck_ps = LCDCLK
	
	// Blink mode selection
  LCD->FCR &= ~LCD_FCR_BLINK; // 00: Blink disabled
															// 01: Blink enabled on SEG[0], COM[0] (1 pixel)
															// 10: Blink enabled on SEG[0], all COMs (up to 8 pixels depending on the programmed duty)
															// 11: Blink enabled on all SEGs and all COMs (all pixels)
	// Blink Frequency
	LCD->FCR &= ~LCD_FCR_BLINKF; 
	LCD->FCR |= LCD_FCR_BLINKF_1;  // 010: fLCD/32	
    
	// Set Pulse ON duration
	// Use high drive internal booster to provide larger drive current
	// Set the duration that the low-resister voltage divider is used
	LCD->FCR |= 0x7 << 4;     // PON[2:0] = 0x111
	
	// Contrast Control: specify one of the VLCD maximum voltages
	LCD->FCR &= ~LCD_FCR_CC;  // CC[2:0] bits (Contrast Control)
	LCD->FCR |= 0x5<<10; 			// 101: VLCD5, Refer to the product datasheet for the VLCDx values

	// Pulse ON duration: A short pulse will lead to lower power consumption, 
	// but displays with high internal resistance may need a longer pulse to 
	// achieve satisfactory contrast. 
	LCD->FCR &= ~LCD_FCR_PON; // PON[2:0] bits (Pulse ON Duration)
	LCD->FCR |= 0x4<<4; // 100: 4/ck_ps
    
	// Waits until the LCD FCR register is synchronized in the LCDCLK domain
	// This bit is set by hardware each time the LCD_FCR register is updated in the LCDCLK domain.
	// It is cleared by hardware when writing to the LCD_FCR register.
	while ((LCD->SR & LCD_SR_FCRSR) == 0);  // Loop until FCRSF flag is set
	
	// Select 1/4 duty
	LCD->CR &= ~(LCD_CR_DUTY);  // Clear duty
	LCD->CR |= 0x3<<2; 		      // DUTY[2:0]: 000=Static; 001=1/2; 010=1/3; 011=1/4; 100=1/8	

	// Select 1/3 bias
	LCD->CR &= ~(LCD_CR_BIAS);  // Clear bias
	LCD->CR |= 0x2<<5; 		      // BIAS[1:0]: 00=1/4; 01=1/2; 10=1/3	
	
	// MUX_SEG disabled
	// 0: SEG pin multiplexing disabled
  // 1: SEG[31:28] are multiplexed with SEG[43:40]
	LCD->CR &= ~LCD_CR_MUX_SEG; // Disable Mux Segment; 
	
	/* LCD control register */
	// VSEL: Voltage source selection
	// When the LCD is based on the internal step-up converter, the VLCD pin should be connected to a capacitor (see the product datasheet for further information).
	LCD->CR &= ~LCD_CR_VSEL;    // 0 = internal source, 1 = external source (VLCD pin)	
	
	// LCD controller enable
	// The VSEL, MUX_SEG, BIAS, DUTY and BUFEN bits are write-protected when the LCD is enabled (ENS bit in LCD_SR to 1).
	// When the LCD is disabled all COM and SEG pins are driven to VSS.
	LCD->CR |= LCD_CR_LCDEN;	 // Enable LCD
	// Loop until LCD controller is enabled
	while ((LCD->SR & LCD_SR_ENS) == 0);  // ENS is set by hardware automatically
		
	// Wait until the LCD Booster is ready
	while ((LCD->SR & LCD_SR_RDY) == 0);  // Loop until step-up converter is ready to provide the correct voltage.
	
  // Enable the display request
  LCD->SR |= LCD_SR_UDR; 	
}

void LCD_Clear(void){
  uint8_t counter = 0;

  // Wait until LCD ready */  
	while ((LCD->SR & LCD_SR_UDR) != 0); // Wait for Update Display Request Bit
  
  for (counter = 0; counter <= 15; counter++) {
    LCD->RAM[counter] = 0;
  }

  /* Update the LCD display */
	LCD->SR |= LCD_SR_UDR; 
}


void LCD_Initialization(void){
	LCD_PIN_Init();
	LCD_Clock_Init();	
	LCD_Configure();
	LCD_Clear();
}


void initSensor(){
	//Use GPIOA 1,2 for ADC
	//Ues GPIOE 12,13,14,15 for the IR sensors 

////Enable ADC CLK
	RCC->AHB2ENR  |= RCC_AHB2ENR_ADCEN;
	RCC->AHB2RSTR	|= RCC_AHB2RSTR_ADCRST;
	(void)RCC->AHB2RSTR; // short delay
	RCC->AHB2RSTR	&= ~RCC_AHB2RSTR_ADCRST;
	
////Enable GPIOE and A CLK  [GPIOA is already enabled in initLCD] 
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN; 		
	
	//ADC Pin init 
	GPIOA->MODER |=  3U<<(2*1) | 3U<<(2*2);  // Mode 11 = Analog
	
	GPIOA->PUPDR &= ~( 3U<<(2*1) | 3U<<(2*2)); // No pull-up, no pull-down
	
	GPIOA->ASCR |= GPIO_ASCR_EN_1 | GPIO_ASCR_EN_2; //Connect analog switch to the ADC input
	
////ADC 1 specific enables 
	// I/O analog switches voltage booster
	// The I/O analog switches resistance increases when the VDDA voltage is too low. This
	// requires to have the sampling time adapted accordingly (cf datasheet for electrical
	// characteristics). This resistance can be minimized at low VDDA by enabling an internal
	// voltage booster with BOOSTEN bit in the SYSCFG_CFGR1 register.
	SYSCFG->CFGR1 |= SYSCFG_CFGR1_BOOSTEN; //EN internal voltage booster to correct for analog sw resistance increase w/low voltage
	

	// V_REFINT enable
	ADC123_COMMON->CCR |= ADC_CCR_VREFEN;  
	
	// ADC Clock Source: System Clock, PLLSAI1, PLLSAI2
	// Maximum ADC Clock: 80 MHz
	
	// ADC prescaler to select the frequency of the clock to the ADC
	ADC123_COMMON->CCR &= ~ADC_CCR_PRESC;   // 0000: input ADC clock not divided
	
	// ADC clock mode
	//   00: CK_ADCx (x=123) (Asynchronous clock mode),
	//   01: HCLK/1 (Synchronous clock mode).
	//   10: HCLK/2 (Synchronous clock mode)
	//   11: HCLK/4 (Synchronous clock mode)	 
	ADC123_COMMON->CCR &= ~ADC_CCR_CKMODE;  // HCLK = 80MHz
	ADC123_COMMON->CCR |=  ADC_CCR_CKMODE_0;

	//////////////////////////////////////////////////////////////////////////////////////////////
	// Independent Mode
	ADC123_COMMON->CCR &= ~ADC_CCR_DUAL;
	ADC123_COMMON->CCR |= 6U;  // 00110: Regular simultaneous mode only
	
	}

void initInterrupt(){

}


encoding characters_to_display[6] = {0};

//Decodes and sends char data to the LCD RAM

void LCDupdate(){
	
	//LCD->SR |= LCD_SR_UDR; 	
	while ((LCD->SR&LCD_SR_UDR) != 0); // Wait for Update Display Request Bit
	
	//LCD->RAM[0] = 0xffffffff; 
	
	
	char2mem(digit_1, alpha[2]);//characters_to_display[0]);
	char2mem(digit_2, characters_to_display[1]);
	char2mem(digit_3, characters_to_display[2]);
	char2mem(digit_4, characters_to_display[3]);
	char2mem(digit_5, characters_to_display[4]);
	char2mem(digit_6, characters_to_display[5]);
	LCD->SR |= LCD_SR_UDR; //request update display
	
	while ((LCD->SR&LCD_SR_UDD) == 0); //wait for update display done
	
	LCD->CLR |= 1<<3; 
}


//Reads sensor data                         //do we want a seperate data converter that calls LCDupdate?????
void collector(){
	
	characters_to_display[0] = alpha[3];
	characters_to_display[1] = alpha[3];
	characters_to_display[2] = alpha[3];
	characters_to_display[3] = alpha[3];
	characters_to_display[4] = alpha[3];
	characters_to_display[5] = alpha[3];
	LCDupdate();

}

int main(void){
	
	LCD_Initialization();					//Initlize all LCD related registers
	
	initSensor();				//Initlize all Sensor related registers 
	
	initInterrupt();		//Initlize all Interrupt related registers
	
	while(1){
	collector();				//Our actual 'main' function; collects data and updates LCD
	}

  //EOP
}
