#ifndef MINIRT_H
# define MINIRT_H

# define EPSILON 0.0001

# define WIDTH 720
# define HEIGHT 1080

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

typedef struct s_tuple
{
	float	x;
	float	y;
	float	z;
	short	id;
}	tuple;

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

typedef struct s_projectile
{
	tuple	*pos;
	tuple	*velocity;
} t_projectile;

typedef struct s_env
{
	tuple	*gravity;
	tuple	*wind;	
} t_env;


int		is_eq(float a, float b);
void	*tuples_operation(tuple *t1, tuple *t2, int operation);
void	*tuple_operation(tuple *t1, int operation, float scalar);
tuple	*point(float x, float y, float z);
tuple	*vector(float x, float y, float z);
void	print_tuple(tuple *t);
void	init_canvas(t_canvas *canvas);
void	my_pixel_put(int x, int y, t_image *image, int color);
int		rgb_to_color(short r, short g, short b);
t_color	*colors_operation(t_color c1, t_color t2, char operation);\
void	put_square(int x, int y, t_image *image, int color);

#endif