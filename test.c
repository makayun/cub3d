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
	bool	map[] ={1,1,1,1,
					1,0,0,1,
					1,1,1,1};
	int		x = 4;
	int		y = 3;
	// int		size = x * y;

	int		px = 0;
	int		py = 1;

	int pos = (py * x + px); 
	printf ("%d\n", (int)map[pos]);


}