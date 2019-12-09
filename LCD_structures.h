#ifndef LCD_STRUCTURES_H
#define LCD_STRUCTURES_H
#include <inttypes.h>

// enable anonymous unions
#pragma anon_unions

// structure for defining the character set.
// each bit corresponds with a segment of a position on the LCD.
typedef struct {
	// these bits are aliased to multiple names because the same structure is
	// used for digit positions and special positions.
	union {
		uint8_t A : 1;
		uint8_t Bar0 : 1;
	};
	union {
		uint8_t B : 1;
		uint8_t Bar1 : 1;
	};
	union {
		uint8_t C : 1;
		uint8_t Bar2 : 1;
	};
	union {
		uint8_t D : 1;
		uint8_t Bar3 : 1;
	};
	uint8_t E : 1;
	uint8_t F : 1;
	uint8_t G : 1;
	uint8_t H : 1;
	uint8_t J : 1;
	uint8_t K : 1;
	uint8_t M : 1;
	uint8_t N : 1;
	uint8_t P : 1;
	uint8_t Q : 1;
	
	uint8_t Col : 1;
	uint8_t DP : 1;
} encoding;

// use these definitions to tell the char2mem function
// which digit you want to set.
#define digit_1 1
#define digit_2 2
#define digit_3 3
#define digit_4 4
#define digit_5 5
#define digit_6 6
#define digit_bar 7

// this function accepts a character encoding and performs the proper logic
// in order to write the information to the proper areas of LCD memory,
// depending on the specified digit position.
void char2mem (uint8_t digit, encoding character);

// helper character sets, defined in LCD_structures.c
extern const encoding numbers[10]; // numbers 0 to 9
extern const encoding alpha[26]; // letters A to Z
extern const encoding special[7]; // special symbols

#endif
