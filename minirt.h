#ifndef MINIRT_H
# define MINIRT_H

# define EPSILON 0.0001
# define PI 3.14159265359

# define WIDTH 1080
# define HEIGHT 720

# define NEG 0
# define ADD 1
# define SUB 2
# define MUL 3
# define DIV 4
# define VEC_MUL 7
# define SCL_MUL 8
# define MAG 9
# define NORM 10
# define ESC 65307

# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "lib/lib.h"

typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	short	id;
}	tuple;

typedef struct s_sphere
{
	tuple	*center;
	float	r;
	char	id;
}	t_sphere;

typedef struct s_ray
{
	tuple	*origin;
	tuple	*direction;
}	t_ray;




typedef	struct s_intersect
{
	int		count;
	float	*times;
	void	*object;
	struct s_intersect	*next;
}	t_intersect;

typedef struct s_color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}	t_color;

typedef struct s_image
{
	int			bpp;
	int			line;
	int			endian;
	char		*addres;
	void		*img_ptr;
}	t_image;


typedef struct s_canvas
{
	void	*mlx;
	void	*win;
	t_image	*image;
} t_canvas;

// typedef struct s_projectile
// {
// 	tuple	*pos;
// 	tuple	*velocity;
// } t_projectile;

// typedef struct s_env
// {
// 	tuple	*gravity;
// 	tuple	*wind;	
// } t_env;

// UTILS

void	free_matrix(float **m, int row);
void	print_intersection(t_intersect *i);
void	print_matrix(float **m, int row, int col);
void	print_tuple(tuple *t);
int		is_eq(float a, float b);
void	print_tuple(tuple *t);

// TUPLES
void	*tuples_operation(tuple *t1, tuple *t2, int operation);
void	*tuple_operation(tuple *t1, int operation, float scalar);
tuple	*point(float x, float y, float z);
tuple	*vector(float x, float y, float z);

// CANVAS
void	init_canvas(t_canvas *canvas);
void	my_pixel_put(int x, int y, t_image *image, int color);
int		rgb_to_color(short r, short g, short b);
t_color	*colors_operation(t_color c1, t_color t2, char operation);\
void	put_square(int x, int y, t_image *image, int color);

// MATRIXES

float	**new_matrix(int row, int col);
float	**matrix_mul(float **a, float **b,char row,char col);
float	**tuple_to_mx(tuple *a);
void	transpose(float **a, char row, char col);
tuple	*mx_to_tuple(float **a);
float	**submatrix(float **a,char rows, char cols, char d_r,char d_c);
float	determinant(float **a, char rows, char cols);
float	**inverse(float **a, char rows, char cols);
float	cofactor(float **a, char rows, char cols, char r, char c);
void	free_matrix(float **m, int row);

// TRANSFORMATIONS

float	**new_translation(float x, float y, float z);
float	**new_scale(float x, float y, float z);
float	**new_rotation_x(float rad);
float	**new_rotation_y(float rad);
float	**new_rotation_z(float rad);
float	**new_shearing(float xy, float xz, float yx, float yz, float zx, float zy);

// RAY_CASTS

t_ray		*new_ray(tuple *o,tuple *d);
tuple		*position(t_ray *r,float t);
t_intersect	*intersect(t_ray *r,t_sphere *s);
void		addIntersection(t_intersect **head, t_intersect *node);

#endif