#ifndef MINIRT_H
# define MINIRT_H

# define EPSILON 0.0001

# define NEG 0
# define ADD 1
# define SUB 2
# define MUL 3
# define DIV 4
# define VEC_MUL 7
# define SCL_MUL 8
# define MAG 9
# define NORM 10

# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	short	id;
}	tuple;

int		is_eq(float a, float b);
void	*tuples_operation(tuple *t1, tuple *t2, int operation);
void	*tuple_operation(tuple *t1, int operation, float scalar);
tuple	*point(float x, float y, float z);
tuple	*vector(float x, float y, float z);
void	print_tuple(tuple *t);

#endif