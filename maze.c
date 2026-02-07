#include <unistd.h>
#include <stdio.h>

#define A "o"
#define B "-"
#define C "|"
#define D " "

void	first_last(int x)
{
	int	width;

	width = x;
	while (width != 0)
	{
		if (width == x)
			printf(A);
		else if (width == 1)
			printf(A);
		else
			printf(B);
		width--;
	}
	printf("\n");
}

void	middle(int x)
{
	int	width;

	width = x;
	while (width != 0)
	{
		if (width == 1)
			printf(C);
		else if (width == x)
			printf(C);
		else
			printf(D);
		width--;
	}
	printf("\n");
}

void	rush(int x, int y)
{
	int	height;

	height = y -2;
	if (x <= 0 || y <= 0)
		return ;
	first_last(x);
	while (height > 0)
	{
		middle(x);
		height--;
	}
	if (y > 1)
	{
		first_last(x);
	}
}
