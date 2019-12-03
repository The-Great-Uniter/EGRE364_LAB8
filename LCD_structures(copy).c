#include "stm32l476xx.h"
#include "LCD_structures.h"

typedef struct LCD_RAM_MASK {
	union {
	struct D1 {
		uint32_t : 3;
		uint8_t E : 1;
		uint8_t G : 1;
		uint32_t : 11;
		uint8_t M : 1;
		uint8_t B : 1;
		uint32_t : 14;
		
		uint32_t : 32;
		
		uint32_t : 3;
		uint8_t D : 1;
		uint8_t F : 1;
		uint32_t : 11;
		uint8_t C : 1;
		uint8_t A : 1;
		uint32_t : 14;
		
		uint32_t : 32;
		
		uint32_t : 3;
		uint8_t P : 1;
		uint8_t Q : 1;
		uint32_t : 11;
		uint8_t Col : 1;
		uint8_t K : 1;
		uint32_t : 14;
		
		uint32_t : 32;
		
		uint32_t : 3;
		uint8_t N : 1;
		uint8_t H : 1;
		uint32_t : 11;
		uint8_t DP : 1;
		uint8_t J : 1;
		uint32_t : 14;
		
		uint32_t : 32;
	} D1;
 	struct D2 {
		uint32_t : 18;
		uint8_t M : 1;
		uint8_t B : 1;
		uint32_t : 5;
		uint8_t E : 1;
		uint8_t G : 1;
		uint32_t : 5;
		
		uint32_t : 32;
		
		uint32_t : 18;
		uint8_t C : 1;
		uint8_t A : 1;
		uint32_t : 5;
		uint8_t D : 1;
		uint8_t F : 1;
		uint32_t : 5;
		
		uint32_t : 32;
		
		uint32_t : 18;
		uint8_t Col : 1;
		uint8_t K : 1;
		uint32_t : 5;
		uint8_t P : 1;
		uint8_t Q : 1;
		uint32_t : 5;
		
		uint32_t : 32;
		
		uint32_t : 18;
		uint8_t DP : 1;
		uint8_t J : 1;
		uint32_t : 5;
		uint8_t N : 1;
		uint8_t H : 1;
		uint32_t : 5;
		
		uint32_t : 32;
	} D2;
	struct D3 {
		uint32_t : 2;
		uint8_t M : 1;
		uint8_t B : 1;
		uint32_t : 12;
		uint8_t E : 1;
		uint8_t G : 1;
		uint32_t : 14;
		
		uint32_t : 32;
		
		uint32_t : 2;
		uint8_t C : 1;
		uint8_t A : 1;
		uint32_t : 12;
		uint8_t D : 1;
		uint8_t F : 1;
		uint32_t : 14;
		
		uint32_t : 32;
		
		uint32_t : 2;
		uint8_t Col : 1;
		uint8_t K : 1;
		uint32_t : 12;
		uint8_t P : 1;
		uint8_t Q : 1;
		uint32_t : 14;
		
		uint32_t : 32;
		
		uint32_t : 2;
		uint8_t DP : 1;
		uint8_t J : 1;
		uint32_t : 12;
		uint8_t N : 1;
		uint8_t H : 1;
		uint32_t : 14;
		
		uint32_t : 32;
	} D3;
	struct D4 {
		uint8_t E : 1;
		uint8_t G : 1;
		uint32_t : 30;
		
		uint32_t : 30;
		uint8_t M : 1;
		uint8_t B : 1;
		
		uint8_t D : 1;
		uint8_t F : 1;
		uint32_t : 30;
		
		uint32_t : 30;
		uint8_t C : 1;
		uint8_t A : 1;
		
		uint8_t P : 1;
		uint8_t Q : 1;
		uint32_t : 30;
		
		uint32_t : 30;
		uint8_t Col : 1;
		uint8_t K : 1;
		
		uint8_t N : 1;
		uint8_t H : 1;
		uint32_t : 30;
		
		uint32_t : 30;
		uint8_t DP : 1;
		uint8_t J : 1;
	} D4;
	struct D5 {
		uint32_t : 6;
		uint8_t M : 1;
		uint8_t B : 1;
		uint32_t : 24;
		
		uint32_t : 28;
		uint8_t E : 1;
		uint8_t G : 1;
		uint32_t : 2;
		
		uint32_t : 6;
		uint8_t C : 1;
		uint8_t A : 1;
		uint32_t : 24;
		
		uint32_t : 28;
		uint8_t D : 1;
		uint8_t F : 1;
		uint32_t : 2;
		
		uint32_t : 7;
		uint8_t K : 1;
		uint32_t : 24;
		
		uint32_t : 28;
		uint8_t P : 1;
		uint8_t Q : 1;
		uint32_t : 2;
		
		uint32_t : 7;
		uint8_t J : 1;
		uint32_t : 24;
		
		uint32_t : 28;
		uint8_t N : 1;
		uint8_t H : 1;
		uint32_t : 2;
	} D5;
	struct D6 {
		uint32_t : 5;
		uint8_t G : 1;
		uint32_t : 8;
		uint8_t E : 1;
		uint32_t : 7;
		uint8_t B : 1;
		uint8_t M : 1;
		uint32_t : 8;
		
		uint32_t : 32;
		
		uint32_t : 5;
		uint8_t F : 1;
		uint32_t : 8;
		uint8_t D : 1;
		uint32_t : 7;
		uint8_t A : 1;
		uint8_t C : 1;
		uint32_t : 8;
		
		uint32_t : 32;
		
		uint32_t : 5;
		uint8_t Q : 1;
		uint32_t : 8;
		uint8_t P : 1;
		uint32_t : 7;
		uint8_t K : 1;
		uint32_t : 9;
		
		uint32_t : 32;
		
		uint32_t : 5;
		uint8_t H : 1;
		uint32_t : 8;
		uint8_t N : 1;
		uint32_t : 7;
		uint8_t J : 1;
		uint32_t : 9;
		
		uint32_t : 32;
	} D6;
	struct D7 {
		uint32_t : 32;
		
		uint32_t : 32;
		
		uint32_t : 32;
		
		uint32_t : 32;
		
		uint32_t : 6;
		uint8_t Bar3 : 1;
		uint32_t : 16;
		uint8_t Bar1 : 1;
		uint32_t : 8;
		
		uint32_t : 32;
		
		uint32_t : 6;
		uint8_t Bar2 : 1;
		uint32_t : 16;
		uint8_t Bar0 : 1;
		uint32_t : 8;
		
		uint32_t : 32;
	} D7;
	};
} LCD_RAM_MASK;