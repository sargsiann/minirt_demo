#include "minirt.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

int	rgb_to_int(t_color *color)
{
	return (color->r << 16 | color->g << 8 | color->b);
}

t_color *colors_operarions(t_color *a, t_color *b, char operation)
{
	t_color	*new;

	new = malloc(sizeof(t_color));
	if (!new)
		exit(1);
	if (operation == '+')
	{
		new->r = a->r + b->r;
		new->g = a->g + b->g;
		new->b = a->b + b->b;
	}
	else if (operation == '-')
	{
		new->r = a->r - b->r;
		new->g = a->g - b->g;
		new->b = a->b - b->b;
	}
	else if (operation == '*')
	{
		new->r = a->r * b->r;
		new->g = a->g * b->g;
		new->b = a->b * b->b;
	}
	else if (operation == '/')
	{
		new->r = a->r / b->r;
		new->g = a->g / b->g;
		new->b = a->b / b->b;
	}
	return (new);
}


t_color	*int_to_rgb(int color)
{
	t_color	*rgb;

	rgb = malloc(sizeof(t_color));
	if (!rgb)
		exit(1);
	rgb->r = (color & 0xFF0000) >> 16;
	rgb->g = (color & 0xFF00) >> 8;
	rgb->b = color & 0xFF;
	return (rgb);
}

int	free_all(canvas *canvas)
{
	mlx_destroy_image(canvas->mlx, canvas->img.img);
	mlx_destroy_window(canvas->mlx, canvas->win);
	mlx_destroy_display(canvas->mlx);
	free(canvas->mlx);
	exit(0);
}

int	key_hook(int keycode, canvas *canvas)
{
	if (keycode == 65307)
		free_all(canvas);
	printf("keycode: %d\n", keycode);	
	return (0);
}

void	ball_render(canvas *canvas)
{
	tuple	start_point = {0, canvas->height, 0, 1};
	tuple 	move_vector = {1.5, 1.2, 0, 0};
	tuple 	gravity_vec = {0, -0.004, 0, 0};
	int		s_y = move_vector.y;
	while (1)
	{
		start_point.x += move_vector.x;
		if (move_vector.y >= 0.6)
			start_point.y -= move_vector.y;
		else
			start_point.y += 1.2 -move_vector.y;
		my_mlx_pixel_put(&canvas->img, start_point.x, start_point.y, 0x00FF00);
		if (move_vector.y < 0)
			break;
		move_vector = operation_tuples(&move_vector, &gravity_vec, '+');
	}
}

void	clock_render(canvas *canvas)
{
	float **origin = new_matrix(4,1);
	origin[0][0] = canvas->width/2 + 10;
	origin[1][0] = canvas->height/2;
	origin[2][0] = 0;
	origin[3][0] = 1;
	float s_x = origin[0][0];
	float s_y = origin[1][0];
	// printf("origin: %f %f\n", origin[0][0], origin[1][0]);
	int i = 0;
	while (1)
	{
		origin = rotation_x(origin, 180/12);
		my_mlx_pixel_put(&canvas->img, origin[0][0], origin[1][0], 0x00FF00);
		if (origin[0][0] == s_x && origin[1][0] == s_y)
			break;
	}
}

int	render(canvas *canvas)
{
	clock_render(canvas);
	mlx_put_image_to_window(canvas->mlx, canvas->win, canvas->img.img, 0, 0);
	return (0);
}

void	save_to_img(t_image *img, int x, int y, t_color *color)
{
	my_mlx_pixel_put(img, x, y, rgb_to_int(color));
}

void	init_canvas(canvas *canvas, int width, int height)
{
	canvas->width = width;
	canvas->height = height;
	canvas->mlx = mlx_init();
	if (!canvas->mlx)
		exit(1);
	canvas->win = mlx_new_window(canvas->mlx, canvas->width, canvas->height, "miniRT");
	if (!canvas->win)
		exit(1);
	canvas->img.img = mlx_new_image(canvas->mlx, canvas->width, canvas->height);
	if (!canvas->img.img)
		exit(1);
	canvas->img.addr = mlx_get_data_addr(canvas->img.img, &canvas->img.bpp, &canvas->img.line_length, &canvas->img.endian);
	if (!canvas->img.addr)
		exit(1);
	mlx_key_hook(canvas->win, key_hook, canvas);
	mlx_loop_hook(canvas->mlx, render, canvas);
	mlx_hook(canvas->win, 17, 0, free_all, canvas);
	mlx_loop(canvas->mlx);
}