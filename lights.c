#include "minirt.h"

tuple	*normal_at(void	*object,tuple	*point)
{
	t_sphere	*sphere;
	tuple	*object_point;
	float	**point_matrix;
	tuple	*object_normal;
	tuple	*world_normal;
	tuple	*tmp;
	float	**I;

	sphere = (t_sphere *)object;

	I = inverse(sphere->transform,4,4);

	point_matrix = tuple_to_mx(point);

	// TRANSFORMS THE POINT INTO OBJECT SPACE
	object_point = mx_to_tuple(matrix_mul(I,point_matrix,4,1,false,true),true);
	
	// GETS THE NORMAL IN OBJECT SPACE
	object_normal = vector(object_point->x,object_point->y,object_point->z);
	
	// TRANSPOSES THE INVERSE MATRIX
	transpose(I,4,4);
	point_matrix = tuple_to_mx(object_normal);
	world_normal = mx_to_tuple(matrix_mul(I,point_matrix,4,1,false,true),true);

	// FREES
	free(object_normal);
	free(object_point);
	free_matrix(I,4);
	
	tmp = tuple_operation(world_normal,NORM,0);

	return (tmp);
}

tuple	*reflect(tuple *in, tuple *normal)
{
	tuple	*res;
	tuple	*tmp;
	float	dot;
	float	*dot_ptr;
	
	dot_ptr =  (float *)tuples_operation(in, normal, SCL_MUL);
	dot =  2 * *dot_ptr;
	tmp = tuple_operation(normal, MUL, dot);
	res = tuples_operation(in, tmp, SUB);
	free(dot_ptr);
	free(tmp);
	return (res);
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

int clamp(int value, int min, int max) {
    if (value < min) return min;  // Если меньше min — вернёт min
    if (value > max) return max;  // Если больше max — вернёт max
    return value;                 // Если внутри диапазона — вернёт value
}

int	lighting(t_material *m, t_light *l, tuple *it_point, tuple	*eye_v,tuple *normal)
{
	tuple	*effective_color;
	tuple	*light_v;
	tuple	*tmp;
	tuple	*ambient;
	tuple	*diffuse;
	tuple	*specular;
	tuple	*reflect_v;
	float	*light_dot_normal;
	float	*reflect_dot_eye;
	float	factor;
	
	// EFFECTIVE COLOR
	effective_color = point(
	m->color->x * l->intens->x,
	m->color->y * l->intens->y,
	m->color->z * l->intens->z);
	
	// LIGHT VECTOR FINDING AND NORMALIZING

	tmp = tuples_operation(l->pos, it_point, SUB);
	light_v = tuple_operation(tmp, NORM, 0);

	free(tmp);

	// AMBIENT
	ambient = tuple_operation(effective_color,MUL,m->ambient);

	// FINDING WHETER LIGHT REFLECT THE EYE SIDE OR NOT
	tmp = tuple_operation(light_v,NEG,0);

	light_dot_normal = tuples_operation(normal,light_v,SCL_MUL);

	// IF THE LIGHT IS ON OTHER SIDE

	if (*light_dot_normal < 0)
	{
		diffuse = point(0,0,0);
		specular = point(0,0,0);
	}
	else
	{
		// ELSE FINDING THE DIFFUSE
		
		diffuse = tuple_operation(effective_color,MUL, *light_dot_normal * m->diffuse);
		reflect_v = reflect(tmp,normal);
		reflect_dot_eye = tuples_operation(reflect_v,eye_v,SCL_MUL);
		
		
		if (*reflect_dot_eye < 0){
			specular = point(0,0,0);
		}
		else
		{
			factor = pow(*reflect_dot_eye, m->shininess);
			// MULTIPLYING BY 255 FOR GETTING LIGHT COLOR NOT THE INTENST
			specular = tuple_operation(l->intens,MUL,m->specular * factor * 255);	
		}
		free(reflect_dot_eye);
	}
	tmp = tuples_operation(ambient,diffuse,ADD);
	tuple	*final_color = tuples_operation(tmp,specular,ADD);
	
	// FIXING EDGES FOR NOT GOING ALONG AND MAKE BLACK

	final_color->x = clamp((int)final_color->x,0,255);
	final_color->y = clamp((int)final_color->y,0,255);
	final_color->z = clamp((int)final_color->z,0,255);

	free(tmp);


	int color = (int)final_color->x << 16 | (int)final_color->y << 8 | (int)final_color->z;
	
	free(diffuse);
	free(light_dot_normal);
	free(ambient);
	free(effective_color);
	free(light_v);
	
	return (color);
}

t_light	*new_light()
{
	t_light	*l;

	l = malloc(sizeof(t_light));
	if (!l)
		return (NULL);
	l->intens = NULL;
	l->pos = NULL;
	return (l);
}

