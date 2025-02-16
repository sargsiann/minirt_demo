#include "minirt.h"

int main(int argc, char **argv)
{
	canvas	canvas;
	int 	**a;

	a = new_matrix(2, 3);
	int k = 1;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			a[i][j] = k;
			k++;
		}
	}
	print_matrix(a, 2, 3);
	printf("\n");
	a = transpose_matrix(a, 2, 3);
	print_matrix(a, 3, 2);
	return (0);
}