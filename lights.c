#include "minirt.h"

tuple	*normal_at(void	*object,tuple	*point)
{
	t_sphere	*sphere;
	tuple	*object_point;
	float	**point_matrix;
	tuple	*object_normal;
	tuple	*world_normal;
	tuple	*world_point;
	float	**I;



	sphere = (t_sphere *)object;

	I = inverse(sphere->transform,4,4);
	point_matrix = matrix_mul(I,tuple_to_mx(point),4,1,false,true);
	// object_point = mx_to_tuple(point_matrix,4);

	print_matrix(point_matrix,4,1);
	// print_tuple(object_point);
	// free(object_point);
	// free_matrix(point_matrix,true);
	// free_matrix(I,4);
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

