#include "minirt.h"

tuple	*normal_at(void	*object,tuple	*point)
{
	t_sphere	*sphere;
	tuple	*object_point;
	tuple	*object_normal;
	tuple	*world_normal;
	tuple	*world_point;
	float	**I;



	sphere = (t_sphere *)object;

	I = inverse(sphere->transform,4,4);
	
	object_point = mx_to_tuple(matrix_mul(I, tuple_to_mx(point), 4, 1));
	object_normal = vector(object_point->x,object_point->y,object_point->z);
	transpose(I,4,4);
	world_normal = mx_to_tuple(matrix_mul(I, tuple_to_mx(object_normal), 4, 1));
	world_normal->id = 0;

	return (world_normal);
}

tuple	*reflect(tuple *in, tuple *normal)
{
	tuple	*res;
	float	dot;

	dot =  2 * *(float *)tuples_operation(in, normal, SCL_MUL);
	res = tuples_operation(in, tuple_operation(normal, MUL, dot), SUB);
	return (res);
}