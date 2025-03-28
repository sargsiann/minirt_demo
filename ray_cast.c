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
	tuple	*tmp;

	tmp = tuple_operation(ray->direction, MUL, time);
	pos = tuples_operation(ray->origin, tmp, ADD);
	free(tmp);
	return(pos);
}

void	addIntersection(t_intersect **head, t_intersect *node)
{
	if (!node)
		return;
	node->next = NULL; // Обнуляем, чтобы не тащить мусор

	if (!*head)
	{
		*head = node;
		return;
	}

	t_intersect	*tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

t_intersect	*intersect(t_ray *r, t_sphere *o)
{
	float **I = inverse(o->transform, 4, 4);
	t_ray *r2 = ray_operation(r, I, o->t_type);

	float *a_ptr = (float *)tuples_operation(r2->direction, r2->direction, SCL_MUL);
	float *b_ptr = (float *)tuples_operation(r2->origin, r2->direction, SCL_MUL);
	float *c_ptr = (float *)tuples_operation(r2->origin, r2->origin, SCL_MUL);


	float a = *a_ptr;
	float b = 2 * (*b_ptr);
	float c = (*c_ptr) - 1;

	

	float discriminant = (b * b) - (4 * a * c);

	t_intersect *inter = malloc(sizeof(t_intersect));
	if (!inter)
		return (NULL);
	inter->count = 0;
	inter->times = NULL;

	if (discriminant < 0)
		inter->count = 0;
	else
	{
		inter->count = (discriminant == 0) ? 1 : 2;
		inter->times = malloc(sizeof(float) * inter->count);
		if (!inter->times)
		{
			free(inter);
			return (NULL);
		}

		inter->times[0] = (-b - sqrt(discriminant)) / (2 * a);
		if (inter->count == 2)
			inter->times[1] = (-b + sqrt(discriminant)) / (2 * a);
		if (inter->count == 2 && (inter->times[0] > inter->times[1] || inter->times[0] <= 0))
			f_swap(&inter->times[0], &inter->times[1]);
	}

	inter->s = o;
	inter->next = NULL;
	if (!I || !r2 || !a_ptr || !b_ptr || !c_ptr)
	{
		free(a_ptr);
		free(b_ptr);
		free(c_ptr);
		free(r2);
		free_matrix(I, 4);
		return (NULL);
	}
	return (inter);
}

t_intersect	*get_sphere_intersections(t_sphere *sps, t_ray *r)
{
	t_intersect	*is_head = NULL;
	t_intersect	*is_tmp2;

	while (sps)
	{
		is_tmp2 = intersect(r, sps);
		if (is_tmp2 && is_tmp2->count > 0)
		{
			addIntersection(&is_head, is_tmp2);
		}
		else
			free(is_tmp2);
		sps = sps->next;
	}
	return (is_head);
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
	float	**ray_o_matrix;
	float	**ray_d_matrix;
	float	**tmp;


	ray_o_matrix = tuple_to_mx(r->origin);
	ray_d_matrix = tuple_to_mx(r->direction);
	tmp = matrix_mul(matrix, ray_o_matrix, 4, 1, false, true);
	res_o = mx_to_tuple(tmp,false);
	free_matrix(tmp,4);
	if (op != TRSL)
	{
		tmp = matrix_mul(matrix, ray_d_matrix, 4, 1, false, true);
		res_d = mx_to_tuple(tmp,false);
		free_matrix(tmp,4);
	}
	else
	{
		res_d = vector(r->direction->x,r->direction->y,r->direction->z);
		free_matrix(ray_d_matrix,4);
	}
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
	new->next = NULL;
	return (new);
}

void	set_transform(t_sphere **s,float **t, char type)
{
	t_sphere	*tmp;
	float		**t_mtx;

	tmp = *s;
	t_mtx = tmp->transform;
	tmp->transform = matrix_mul(t_mtx,t, 4, 4, true, true);
	tmp->t_type = type;
	return ;
}