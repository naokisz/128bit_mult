#include "128bit_mult.h"
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

void mul128_asm_x86_64(uint64_t a, uint64_t b, uint64_t *lo, uint64_t *hi)
{
	__asm__("mul %%rdx":
	"=a" (*lo), "=d" (*hi):
	"a" (a), "d" (b));
	
}

int main() {

	int bit;
	uint64_t a = 0, b = 0, lo_asm, hi_asm, lo, hi;

	for(;;) {
		for(;;) {
			printf("a=%"PRIu64"\t", a);
			printf("b=%"PRIu64"\n", b);
			mul128_asm_x86_64(a, b, &lo_asm, &hi_asm);
			mult_128bit(a, b, &lo, &hi);
			if(lo_asm != lo || hi_asm != hi) {
				printf("Not much!!!!!!!!\n");
				printf("a=%"PRIu64"\nb=%"PRIu64"\n", a, b);
	
				printf("hi=%"PRIX64"\nlo=%"PRIX64"\n", hi, lo);
				printf("hi_asm=%"PRIX64"\nlo_asm=%"PRIX64"\n", hi_asm, lo_asm);
				return -1;
			}
			if(b == UINT64_MAX) break;
			else b++;
		}
		if(a == UINT64_MAX) break;
		else a++;
	}

	return 0;
}

