#include "minirt.h"

// INITING MUTEX FOR ONE AT ONCE ACCESING SAME MEMORY


int	close(int s)
{
	exit(s);
}

t_color	*new_color(unsigned char r, unsigned char g, unsigned char b)
{
	t_color *color;

	color = malloc(sizeof(t_color));
	if (!color)
		exit(1);
	color->r = r;
	color->g = g;
	color->b = b;
	return (color);
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

int		rgb_to_color(t_color	*color)
{
	return (color->r << 16 | color->g << 8 | color->b << 0);
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
	if (!*img)
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
	int		color;


	t_light	*light;
	t_ray *ray;
	t_sphere *sphere;
	t_intersect *inter;
	t_intersect	*hit;

	tuple	*eye_pos = NULL;
	tuple	*ray_dir ;
	tuple	*it_pos = NULL;
	tuple	*normal = NULL;
	tuple	*eye_vec = NULL;
	tuple	*tmp;

	t_material *m;


	wall_size = 7.0;
	pixel_size = 7.0 / 300;
	w_x = 0;
	w_y = 0;
	w_z = 20;


	sphere = new_sphere(1);
	sphere->m = material(0.1,0.9,0.9,20);
	set_transform(&sphere,new_translation(-2,0,0),TRSL);
	sphere->m->color = point(255,255,255);

	t_sphere	*sphere2 = new_sphere(2);
	sphere2->m = material(0.1,0.9,1,10);
	sphere2->m->color = point(255,255,0);
	
	sphere->next = sphere2;
	// set_transform(&sphere2,new_scale(1,0.5,0.5),SCALE);
	// set_transform(&sphere2,new_translation(),TRSL);

	light = new_light();
	eye_pos = point(0,0,-20);

	light->pos = point(-4,1,-4);
	light->intens = point(1,1,1);
	
	for (int i = 0; i<300; i++)
	{
		w_y = 3.5 - pixel_size * i;
		for (int j = 0; j < 300; j++)
		{
			w_x = j * pixel_size - 3.5;

			tmp = point(w_x,w_y,(w_z - (-20)));
			ray_dir = tuple_operation(tmp,NORM,0);

			free(tmp);
			ray = new_ray(eye_pos,ray_dir);

			// GETTING INTERSECTIONS OF SPHERES WITH RAY IN THAT EXACT POINT

			inter = get_sphere_intersections(sphere,ray);
			hit = find_hit(inter);

			if (hit)
			{
				// FINDING POSITION WHERE RAY INTERSECTED THE SPHERE

				it_pos = position(ray,hit->times[0]);

				// EYE VECTOR SHOWING FROM IT_POS TO CAMERA OR JUST WE CAN NEGATE THE DIRECTION VEC OF RAY

				eye_vec = tuple_operation(ray->direction,NEG,0);
				
				// LIGHT VECTOR SHOWING FROM LIGHT SOURCE TO INTERSECTION POSITION

				// SURFACE NORMAL IS A VECTOR SHOWING THE PEREPENDICULAR TO THAT SHPHERE IN THAT POINT
				// WEE NEED TO TRANSFORM NORMAL IF WE TRANSFORMED OUR OBJECT

				normal = normal_at(hit->s,it_pos);

				// REFLECTION VECTOR VECTOR DEFINED 

				// FINDING COLOR IN THAT EXACT POINT


				color = lighting(hit->s->m,light,it_pos,eye_vec,normal);

				// PUTTING THAT COLOR IN SCREEN
				
				my_pixel_put(j,i,canvas->image,color);
				

				// FREEING MEMORY OF LIGHTS
				free(normal);
				free(it_pos);
				free(eye_vec);
			}
			// FREEING THIS RAY 
			free(ray_dir);
			free(ray);

			// FREEING ALL INTERSECTIONS FOR THIS POINT HIT WILL BE FREED WITH THAT
			free_intersections(inter);
			
		}
	}

	// FREEING ALL THE MEMORY
	free(light->intens);
	free(light->pos);
	free(light);
	free(eye_pos);
	free_spheres(sphere);
	mlx_put_image_to_window(canvas->mlx, canvas->win, canvas->image->img_ptr, 0, 0);
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
	mlx_loop_hook(canvas->mlx,loop_hook,canvas);
}