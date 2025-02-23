#include "minirt.h"

tuple	*vector(float x, float y, float z)
{
	tuple *vector;

	vector = malloc(sizeof(tuple));
	if (!vector)
		return (NULL);
	vector->x = x;
	vector->y = y;
	vector->z = z;
	vector->id = 0;
	return (vector);
}

void *tuple_operation(tuple *t1, int operation, float scalar)
{
	tuple *res;
	float	*fl_res;

	fl_res = malloc(sizeof(float));
	res = NULL;
	if (operation == MAG)
	{
		*fl_res = sqrt(t1->x * t1->x + t1->y * t1->y + t1->z * t1->z);
		return (fl_res);
	}
	res = malloc(sizeof(tuple));
	if (!res)
		return (NULL);
	if (operation == NEG)
	{
		return (vector(-t1->x, -t1->y, -t1->z));
	}
	if (operation == MUL)
	{
		res->x *= scalar;
		res->y *= scalar;
		res->z *= scalar;
	}
	if (operation == DIV)
	{
		res->x /= scalar;
		res->y /= scalar;
		res->z /= scalar;
	}
	if (operation == NORM)
	{
		float mag = *(float *)(tuple_operation(t1, MAG, 0));
		return (vector(t1->x / mag, t1->y / mag, t1->z / mag));
	}
	return (res);
}

void	*tuples_operation(tuple *t1, tuple *t2, int operation)
{
	tuple	*res;
	float	*fl_res;
	
	res = NULL;
	fl_res = malloc(sizeof(float));
	if (operation == SCL_MUL)
	{
		*fl_res = t1->x * t2->x + t1->z * t2->z + t1->z * t2->z;
		return  (fl_res);
	}
	res = malloc(sizeof(tuple));
	if (!res)
		return (NULL);
	if (operation == ADD)
	{
		res->x = t1->x + t2->x;
		res->y = t1->y + t2->y;
		res->z = t1->z + t2->z;
	} 
	if (operation == SUB)
	{
		return (vector(t1->x - t2->x, t1->y - t2->y, t1->z - t2->z));
	}
	if (operation == VEC_MUL)
	{
		return (vector(t1->y * t2->z - t1->z * t2->y, 
			t1->z * t2->x - t1->x * t2->z,
			t1->x * t2->y - t1->y * t2->x));
	}
	return (res);
}

tuple	*point(float x, float y, float z)
{
	tuple *point;

	point = malloc(sizeof(tuple));
	if (!point)
		return (NULL);
	point->x = x;
	point->y = y;
	point->z = z;
	point->id = 1;
	return (point);
}