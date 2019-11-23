#ifndef LCD_STRUCTURES_H
#define LCD_STRUCTURES_H
#include <inttypes.h>
#pragma anon_unions

typedef struct {
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

extern const encoding alpha[26]; 
extern const encoding numbers[10];
extern const encoding special[3]; 

#define digit_1 1
#define digit_2 2
#define digit_3 3
#define digit_4 4
#define digit_5 5
#define digit_6 6
#define digit_bar 7

void char2mem (uint8_t digit, encoding character);

#endif
