#include "minirt.h"

void	free_matrix(float **m, int row)
{
	int	i;

	i = -1;
	while (++i < row)
		free(m[i]);
	free(m);
}

void	free_intersections(t_intersect *i)
{
	t_intersect	*tmp;

	while (i)
	{
		tmp = i;
		i = i->next;
		free(tmp->times);
		free(tmp);
	}
	free(i);
}

void	print_intersection(t_intersect *i)
{
	printf("--------------------\n");
	printf("count %d\n", i->count);
	for (int j = 0; j < i->count; j++)
		printf("time: %.2f\n", i->times[j]);
	printf("--------------------\n");
}

void	print_intersections(t_intersect *i)
{
	while (i)
	{
		print_intersection(i);
		i = i->next;
	}
}

void	print_ray(t_ray *r)
{
	printf("origin: ");
	print_tuple(r->origin);
	printf("direction: ");
	print_tuple(r->direction);
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