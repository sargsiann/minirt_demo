#include "minirt.h"
void	put_square(int x, int y, t_image *image, int color)
{
	int i = 0;
	int j = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			my_pixel_put(x + i, y  + j, image, color);
			j++;
		}
		i++;
	}
}

/* EXERCISE 1 AND 0

EXERCISE 0

t_projectile tick(t_projectile p, t_env e)
{
	p.pos = (tuple *)(tuples_operation(p.pos,p.velocity,ADD));
	p.velocity = (tuple *)(tuples_operation(p.velocity,
		(tuple *)(tuples_operation(e.gravity,e.wind,ADD)),ADD));
	print_tuple(p.pos); 
	return (p);
}

void	render(t_canvas *canvas)
{
	t_projectile p;
	t_env e;
	p.pos = point(0,720,0);
	p.velocity = vector(10,-20,0);
	e.gravity = vector(0,0.5,0);
	e.wind = vector(-0.1,0,0);
	while (p.pos->y <= 720)
	{
		p = tick(p,e);
		put_square(p.pos->x,p.pos->y,canvas->image,0x00ff00);
	}
}
*/


int	close(int status)
{
	exit(status);
}

int	key_hook(int key, void *param)
{
	if (key == ESC)
		close(0);
}

t_color	*colors_operation(t_color c1, t_color t2, char operation)
{
	t_color *res;

	res = malloc(sizeof(t_color));
	if (!res)
		exit(1);
	if (operation == ADD)
	{
		res->r = c1.r + t2.r;
		res->g = c1.g + t2.g;
		res->b = c1.b + t2.b;
	}
	else if (operation == SUB)
	{
		res->r = c1.r - t2.r;
		res->g = c1.g - t2.g;
		res->b = c1.b - t2.b;
	}
	else if (operation == MUL)
	{
		res->r = c1.r * t2.r;
		res->g = c1.g * t2.g;
		res->b = c1.b * t2.b;
	}
	else if (operation == DIV)
	{
		res->r = c1.r / t2.r;
		res->g = c1.g / t2.g;
		res->b = c1.b / t2.b;
	}
	return (res);
}

int		rgb_to_color(short r, short g, short b)
{
	return (r << 16 | g << 8 | b);
}

void	my_pixel_put(int x, int y, t_image *image, int color)
{
	if (x < 0 || x >= 1080 || y < 0 || y >= 720)
		return ;
	char *addr = image->addres + x * (image->bpp / 8) + y * image->line;
	*(unsigned int *)addr = color;
}

int	mouse_hook(int b, int x, int y, void *param)
{
	t_canvas *canvas = param;
	put_square(x, y, canvas->image, rgb_to_color(255, 0, 0));
}

void	init_image(t_image **img, void *mlx)
{
	*img = malloc(sizeof(t_image));
	if (!img)
		exit(1);
	(*img)->img_ptr = mlx_new_image(mlx,1080, 720);
	(*img)->addres = mlx_get_data_addr((*img)->img_ptr,
		&(*img)->bpp, &(*img)->line, &(*img)->endian);
}

int loop_hook(void *param)
{
	t_canvas *canvas = param;
	mlx_put_image_to_window(canvas->mlx, canvas->win, canvas->image->img_ptr, 0, 0);
}

tuple	*canvas_cors(tuple *p)
{
	return point(p->x + WIDTH/2,HEIGHT/2 - p->y,p->z);
}

void	render(t_canvas *canvas)
{
	t_ray *r;
	t_intersect	*it;
	t_sphere	*sp;
	tuple	*pos;
	float	w_size;
	float	w_y;
	float	w_x;

	w_size = 7;
	sp = new_sphere(1);
	sp->transform = new_scale(0.5,0.5,0.5);
	sp->t_type = SCALE;
	float px_size = 7.0/100; // PROJECTING CANVAS POSITION TO REAL LIFE POSITION
	for (int i = 0;i < 100;i++)
	{
		w_y = 3.5 - px_size * i; // PROJECTING CANVAS POSITION TO REAL LIFE POSITION
		for (int j = 0;j < 100;j++)
		{
			w_x = px_size * j - 3.5;
			pos = point(w_x,w_y,10); // GETTING POINT OF IN WALL BY REAL LIFE SIZES
			r = new_ray(point(0,0,-5),tuple_operation(
				vector(pos->x,pos->y,pos->z - (-5)),NORM,0)); // CREATING RAY FROM ORIGIN TO WALL NORMALIZING VECTOR
			it = intersect(r,sp);
			if (it->count > 0) // IF WE HAVE INTERSECTION IN THAT CANVAS POINT CASTED TO REAL-WORLD WE PUT PIXEL
				my_pixel_put(i,j,canvas->image,0xff0000);
		}	
	}
}

// void	render(t_canvas *canvas)
// {
// 	float	**cen;

// 	cen = new_matrix(4,1);
// 	cen[0][0] = WIDTH/2;
// 	cen[1][0] = HEIGHT/2;
// 	cen[2][0] = 0;
// 	cen[3][0] = 1;
// 	float	**pos;

// 	pos = new_matrix(4,1);
// 	pos[0][0] = 10;
// 	pos[1][0] = 10;
// 	pos[2][0] = 0;
// 	pos[3][0] = 1;
// 	put_square(cen[0][0],cen[1][0],canvas->image,0xff0000);

// 	float	**r = new_rotation_z(PI/180);
// 	int i = 0;
// 	while (i< 360)
// 	{
// 		pos = matrix_mul(r,pos,4,1);
// 		// tuple *print = canvas_cors(pos)
// 		put_square(pos[0][0] * 10 + WIDTH/2,HEIGHT/2 - pos[1][0] * 10,canvas->image,0x0000ff);	
// 		i++;
// 	}
// }



// void	render(t_canvas *canvas)
// {
// 	t_ray	*ray;
// 	tuple	*origin;
// 	tuple	*direction;
// 	char	z;
// 	char	size;

// 	origin = point(0,0,-5);
// 	z = 10;
// 	size = 7;
// }

void	init_canvas(t_canvas *canvas)
{
	canvas = malloc(sizeof(t_canvas));
	if (!canvas)
		exit(1);
	canvas->mlx = mlx_init();
	canvas->win = mlx_new_window(canvas->mlx, 1080,720, "Minirt");
	init_image(&canvas->image, canvas->mlx);
	render(canvas);
	mlx_put_image_to_window(canvas->mlx, canvas->win, canvas->image->img_ptr, 0, 0);
	mlx_hook(canvas->win,17,0,close,NULL);
	mlx_mouse_hook(canvas->win,mouse_hook,canvas);
	mlx_key_hook(canvas->win,key_hook,NULL);
	mlx_loop(canvas->mlx);
}