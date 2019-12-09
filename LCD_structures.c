#include "stm32l476xx.h"
#include "LCD_structures.h"

// You may want to set your editor settings to use the Tab character instead of spaces.

// Bitmap of the entirety of LCD RAM we want to modify.
typedef struct LCD_RAM_MASK {
	uint32_t     : 3; // bit padding.
	uint32_t _1g : 1; // digit position 1, segment g
	uint32_t _1e : 1; // digit position 1, segment e
	uint32_t _2g : 1; // digit position 2, segment g
	uint32_t _2e : 1; // etc...
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
	
	uint32_t     : 3;
	uint32_t _1f : 1;
	uint32_t _1d : 1;
	uint32_t _2f : 1;
	uint32_t _2d : 1;
	uint32_t     : 1;
	uint32_t _6c : 1;
	uint32_t _6a : 1;
	uint32_t     : 2;
	uint32_t _2a : 1;
	uint32_t _2c : 1;
	uint32_t _3f : 1;
	uint32_t _3d : 1;
	uint32_t     : 1;
	uint32_t _6d : 1;
	uint32_t     : 4;
	uint32_t _1a : 1;
	uint32_t _1c : 1;
	uint32_t _5a : 1;
	uint32_t _5c : 1;
	uint32_t _6f : 1;
	uint32_t     : 1;
	uint32_t _3a : 1;
	uint32_t _3c : 1;
	uint32_t _4f : 1;
	uint32_t _4d : 1;
	
	uint32_t _4a : 1;
	uint32_t _4c : 1;
	uint32_t _5f : 1;
	uint32_t _5d : 1;
	uint32_t     : 28;
	
	uint32_t     : 3;
	uint32_t _1q : 1;
	uint32_t _1p : 1;
	uint32_t _2q : 1;
	uint32_t _2p : 1;
	uint32_t     : 1;
	uint32_t _1bar : 1; // bar position, segment 1
	uint32_t _6k : 1;
	uint32_t     : 2;
	uint32_t _2k : 1;
	uint32_t _2col : 1; // digit position 2, segment colon
	uint32_t _3q : 1;
	uint32_t _3p : 1;
	uint32_t     : 1;
	uint32_t _6p : 1;
	uint32_t     : 4;
	uint32_t _1k : 1;
	uint32_t _1col : 1;
	uint32_t _5k : 1;
	uint32_t _3bar : 1; // bar position, segment 3
	uint32_t _6q : 1;
	uint32_t     : 1;
	uint32_t _3k : 1;
	uint32_t _3col : 1;
	uint32_t _4q : 1;
	uint32_t _4p : 1;
	
	uint32_t _4k : 1;
	uint32_t _4col : 1;
	uint32_t _5q : 1;
	uint32_t _5p : 1;
	uint32_t     : 28;
	
	uint32_t     : 3;
	uint32_t _1h : 1;
	uint32_t _1n : 1;
	uint32_t _2h : 1;
	uint32_t _2n : 1;
	uint32_t     : 1;
	uint32_t _0bar : 1; // bar position, segment 0
	uint32_t _6j : 1;
	uint32_t     : 2;
	uint32_t _2j : 1;
	uint32_t _2dp : 1; // digit position 2, segment decimal
	uint32_t _3h : 1;
	uint32_t _3n : 1;
	uint32_t     : 1;
	uint32_t _6n : 1;
	uint32_t     : 4;
	uint32_t _1j : 1;
	uint32_t _1dp : 1;
	uint32_t _5j : 1;
	uint32_t _2bar : 1; // bar position, segment 2
	uint32_t _6h : 1;
	uint32_t     : 1;
	uint32_t _3j : 1;
	uint32_t _3dp : 1;
	uint32_t _4h : 1;
	uint32_t _4n : 1;
	
	uint32_t _4j : 1;
	uint32_t _4dp : 1;
	uint32_t _5h : 1;
	uint32_t _5n : 1;
	uint32_t     : 28;
} LCD_RAM_MASK;

// assign our bitmask to the proper area in memory.
#define LCD_RAM ((LCD_RAM_MASK*)(LCD->RAM))

void char2mem (uint8_t digit, encoding character) {
	switch(digit) {
	case digit_1:
		// use our bitmap to write to the proper locations in memory.
		LCD_RAM->_1a = character.A;
		LCD_RAM->_1b = character.B;
		LCD_RAM->_1c = character.C;
		LCD_RAM->_1d = character.D;
		LCD_RAM->_1e = character.E;
		LCD_RAM->_1f = character.F;
		LCD_RAM->_1g = character.G;
		LCD_RAM->_1h = character.H;
		LCD_RAM->_1j = character.J;
		LCD_RAM->_1k = character.K;
		LCD_RAM->_1m = character.M;
		LCD_RAM->_1n = character.N;
		LCD_RAM->_1p = character.P;
		LCD_RAM->_1q = character.Q;
		LCD_RAM->_1dp = character.DP;
		LCD_RAM->_1col = character.Col;
		break;
	case digit_2:
		LCD_RAM->_2a = character.A;
		LCD_RAM->_2b = character.B;
		LCD_RAM->_2c = character.C;
		LCD_RAM->_2d = character.D;
		LCD_RAM->_2e = character.E;
		LCD_RAM->_2f = character.F;
		LCD_RAM->_2g = character.G;
		LCD_RAM->_2h = character.H;
		LCD_RAM->_2j = character.J;
		LCD_RAM->_2k = character.K;
		LCD_RAM->_2m = character.M;
		LCD_RAM->_2n = character.N;
		LCD_RAM->_2p = character.P;
		LCD_RAM->_2q = character.Q;
		LCD_RAM->_2dp = character.DP;
		LCD_RAM->_2col = character.Col;
		break;
	case digit_3:
		LCD_RAM->_3a = character.A;
		LCD_RAM->_3b = character.B;
		LCD_RAM->_3c = character.C;
		LCD_RAM->_3d = character.D;
		LCD_RAM->_3e = character.E;
		LCD_RAM->_3f = character.F;
		LCD_RAM->_3g = character.G;
		LCD_RAM->_3h = character.H;
		LCD_RAM->_3j = character.J;
		LCD_RAM->_3k = character.K;
		LCD_RAM->_3m = character.M;
		LCD_RAM->_3n = character.N;
		LCD_RAM->_3p = character.P;
		LCD_RAM->_3q = character.Q;
		LCD_RAM->_3dp = character.DP;
		LCD_RAM->_3col = character.Col;
		break;
	case digit_4:
		LCD_RAM->_4a = character.A;
		LCD_RAM->_4b = character.B;
		LCD_RAM->_4c = character.C;
		LCD_RAM->_4d = character.D;
		LCD_RAM->_4e = character.E;
		LCD_RAM->_4f = character.F;
		LCD_RAM->_4g = character.G;
		LCD_RAM->_4h = character.H;
		LCD_RAM->_4j = character.J;
		LCD_RAM->_4k = character.K;
		LCD_RAM->_4m = character.M;
		LCD_RAM->_4n = character.N;
		LCD_RAM->_4p = character.P;
		LCD_RAM->_4q = character.Q;
		LCD_RAM->_4dp = character.DP;
		LCD_RAM->_4col = character.Col;
		break;
	case digit_5:
		LCD_RAM->_5a = character.A;
		LCD_RAM->_5b = character.B;
		LCD_RAM->_5c = character.C;
		LCD_RAM->_5d = character.D;
		LCD_RAM->_5e = character.E;
		LCD_RAM->_5f = character.F;
		LCD_RAM->_5g = character.G;
		LCD_RAM->_5h = character.H;
		LCD_RAM->_5j = character.J;
		LCD_RAM->_5k = character.K;
		LCD_RAM->_5m = character.M;
		LCD_RAM->_5n = character.N;
		LCD_RAM->_5p = character.P;
		LCD_RAM->_5q = character.Q;
		break;
	case digit_6:
		LCD_RAM->_6a = character.A;
		LCD_RAM->_6b = character.B;
		LCD_RAM->_6c = character.C;
		LCD_RAM->_6d = character.D;
		LCD_RAM->_6e = character.E;
		LCD_RAM->_6f = character.F;
		LCD_RAM->_6g = character.G;
		LCD_RAM->_6h = character.H;
		LCD_RAM->_6j = character.J;
		LCD_RAM->_6k = character.K;
		LCD_RAM->_6m = character.M;
		LCD_RAM->_6n = character.N;
		LCD_RAM->_6p = character.P;
		LCD_RAM->_6q = character.Q;
		break;
	case digit_bar:
		LCD_RAM->_0bar = character.Bar0;
		LCD_RAM->_1bar = character.Bar1;
		LCD_RAM->_2bar = character.Bar2;
		LCD_RAM->_3bar = character.Bar3;
	};
}

const encoding numbers[10] = {
	{.A=1, .B=1, .C=1, .D=1, .E=1, .F=1, .K=1, .Q=1},	// 0
	{.K=1, .B=1, .C=1},									// 1
	{.A=1, .B=1, .M=1, .G=1, .E=1, .D=1},				// 2
	{.A=1, .B=1, .M=1, .C=1, .D=1},						// 3
	{.F=1, .G=1, .M=1, .B=1, .C=1},						// 4
	{.A=1, .F=1, .G=1, .M=1, .C=1, .D=1},				// 5
	{.A=1, .F=1, .E=1, .D=1, .C=1, .M=1, .G=1},			// 6
	{.A=1, .B=1, .C=1},									// 7
	{.A=1, .B=1, .C=1, .D=1, .E=1, .F=1, .G=1, .M=1},	// 8
	{.D=1, .C=1, .B=1, .A=1, .F=1, .G=1, .M=1}			// 9
};

const encoding alpha[26] = {
	{.E=1, .F=1, .A=1, .B=1, .C=1, .G=1, .M=1},	// A
	{.J=1, .P=1, .A=1, .B=1, .M=1, .C=1, .D=1},	// B
	{.A=1, .F=1, .E=1, .D=1},					// C
	{.J=1, .P=1, .A=1, .B=1, .C=1, .D=1},		// D
	{.A=1, .F=1, .G=1, .E=1, .D=1},				// E
	{.A=1, .F=1, .E=1, .G=1},					// F
	{.A=1, .F=1, .E=1, .D=1, .C=1, .M=1},		// G
	{.F=1, .E=1, .G=1, .M=1, .B=1, .C=1},		// H
	{.J=1, .P=1, .A=1, .D=1},					// I
	{.B=1, .C=1, .D=1, .E=1},					// J
	{.F=1, .E=1, .G=1, .K=1, .N=1},				// K
	{.F=1, .E=1, .D=1},							// L
	{.E=1, .F=1, .H=1, .K=1, .B=1, .C=1},		// M
	{.E=1, .F=1, .H=1, .N=1, .C=1, .B=1},		// N
	{.A=1, .B=1, .C=1, .D=1, .E=1, .F=1},		// O
	{.E=1, .F=1, .A=1, .B=1, .M=1, .G=1},		// P
	{.A=1, .B=1, .C=1, .D=1, .E=1, .F=1, .N=1}, // Q
	{.E=1, .F=1, .A=1, .B=1, .M=1, .G=1, .N=1}, // R
	{.A=1, .F=1, .G=1, .M=1, .C=1, .D=1},		// S
	{.J=1, .P=1, .A=1},							// T
	{.B=1, .C=1, .D=1, .E=1, .F=1},				// U
	{.F=1, .E=1, .Q=1, .K=1},					// V
	{.F=1, .E=1, .Q=1, .N=1, .C=1, .B=1},		// W
	{.H=1, .N=1, .K=1, .Q=1},					// X
	{.H=1, .P=1, .K=1},							// Y
	{.A=1, .K=1, .Q=1, .D=1}					// Z
};

// some of these may be ORRed with specific digits to produce desired display
const encoding special[7] = {
	{.G=1, .M=1},						// -
	{.Col=1},							// :
	{.DP=1},							// .
	{.Bar0=1},							// special character 1 for BAR position
	{.Bar0=1, .Bar1=1},					// special character 2 for BAR position
	{.Bar0=1, .Bar1=1, .Bar2=1},		// special character 3 for BAR position
	{.Bar0=1, .Bar1=1, .Bar2=1, .Bar3=1}// special character 4 for BAR position
};
