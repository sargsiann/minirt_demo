#include "minirt.h"

void	free_matrix(float **m, int row)
{
	int	i;

	i = -1;
	while (++i < row)
		free(m[i]);
	free(m);
}

void	print_matrix(float **m, int row, int col)
{
	int	i;
	int	j;

	i = -1;
	printf("--------------------\n");
	while (++i < row)
	{
		j = -1;
		while (++j < col)
			printf("%.2f ", m[i][j]);
		printf("\n");
	}
	printf("--------------------\n");
}

void	print_tuple(tuple *t)
{
	printf("x: %.2f, y: %.2f, z: %.2f\n", t->x, t->y, t->z);
}

int	is_eq(float a, float b)
{
	return (a - b < EPSILON);
}