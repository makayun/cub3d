#include <stdio.h>
#include <stdbool.h>

typedef struct s_keys {
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	la;
	bool	ra;
}				t_keys;

int main()
{
    t_keys a;

    printf("%lu\n", sizeof(&a));
}