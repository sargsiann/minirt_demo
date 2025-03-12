#include "minirt.h"

// INITING MUTEX FOR ONE AT ONCE ACCESING SAME MEMORY


int	close(int s)
{
	exit(s);
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
	// put_square(x, y, canvas->image, rgb_to_color(255, 0, 0));
}

void	init_image(t_image **img, void *mlx)
{
	*img = malloc(sizeof(t_image));
	if (!img)
		exit(1);
	(*img)->img_ptr = mlx_new_image(mlx,300,300);
	(*img)->addres = mlx_get_data_addr((*img)->img_ptr,
		&(*img)->bpp, &(*img)->line, &(*img)->endian);
}

int loop_hook(void *param)
{
	t_canvas *canvas = param;
	mlx_put_image_to_window(canvas->mlx, canvas->win, canvas->image->img_ptr, 0, 0);
}


void	render(t_canvas *canvas)
{
	float	w_x,w_y,w_z;
	float	wall_size;
	float	pixel_size;
	float	it_time;

	t_ray *ray;
	t_sphere *sphere;
	t_intersect *inter;
	t_intersect	*hit;

	tuple	*eye_pos = NULL;
	tuple	*ray_dir ;
	tuple	*it_pos = NULL;
	tuple	*light_pos = NULL;
	tuple	*light_vec = NULL;
	tuple	*normal = NULL;
	tuple	*eye_vec = NULL;
	tuple	*reflect_vec = NULL;


	wall_size = 7.0;
	pixel_size = 7.0 / 300;
	w_x = 0;
	w_y = 0;
	w_z = 10;


	sphere = new_sphere(1);
	// set_transform(&sphere,new_translation(-0.5,1,0),TRSL);
	sphere->color = 0xff0000;

	t_sphere *sphere2 = new_sphere(2);
	// set_transform(&sphere2,new_translation(1,0,0),TRSL);
	// set_transform(&sphere2,new_scale(0.5,0.5,0.5),SCALE);
	sphere2->color = 0x00ff00;
	

	sphere->next = sphere2;
	sphere2->next = NULL;

	light_pos = point(-10,10,10);
	eye_pos = point(0,0,-5);
	
	for (int i = 150; i< 151; i++)
	{
		w_y = 3.5 - pixel_size * i;
		for (int j = 150; j < 151; j++)
		{
			w_x = j * pixel_size - 3.5;

			ray_dir = vector(w_x,w_y,w_z);
			ray = new_ray(eye_pos,ray_dir);

			// GETTING INTERSECTIONS OF SPHERES WITH RAY IN THAT EXACT POINT

			inter = get_sphere_intersections(sphere,ray);
			hit = find_hit(inter);

			if (hit)
			{
				it_pos = position(ray,hit->times[0]);
				normal = normal_at(hit->s,it_pos);
				// eye_vec = vector(0,0,-1);
				// reflect_vec = reflect(ray->direction,normal);
				// light_vec = tuples_operation(light_pos,it_pos,SUB);

				my_pixel_put(j,i,canvas->image,hit->s->color);
				
				// FREEING MEMORY OF LIGHTS
				free(it_pos);
				free(normal);
			}
			// FREEING THIS RAY 
			free(ray_dir);
			free(ray);

			// FREEING ALL INTERSECTIONS FOR THIS POINT HIT WILL BE FREED WITH THAT
			free_intersections(inter);

		}
	}

	// FREEING ALL THE MEMORY
	free(light_pos);
	free(eye_pos);
	free_spheres(sphere);
}

void	init_canvas(t_canvas *canvas)
{
	canvas = malloc(sizeof(t_canvas));
	if (!canvas)
		exit(1);
	canvas->mlx = mlx_init();
	canvas->win = mlx_new_window(canvas->mlx,300,300, "Minirt");
	init_image(&canvas->image, canvas->mlx);
	render(canvas);
	mlx_put_image_to_window(canvas->mlx, canvas->win, canvas->image->img_ptr, 0, 0);
	mlx_hook(canvas->win,17,0,close,NULL);
	mlx_mouse_hook(canvas->win,mouse_hook,canvas);
	mlx_key_hook(canvas->win,key_hook,NULL);
	mlx_loop(canvas->mlx);
}