#include <stdio.h>
#include <stdbool.h>

typedef struct s_test
{
	int		zero;
	bool one;
	bool two;
	bool three;
	bool four;
	// bool five;
}				t_test;

int main()
{
	printf("%lu\n", sizeof(t_test));
}