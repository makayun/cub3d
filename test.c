#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

typedef struct s_pos
{
	float	x;
	float	y;
}				t_pos;

int main()
{
	double ff = 37.923378;
	int x = (int)(ff) * 4 % 64;
	printf("%d\n", x);

}