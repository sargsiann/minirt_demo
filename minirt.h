#ifndef MINIRT_H

# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include "mlx.h"
# include <math.h>

typedef struct tuple
{
	float x;
	float y;
	float z;
	short id;
} tuple;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	int		t;
} t_color;

typedef struct t_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
} t_image;

typedef struct canvas
{
	int		width;
	int		height;
	void	*mlx;
	void	*win;
	t_image	img;
} canvas;

tuple	*new_tuple(float x, float y, float z, short id);
tuple	operation_tuples(tuple *a, tuple *b, char operation);
tuple	*scalar_tuple(tuple *a, float scalar, char operation);
float	magnitude(tuple *a);
void	print_tuple(tuple *a);
int		compare_tuple(tuple *a, tuple *b);
void	init_canvas(canvas *canvas, int width, int height);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
int		rgb_to_int(t_color *color);
t_color *colors_operarions(t_color *a, t_color *b, char operation);
t_color	*int_to_rgb(int color);
int		**new_matrix(int rows, int cols);
void	print_matrix(int **matrix, int rows, int cols);
void	free_matrix(int **matrix, int rows);
int		**matrix_mul(int **a, int **b, int rows, int cols);
int		**transpose_matrix(int **matrix, int rows, int cols);
int		**matrix_operation(int **a, int **b, int rows, int cols, char operation);
int		**submatrix(int **matrix, int rows, int cols, int row, int col);
int		**inverse_matrix(int **matrix, int rows, int cols);
float	cofactor(int **matrix, int rows, int cols, int row, int col);
float	determinant(int **matrix, int rows);

#endif