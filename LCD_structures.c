#include "stm32l476xx.h"
#include "LCD_structures.h"

typedef struct LCD_RAM_MASK {
	union {
	volatile struct D1 {
		uint32_t : 32;
		
		uint32_t : 3;
		uint8_t H : 1;
		uint8_t N : 1;
		uint32_t : 17;
		uint8_t J : 1;
		uint8_t DP : 1;
		uint32_t : 8;
		
		uint32_t : 32;
		
		uint32_t : 3;
		uint8_t Q : 1;
		uint8_t P : 1;
		uint32_t : 17;
		uint8_t K : 1;
		uint8_t Col : 1;
		uint32_t : 8;
		
		uint32_t : 32;
		
		uint32_t : 3;
		uint8_t F : 1;
		uint8_t D : 1;
		uint32_t : 17;
		uint8_t A : 1;
		uint8_t C : 1;
		uint32_t : 8;
		
		uint32_t : 32;
		
		uint32_t : 3;
		uint8_t G : 1;
		uint8_t E : 1;
		uint32_t : 17;
		uint8_t B : 1;
		uint8_t M : 1;
		uint32_t : 8;
	} D1;
	volatile struct D2 {
		uint32_t : 32;
		
		uint32_t : 5;
		uint8_t H : 1;
		uint8_t N : 1;
		uint32_t : 5;
		uint8_t J : 1;
		uint8_t DP : 1;
		uint32_t : 18;
		
		uint32_t : 32;
		
		uint32_t : 5;
		uint8_t Q : 1;
		uint8_t P : 1;
		uint32_t : 5;
		uint8_t K : 1;
		uint8_t Col : 1;
		uint32_t : 18;
		
		uint32_t : 32;
		
		uint32_t : 5;
		uint8_t F : 1;
		uint8_t D : 1;
		uint32_t : 5;
		uint8_t A : 1;
		uint8_t C : 1;
		uint32_t : 18;
		
		uint32_t : 32;
		
		uint32_t : 5;
		uint8_t G : 1;
		uint8_t E : 1;
		uint32_t : 5;
		uint8_t B : 1;
		uint8_t M : 1;
		uint32_t : 18;
	} D2;
	volatile struct D3 {
		uint32_t : 32;
		
		uint32_t : 14;
		uint8_t H : 1;
		uint8_t N : 1;
		uint32_t : 12;
		uint8_t J : 1;
		uint8_t DP : 1;
		uint32_t : 2;
		
		uint32_t : 32;
		
		uint32_t : 14;
		uint8_t Q : 1;
		uint8_t P : 1;
		uint32_t : 12;
		uint8_t K : 1;
		uint8_t Col : 1;
		uint32_t : 2;
		
		uint32_t : 32;
		
		uint32_t : 14;
		uint8_t F : 1;
		uint8_t D : 1;
		uint32_t : 12;
		uint8_t A : 1;
		uint8_t C : 1;
		uint32_t : 2;
		
		uint32_t : 32;
		
		uint32_t : 14;
		uint8_t G : 1;
		uint8_t E : 1;
		uint32_t : 12;
		uint8_t B : 1;
		uint8_t M : 1;
		uint32_t : 2;
	} D3;
	volatile struct D4 {
		uint8_t J : 1;
		uint8_t DP : 1;
		uint32_t : 30;
		
		uint32_t : 30;
		uint8_t H : 1;
		uint8_t N : 1;
		
		uint8_t K : 1;
		uint8_t Col : 1;
		uint32_t : 30;
		
		uint32_t : 30;
		uint8_t Q : 1;
		uint8_t P : 1;
		
		uint8_t A : 1;
		uint8_t C : 1;
		uint32_t : 30;
		
		uint32_t : 30;
		uint8_t F : 1;
		uint8_t D : 1;
		
		uint8_t B : 1;
		uint8_t M : 1;
		uint32_t : 30;
		
		uint32_t : 30;
		uint8_t G : 1;
		uint8_t E : 1;
	} D4;
	volatile struct D5 {
		uint32_t : 2;
		uint8_t H : 1;
		uint8_t N : 1;
		uint32_t : 28;
		
		uint32_t : 24;
		uint8_t J : 1;
		uint32_t : 7;
		
		uint32_t : 2;
		uint8_t Q : 1;
		uint8_t P : 1;
		uint32_t : 28;
		
		uint32_t : 24;
		uint8_t K : 1;
		uint32_t : 7;
		
		uint32_t : 2;
		uint8_t F : 1;
		uint8_t D : 1;
		uint32_t : 28;
		
		uint32_t : 24;
		uint8_t A : 1;
		uint8_t C : 1;
		uint32_t : 6;
		
		uint32_t : 2;
		uint8_t G : 1;
		uint8_t E : 1;
		uint32_t : 28;
		
		uint32_t : 24;
		uint8_t B : 1;
		uint8_t M : 1;
		uint32_t : 6;
	} D5;
	volatile struct D6 {
		uint32_t : 32;
		
		uint32_t : 9;
		uint8_t J : 1;
		uint32_t : 7;
		uint8_t N : 1;
		uint32_t : 8;
		uint8_t H : 1;
		uint32_t : 5;
		
		uint32_t : 32;
		
		uint32_t : 9;
		uint8_t K : 1;
		uint32_t : 7;
		uint8_t P : 1;
		uint32_t : 8;
		uint8_t Q : 1;
		uint32_t : 5;
		
		uint32_t : 32;
		
		uint32_t : 8;
		uint8_t C : 1;
		uint8_t A : 1;
		uint32_t : 7;
		uint8_t D : 1;
		uint32_t : 8;
		uint8_t F : 1;
		uint32_t : 5;
		
		uint32_t : 32;
		
		uint32_t : 8;
		uint8_t M : 1;
		uint8_t B : 1;
		uint32_t : 7;
		uint8_t E : 1;
		uint32_t : 8;
		uint8_t G : 1;
		uint32_t : 5;
	} D6;
	volatile struct D7 {
		uint32_t : 32;
		
		uint32_t : 8;
		uint8_t Bar0 : 1;
		uint32_t : 16;
		uint8_t Bar2 : 1;
		uint32_t : 6;
		
		uint32_t : 32;
		
		uint32_t : 8;
		uint8_t Bar1 : 1;
		uint32_t : 16;
		uint8_t Bar3 : 1;
		uint32_t : 6;
		
		uint32_t : 32;
		
		uint32_t : 32;
		
		uint32_t : 32;
		
		uint32_t : 32;
	} D7;
	};
} LCD_RAM_MASK;

#define LCD_RAM ((LCD_RAM_MASK*)(LCD->RAM))

#define fillmem_helper(X, Y) LCD_RAM->D##X.Y = character.Y;

#define fillmem(n) \
fillmem_helper(n, A) \
fillmem_helper(n, B) \
fillmem_helper(n, C) \
fillmem_helper(n, D) \
fillmem_helper(n, E) \
fillmem_helper(n, F) \
fillmem_helper(n, G) \
fillmem_helper(n, H) \
fillmem_helper(n, J) \
fillmem_helper(n, K) \
fillmem_helper(n, M) \
fillmem_helper(n, N) \
fillmem_helper(n, P) \
fillmem_helper(n, Q) \
fillmem_helper(n, Col) \
fillmem_helper(n, DP)

#define fillmem1(n) \
fillmem_helper(n, A) \
fillmem_helper(n, B) \
fillmem_helper(n, C) \
fillmem_helper(n, D) \
fillmem_helper(n, E) \
fillmem_helper(n, F) \
fillmem_helper(n, G) \
fillmem_helper(n, H) \
fillmem_helper(n, J) \
fillmem_helper(n, K) \
fillmem_helper(n, M) \
fillmem_helper(n, N) \
fillmem_helper(n, P) \
fillmem_helper(n, Q)

#define fillmem2(n) \
fillmem_helper(n, Bar0) \
fillmem_helper(n, Bar1) \
fillmem_helper(n, Bar2) \
fillmem_helper(n, Bar3)

void char2mem (uint8_t digit, encoding character) {
	switch(digit) {
	case digit_1:
		fillmem(digit_1)
		break;
	case digit_2:
		fillmem(digit_2)
		break;
	case digit_3:
		fillmem(digit_3)
		break;
	case digit_4:
		fillmem(digit_4)
		break;
	case digit_5:
		fillmem1(digit_5)
		break;
	case digit_6:
		fillmem1(digit_6)
		break;
	case digit_bar:
		fillmem2(digit_bar)
		break;
	}
}

const encoding numbers[] = {
	{.A=1, .B=1, .C=1, .D=1, .E=1, .F=1, .K=1, .Q=1},	// 0
	{.K=1, .B=1, .C=1},																// 1
	{.A=1, .B=1, .M=1, .G=1, .E=1, .D=1},							// 2
	{.A=1, .B=1, .M=1, .C=1, .D=1},										// 3
	{.F=1, .G=1, .M=1, .B=1, .C=1},										// 4
	{.A=1, .F=1, .G=1, .M=1, .C=1, .D=1},							// 5
	{.A=1, .F=1, .E=1, .D=1, .C=1, .M=1, .G=1},				// 6
	{.A=1, .B=1, .C=1},																// 7
	{.A=1, .B=1, .C=1, .D=1, .E=1, .F=1, .G=1, .M=1}, // 8
	{.D=1, .C=1, .B=1, .A=1, .F=1, .G=1, .M=1}				// 9
};

const encoding alpha[] = {
	{.E=1, .F=1, .A=1, .B=1, .C=1, .G=1, .M=1}, // A
	{.J=1, .P=1, .A=1, .B=1, .M=1, .C=1, .D=1}, // B
	{.A=1, .F=1, .E=1, .D=1},										// C
	{.J=1, .P=1, .A=1, .B=1, .C=1, .D=1},				// D
	{.A=1, .F=1, .G=1, .E=1, .D=1},							// E
	{.A=1, .F=1, .E=1, .G=1},										// F
	{.A=1, .F=1, .E=1, .D=1, .C=1, .M=1},				// G
	{.F=1, .E=1, .G=1, .M=1, .B=1, .C=1},				// H
	{.J=1, .P=1, .A=1, .D=1},										// I
	{.B=1, .C=1, .D=1, .E=1},										// J
	{.F=1, .E=1, .G=1, .K=1, .N=1},							// K
	{.F=1, .E=1, .D=1},													// L
	{.E=1, .F=1, .H=1, .K=1, .B=1, .C=1},				// M
	{.E=1, .F=1, .H=1, .N=1, .C=1, .B=1},				// N
	{.A=1, .B=1, .C=1, .D=1, .E=1, .F=1},				// O
	{.E=1, .F=1, .A=1, .B=1, .M=1, .G=1},				// P
	{.A=1, .B=1, .C=1, .D=1, .E=1, .F=1, .N=1}, // Q
	{.E=1, .F=1, .A=1, .B=1, .M=1, .G=1, .N=1}, // R
	{.A=1, .F=1, .G=1, .M=1, .C=1, .D=1},				// S
	{.J=1, .P=1, .A=1},													// T
	{.B=1, .C=1, .D=1, .E=1, .F=1},							// U
	{.F=1, .E=1, .Q=1, .K=1},										// V
	{.F=1, .E=1, .Q=1, .N=1, .C=1, .B=1},				// W
	{.H=1, .N=1, .K=1, .Q=1},										// X
	{.H=1, .P=1, .K=1},													// Y
	{.A=1, .K=1, .Q=1, .D=1}										// Z
};

const encoding special[] = { // some of these may be ORRed with specific digits to produce desired display
	{.G=1, .M=1}, // -
	{.Col=1},			// :
	{.DP=1}				// .
};
