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
	
	object_point = mx_to_tuple(matrix_mul(I, tuple_to_mx(point), 4, 1, false, true));
	object_normal = vector(object_point->x,object_point->y,object_point->z);
	transpose(I,4,4);
	world_normal = mx_to_tuple(matrix_mul(I, tuple_to_mx(object_normal), 4, 1, false, true));
	world_normal->id = 0;
	free(object_point);
	free(object_normal);
	free(I);

	return (world_normal);
}

tuple	*reflect(tuple *in, tuple *normal)
{
	tuple	*res;
	float	dot;

	// 
	// dot =  2 * *(float *)tuples_operation(in, normal, SCL_MUL);
	// res = tuples_operation(in, tuple_operation(normal, MUL, dot), SUB);
	return (res);
}

t_light	*light(tuple *intensity,tuple *position)
{
	t_light	*l;

	l = malloc(sizeof(t_light));
	if (!l)
		return (NULL);
	l->intens = intensity;
	l->pos = position;
	return (l);
}

t_material	*material(float ambient, float diffuse, float specular, float shininess)
{
	t_material	*m;

	m = malloc(sizeof(t_material));
	if (!m)
		return (NULL);
	m->ambient = ambient;
	m->diffuse = diffuse;
	m->specular = specular;
	m->shininess = shininess;
	return (m);
}

