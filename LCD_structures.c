#include "stm32l476xx.h"
#include "LCD_structures.h"

typedef struct LCD_RAM_MASK {
	union {
	struct D1 {
		uint32_t : 32;
		
		uint32_t : 14;
		uint8_t J : 1;
		uint8_t DP : 1;
		uint32_t : 11;
		uint8_t H : 1;
		uint8_t N : 1;
		uint32_t : 3;
		
		uint32_t : 32;
		
		uint32_t : 14;
		uint8_t K : 1;
		uint8_t Col : 1;
		uint32_t : 11;
		uint8_t Q : 1;
		uint8_t P : 1;
		uint32_t : 3;
		
		uint32_t : 32;
		
		uint32_t : 14;
		uint8_t A : 1;
		uint8_t C : 1;
		uint32_t : 11;
		uint8_t F : 1;
		uint8_t D : 1;
		uint32_t : 3;
		
		uint32_t : 32;
		
		uint32_t : 14;
		uint8_t B : 1;
		uint8_t M : 1;
		uint32_t : 11;
		uint8_t G : 1;
		uint8_t E : 1;
		uint32_t : 3;
	} D1;
 	struct D2 {
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
	struct D3 {
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
	struct D4 {
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
	struct D5 {
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
	struct D6 {
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
	struct D7 {
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

void char2mem (uint8_t digit, encoding character) {
	switch(digit) {
	case digit_1:
		LCD_RAM->D1 = (struct D1){
			.A=character.A, .B=character.B, .C=character.C, .D=character.D,
			.E=character.E, .F=character.F, .G=character.G, .H=character.H,
			.J=character.J, .K=character.K, .M=character.M, .N=character.N,
			.P=character.P, .Q=character.Q, .Col=character.Col, .DP=character.DP
		};
		break;
	case digit_2:
		LCD_RAM->D2.A = character.A;
		LCD_RAM->D2.B = character.B;
		LCD_RAM->D2.C = character.C;
		LCD_RAM->D2.D = character.D;
		LCD_RAM->D2.E = character.E;
		LCD_RAM->D2.F = character.F;
		LCD_RAM->D2.G = character.G;
		LCD_RAM->D2.H = character.H;
		LCD_RAM->D2.J = character.J;
		LCD_RAM->D2.K = character.K;
		LCD_RAM->D2.M = character.M;
		LCD_RAM->D2.N = character.N;
		LCD_RAM->D2.P = character.P;
		LCD_RAM->D2.Q = character.Q;
		LCD_RAM->D2.Col = character.Col;
		LCD_RAM->D2.DP = character.DP;
		break;
	case digit_3:
		LCD_RAM->D3.A = character.A;
		LCD_RAM->D3.B = character.B;
		LCD_RAM->D3.C = character.C;
		LCD_RAM->D3.D = character.D;
		LCD_RAM->D3.E = character.E;
		LCD_RAM->D3.F = character.F;
		LCD_RAM->D3.G = character.G;
		LCD_RAM->D3.H = character.H;
		LCD_RAM->D3.J = character.J;
		LCD_RAM->D3.K = character.K;
		LCD_RAM->D3.M = character.M;
		LCD_RAM->D3.N = character.N;
		LCD_RAM->D3.P = character.P;
		LCD_RAM->D3.Q = character.Q;
		LCD_RAM->D3.Col = character.Col;
		LCD_RAM->D3.DP = character.DP;
		break;
	case digit_4:
		LCD_RAM->D4.A = character.A;
		LCD_RAM->D4.B = character.B;
		LCD_RAM->D4.C = character.C;
		LCD_RAM->D4.D = character.D;
		LCD_RAM->D4.E = character.E;
		LCD_RAM->D4.F = character.F;
		LCD_RAM->D4.G = character.G;
		LCD_RAM->D4.H = character.H;
		LCD_RAM->D4.J = character.J;
		LCD_RAM->D4.K = character.K;
		LCD_RAM->D4.M = character.M;
		LCD_RAM->D4.N = character.N;
		LCD_RAM->D4.P = character.P;
		LCD_RAM->D4.Q = character.Q;
		LCD_RAM->D4.Col = character.Col;
		LCD_RAM->D4.DP = character.DP;
		break;
	case digit_5:
		LCD_RAM->D5.A = character.A;
		LCD_RAM->D5.B = character.B;
		LCD_RAM->D5.C = character.C;
		LCD_RAM->D5.D = character.D;
		LCD_RAM->D5.E = character.E;
		LCD_RAM->D5.F = character.F;
		LCD_RAM->D5.G = character.G;
		LCD_RAM->D5.H = character.H;
		LCD_RAM->D5.J = character.J;
		LCD_RAM->D5.K = character.K;
		LCD_RAM->D5.M = character.M;
		LCD_RAM->D5.N = character.N;
		LCD_RAM->D5.P = character.P;
		LCD_RAM->D5.Q = character.Q;
		break;
	case digit_6:
		LCD_RAM->D6.A = character.A;
		LCD_RAM->D6.B = character.B;
		LCD_RAM->D6.C = character.C;
		LCD_RAM->D6.D = character.D;
		LCD_RAM->D6.E = character.E;
		LCD_RAM->D6.F = character.F;
		LCD_RAM->D6.G = character.G;
		LCD_RAM->D6.H = character.H;
		LCD_RAM->D6.J = character.J;
		LCD_RAM->D6.K = character.K;
		LCD_RAM->D6.M = character.M;
		LCD_RAM->D6.N = character.N;
		LCD_RAM->D6.P = character.P;
		LCD_RAM->D6.Q = character.Q;
		break;
	case digit_bar:
		LCD_RAM->D7.Bar0 = character.Bar0;
		LCD_RAM->D7.Bar1 = character.Bar1;
		LCD_RAM->D7.Bar2 = character.Bar2;
		LCD_RAM->D7.Bar3 = character.Bar3;
		break;
	}
}

const encoding numbers[10] = {
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

const encoding alpha[26] = {
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

const encoding special[3] = { // some of these may be ORRed with specific digits to produce desired display
	{.G=1, .M=1}, // -
	{.Col=1},			// :
	{.DP=1}				// .
};
