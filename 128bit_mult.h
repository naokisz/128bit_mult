#include <stdint.h>

int carry_of_64bit_add(uint64_t a, uint64_t b) {

	int carry_of_LSB_add = (int)((a & 0x1) & (b & 0x1));
	int carry;

	a >>= 1;
	b >>= 1;

	if((a + b + carry_of_LSB_add) >> 63) {
		carry = 1;
	} else {
		carry = 0;
	}

	return carry;
}

void mult_128bit(uint64_t a, uint64_t b, uint64_t *lo, uint64_t *hi) {

	uint64_t tmphi, tmplo;
	int bit;

	*hi = 0;
	*lo = 0;

	for(bit = 0;bit < 64;bit++) {
		if(b & (0x1ull << bit)) {
			tmplo = a << bit;
			tmphi = a >> (64 - bit);
			*hi += tmphi + carry_of_64bit_add(*lo, tmplo);
			*lo += tmplo;
		}
	}

	return;
}

