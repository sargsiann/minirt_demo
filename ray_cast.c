#include "minirt.h"

t_ray	*new_ray(tuple *o,tuple *d)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	ray->origin = o;
	ray->direction = d;
	return (ray);
}

tuple	*position(t_ray	*ray, float	time)
{
	tuple	*pos;

	pos = tuples_operation(ray->origin, 
		tuple_operation(ray->direction, MUL, time), 
		ADD);
	return(pos);
}

char	getIntesectCount(t_ray *r)
{
	float a = r->direction->x * r->direction->x * +
	r->direction->y * r->direction->y +
	r->direction->z * r->direction->z;
	float b = 2 * (r->origin->x * r->direction->x +
	r->origin->y * r->direction->y +
	r->origin->z * r->direction->z);
	float c = r->origin->x * r->origin->x +
	r->origin->y * r->origin->y +
	r->origin->z * r->origin->z - 1;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	else if (discriminant == 0)
		return (1);
	else
		return (2);
}

void	addIntersection(t_intersect **head, t_intersect *node)
{
	t_intersect	*tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

t_intersect	*intersect(t_ray	*r,t_sphere	*o)
{

	float a = *(float *)(tuples_operation(r->direction, r->direction, SCL_MUL));
	float b = 2 * *(float *)(tuples_operation(r->direction, r->origin, SCL_MUL));
	float c = *(float *)(tuples_operation(r->origin, r->origin, SCL_MUL)) - 1;

	float discriminant = b * b - 4 * a * c;
	t_intersect	*inter;

	inter = malloc(sizeof(t_intersect));
	if (!inter)
		return (NULL);
	if (discriminant < 0)
		inter->count = 0;
	else if (discriminant == 0)
	{
		inter->count = 1;
		inter->times = malloc(sizeof(float));
		if (!inter->times)
			return (NULL);
	}
	else
	{
		inter->count = 2;
		inter->times = malloc(sizeof(float) * 2);
		if (!inter->times)
			return (NULL);
	}
	if (inter->count > 0)
		inter->times[0] = (-b + sqrt(discriminant)) / (2 * a);
	if (inter->count == 2)
		inter->times[1] = (-b - sqrt(discriminant)) / (2 * a);
	inter->object = o;
	inter->next = NULL;
	return (inter);
}

float	findMaxFloat(float *a, int count)
{
	float	max;
	int	i;

	i = -1;
	max = a[0];
	while (++i < count)
	{
		if (a[i] > max)
			max = a[i];
	}
	return (max);
}


t_intersect	*find_hit(t_intersect *head)
{
	t_intersect	*max;
	float	max_float;
	float	val;

	max = head;
	head = head->next;
	while (head)
	{
		val = findMaxFloat(head->times, head->count);
		if (val < max_float)
		{
			max = head;
			max_float = val;
		}
		head = head->next;
	}
	return (max);
}