#include <stdio.h>
#include <stdint.h>

int main()
{
	uint32_t a[2];
	uint32_t b[2];

	a[0] = 1000;
	a[1] = 2000;

	b[0] = 3000;
	b[1] = 4000;

	*(uint64_t *)a += *(uint64_t *)b;

	printf ("%d, %d\n", a[0], a[1]);

	*(uint64_t *)a = *(uint64_t *)b;

	printf ("%d, %d", a[0], a[1]);
}