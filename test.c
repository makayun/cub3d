#include <stdio.h>
#include <math.h>

#define BLOCK 32

int	cub_count_shift(void)
{
	int shift;
	int	map_block;

	map_block = BLOCK;
	shift = 0;
	while (map_block)
	{
		if ((map_block >> shift) == 1)
			break ;
		shift++;
	}
	return (shift);
}

int main()
{
	printf ("%d %d\n", cub_count_shift(), (int)log2(BLOCK));
}