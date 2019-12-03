#include "stm32l476xx.h"
#include "LCD_structures.h"

typedef struct LCD_RAM_MASK {
	uint32_t     : 3;
	uint32_t _1g : 1;
	uint32_t _1e : 1;
	uint32_t _2g : 1;
	uint32_t _2e : 1;
	uint32_t     : 1;
	uint32_t _6m : 1;
	uint32_t _6b : 1;
	uint32_t     : 2;
	uint32_t _2b : 1;
	uint32_t _2m : 1;
	uint32_t _3g : 1;
	uint32_t _3e : 1;
	uint32_t     : 1;
	uint32_t _6e : 1;
	uint32_t     : 4;
	uint32_t _1b : 1;
	uint32_t _1m : 1;
	uint32_t _5b : 1;
	uint32_t _5m : 1;
	uint32_t _6g : 1;
	uint32_t     : 1;
	uint32_t _3b : 1;
	uint32_t _3m : 1;
	uint32_t _4g : 1;
	uint32_t _4e : 1;
	
	uint32_t _4b : 1;
	uint32_t _4m : 1;
	uint32_t _5g : 1;
	uint32_t _5e : 1;
	uint32_t     : 28;
} LCD_RAM_MASK;

#define LCD_RAM ((LCD_RAM_MASK*)(LCD->RAM))

void char2mem (uint8_t digit, encoding character) {
	LCD_RAM->_1b = 1;
	LCD_RAM->_4b = 1;
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
