#include "minirt.h"


void	free_matrix(float **m, int row)
{
	int	i;

	i = -1;
	while (++i < row)
		free(m[i]);
	free(m);
}

void	free_ray(t_ray *r)
{
	if (r->origin)
		free(r->origin);
	if (r->direction)
		free(r->direction);
	free(r);
}

void	free_spheres(t_sphere *s)
{
	t_sphere	*tmp;

	tmp = s;
	if (!tmp)
		return ;
	while (s)
	{
		tmp = s;
		s = s->next;
		if (tmp->center)
			free(tmp->center);
		if (tmp->transform)
			free_matrix(tmp->transform,4);
		free(tmp->m->color);
		free(tmp->m);
		free(tmp);
	}
	free(s);
}

void	free_intersections(t_intersect *i)
{
	t_intersect	*tmp;

	tmp = i;
	if (!tmp)
		return ;
	while (i)
	{
		tmp = i;
		i = i->next;
		if (tmp->times)
			free(tmp->times);
		free(tmp);
	}
	free(i);
}

void	print_spheres(t_sphere *s)
{
	while (s)
	{
		printf("--------------------\n");
		printf("id: %d\n", s->id);
		printf("sphere\n");
		printf("center: ");
		print_tuple(s->center);
		printf("radius: %.2f\n", s->r);
		s = s->next;
		printf("--------------------\n");
	}
}

void	print_intersection(t_intersect *i)
{
	if (!i)
		return ;
	printf("--------------------\n");
	printf("count %d\n", i->count);
	for (int j = 0; j < i->count; j++)
		printf("time: %.2f\n", i->times[j]);
	printf("--------------------\n");
}

void	print_intersections(t_intersect *i)
{
	if (!i)
		return ;
	while (i)
	{
		print_intersection(i);
		i = i->next;
	}
}

void	f_swap(float *t1,float *t2)
{
	float tmp;

	tmp = *t1;
	*t1 = *t2;
	*t2 = tmp;
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

bool	is_inside(tuple **n, tuple *e_v){
	float *dot;
	tuple	*tmp;

	dot = tuples_operation(*n,e_v,SCL_MUL);
	if (*dot < 0)
	{
		tmp = vector(-(*n)->x,(*n)->y,(*n)->z);
		free(*n);
		free(dot);
		*n = tmp;
		return true;
	}
	return false;
}