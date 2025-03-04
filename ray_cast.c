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
	t_ray *r2 = ray_operation(r,inverse(o->transform,4,4),o->t_type);	
	float a = *(float *)(tuples_operation(r2->direction, r2->direction, SCL_MUL));
	float b = 2 * *(float *)(tuples_operation(r2->direction, r2->origin, SCL_MUL));
	float c = *(float *)(tuples_operation(r2->origin,r2->origin, SCL_MUL)) - 1;
	float discriminant = b * b - 4 * a * c;
	t_intersect	*inter;

	inter = malloc(sizeof(t_intersect));
	if (!inter)
		return (NULL);
	inter->count = 0;
	inter->times = NULL;
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
	if (inter->count > 1 && inter->times[1] < inter->times[0])
		f_swap(&inter->times[1],&inter->times[2]);
	inter->s = o;
	inter->next = NULL;
	return (inter);
}


t_intersect	*get_sphere_intersections(t_sphere *sps,t_ray *r)
{
	t_intersect	**is_head;
	t_intersect	*is_tmp2;

	is_head = malloc(sizeof(t_intersect *));
	*is_head = NULL;
	while (sps)
	{
		is_tmp2 = intersect(r,sps);
		if (is_tmp2->count > 0)
		{
			addIntersection(is_head,is_tmp2);
		}
		sps = sps->next;
	}
	return (*is_head);
}


t_intersect	*find_hit(t_intersect *head)
{
	t_intersect	*min;
	float		min_float;
	float		val;

	min = NULL;
	val = MAX_DIR_VIS_TIME;
	while (head)
	{
		if (!head->times)
			head = head->next;
		min_float = head->times[0];
		if (min_float < val && min_float > 0)
		{
			val = min_float;
			min = head;	
		}
		head = head->next;
	}
	return (min);
}

t_ray	*ray_operation(t_ray *r, float **matrix,char op)
{
	t_ray	*res;
	tuple	*res_o;
	tuple	*res_d;

	res_o = mx_to_tuple(matrix_mul(matrix, tuple_to_mx(r->origin), 4, 1));
	if (op != TRSL)
		res_d = mx_to_tuple(matrix_mul(matrix, tuple_to_mx(r->direction), 4, 1));
	else
		res_d = vector(r->direction->x,r->direction->y,r->direction->z);
	res = new_ray(res_o, res_d);
	return (res);
}

t_sphere	*new_sphere(int id)
{
	t_sphere	*new;

	new = malloc(sizeof(t_sphere));
	if (!new)
		return (NULL);
	new->center = point(0,0,0);
	new->r = 1;
	new->id = id;
	new->transform = new_identity();
	new->t_type = IDM;
	return (new);
}

void	set_transform(t_sphere **s,float **t, char type)
{
	t_sphere	*tmp;

	tmp = *s;
	tmp->transform = matrix_mul(t,tmp->transform,4,4);
	tmp->t_type = type;
	return ;
}