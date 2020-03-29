#ifndef _FLAPPYBIRD_RANDOM_MWCRAND_H_
#define _FLAPPYBIRD_RANDOM_MWCRAND_H_

// C99 Complementary Multiply With Carry generator
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// CMWC working parts
#define CMWC_CYCLE 4096		// as Marsaglia recommends
#define CMWC_C_MAX 809430660	// as Marsaglia recommends

struct cmwc_state
{
	uint32_t Q[CMWC_CYCLE];
	uint32_t c;	// must be limited with CMWC_C_MAX
	unsigned i;
};

// Make 32 bit random number (some systems use 16 bit RAND_MAX [Visual C 2012 uses 15 bits!])
uint32_t rand32(void);

// Init the state with seed
void initCMWC(struct cmwc_state *state, unsigned int seed);

// CMWC engine
uint32_t randCMWC(struct cmwc_state *state);  //EDITED parameter *state was missing


#endif