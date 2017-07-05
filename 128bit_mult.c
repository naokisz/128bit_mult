#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t hi, lo;

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

void mult_128bit(uint64_t a, uint64_t b) {

	uint64_t tmphi, tmplo;
	int bit;

	hi = 0;
	lo = 0;

	for(bit = 0;bit < 64;bit++) {
		if(b & (0x1ull << bit)) {
			tmplo = a << bit;
			tmphi = a >> (64 - bit);
			hi += tmphi + carry_of_64bit_add(lo, tmplo);
			lo += tmplo;
		}
	}

	return;
}

int main() {

	uint64_t a, b;
	int bit;

	printf("a=");
	scanf("%"SCNx64"", &a);

	printf("b=");
	scanf("%"SCNx64"", &b);
	
	mult_128bit(a, b);
	printf("a*b=");
	for(bit = 64;bit >= 1;bit--) {
		if(hi & (0x1ull << (bit - 1))) {
			printf("1");
		} else {
			printf("0");
		}
	}
	for(bit = 64;bit >= 1;bit--) {
		if(lo & (0x1ull << (bit - 1))) {
			printf("1");
		} else {
			printf("0");
		}
	}
	printf("\n\n");

	printf("a*b=%"PRIX64" %"PRIX64"\n", hi, lo);

	return 0;
}

