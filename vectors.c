#include "minirt.h"

tuple	*new_tuple(float x, float y, float z, short id)
{
	tuple	*new;

	new = malloc(sizeof(tuple));
	if (!new)
		exit(1);
	new->x = x;
	new->y = y;
	new->z = z;
	new->id = id;
	return (new);
}

tuple	*vector(float x, float y, float z)
{
	tuple	*new;

	new = malloc(sizeof(tuple));
	if (!new)
		exit(1);
	new->x = x;
	new->y = y;
	new->z = z;
	new->id = 0;
	return (new);
}

tuple	*point(float x, float y, float z)
{
	tuple	*new;

	new = malloc(sizeof(tuple));
	if (!new)
		exit(1);
	new->x = x;
	new->y = y;
	new->z = z;
	new->id = 1;
	return (new);
}

void	print_tuple(tuple *a)
{
	printf("x: %f, y: %f, z: %f, id: %d\n", a->x, a->y, a->z, a->id);
}

int	compare_tuple(tuple *a, tuple *b)
{
	if (magnitude(a) - magnitude(b) < 0.0001)
		return (1);
	return (0);
}

tuple	operation_tuples(tuple *a, tuple *b, char operation)
{
	tuple	*new;

	new = malloc(sizeof(tuple));
	if (!new)
		exit(1);
	if (operation == '+')
	{
		new->x = a->x + b->x;
		new->y = a->y + b->y;
		new->z = a->z + b->z;
		new->id = a->id + b->id;
	}
	else if (operation == '-')
	{
		new->x = a->x - b->x;
		new->y = a->y - b->y;
		new->z = a->z - b->z;
		new->id = a->id - b->id;
	}
	else if (operation == '*')
	{
		new->x = a->x * b->x;
		new->y = a->y * b->y;
		new->z = a->z * b->z;
	}
	else if (operation == '/')
	{
		new->x = a->x / b->x;
		new->y = a->y / b->y;
		new->z = a->z / b->z;
	}
	else if (operation == 'x')
	{
		new->x = a->y * b->z - a->z * b->y;
		new->y = a->z * b->x - a->x * b->z;
		new->z = a->x * b->y - a->y * b->x;
	}
	if (new->id > 1)
		new->id = 1;
	return (*new);
}

tuple	*scalar_tuple(tuple *a, float scalar, char operation)
{
	tuple	*new;

	new = malloc(sizeof(tuple));
	if (!new)
		exit(1);
	if (operation == '*')
	{
		new->x = a->x * scalar;
		new->y = a->y * scalar;
		new->z = a->z * scalar;
	}
	else if (operation == '/')
	{
		new->x = a->x / scalar;
		new->y = a->y / scalar;
		new->z = a->z / scalar;
	}
	else if (operation == 'n')
	{
		new->x = -a->x;
		new->y = -a->y;
		new->z = -a->z;
	}
	else if (operation == '1')
	{
		new->x/= magnitude(a);
		new->y/= magnitude(a);
		new->z/= magnitude(a);
	}
	return (new);
}

float	magnitude(tuple *a)
{
	return (sqrt(a->x * a->x + a->y * a->y + a->z * a->z));
}
