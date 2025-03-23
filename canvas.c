#include "minirt.h"

// INITING MUTEX FOR ONE AT ONCE ACCESING SAME MEMORY

void render(t_word	**word);
void	black_image(t_image *img);

int	close(int s)
{
	exit(s);
}


void rotate_x(t_word **word, double angle)
{
	double y = (*word)->eye_pos->y;
	double z = (*word)->eye_pos->z;

	(*word)->eye_pos->y = y * cos(angle) - z * sin(angle);
	(*word)->eye_pos->z = y * sin(angle) + z * cos(angle);
}

void rotate_y(t_word **word, double angle)
{
	double x = (*word)->eye_pos->x;
	double z = (*word)->eye_pos->z;

	(*word)->eye_pos->x = x * cos(angle) + z * sin(angle);
	(*word)->eye_pos->z = -x * sin(angle) + z * cos(angle);
}

void rotate_z(t_word **word, double angle)
{
	double x = (*word)->eye_pos->x;
	double y = (*word)->eye_pos->y;

	(*word)->eye_pos->x = x * cos(angle) - y * sin(angle);
	(*word)->eye_pos->y = x * sin(angle) + y * cos(angle);
}



int	key_hook(int key, void *param)
{
	t_word **word = param;
	if (key == ESC)
		close(0);
	if (key == UP)
	{
		black_image((*word)->canvas->image);
		(*word)->eye_pos->y -= 0.5;
		render(word);
	}
	if (key == DOWN)
	{
		black_image((*word)->canvas->image);
		(*word)->eye_pos->y += 0.5;
		render(word);
	}
	if (key == LEFT)
	{
		black_image((*word)->canvas->image);
		(*word)->eye_pos->x += 0.5;
		render(word);
	}
	if (key == RIGHT)
	{
		black_image((*word)->canvas->image);
		(*word)->eye_pos->x -= 0.5;
		render(word);
	}
	if (key == 65451)
	{
		black_image((*word)->canvas->image);
		(*word)->eye_pos->z += 0.5;
		render(word);
	}
	if (key == 65453)
	{
		black_image((*word)->canvas->image);
		(*word)->eye_pos->z -= 0.5;
		render(word);
	}
	if (key == ROT_UP_X)
	{
		black_image((*word)->canvas->image);
		rotate_x(word, 0.1);
		render(word);
	}
	if (key == ROT_DOWN_X)
	{
		black_image((*word)->canvas->image);
		rotate_x(word, -0.1);
		render(word);
	}
	if (key == ROT_UP_Y)
	{
		black_image((*word)->canvas->image);
		rotate_y(word, 0.1);
		render(word);
	}
	if (key == ROT_DOWN_Y)
	{
		black_image((*word)->canvas->image);
		rotate_y(word, -0.1);
		render(word);
	}
	if (key == ROT_UP_Z)
	{
		black_image((*word)->canvas->image);
		rotate_z(word, 0.1);
		render(word);
	}
	if (key == ROT_DOWN_Z)
	{
		black_image((*word)->canvas->image);
		rotate_z(word, -0.1);
		render(word);
	}
	if (key == 114){
		black_image((*word)->canvas->image);
		(*word)->eye_pos->x = 0;
		(*word)->eye_pos->y = 0;
		(*word)->eye_pos->z = -8;
		render(word);
	}
	mlx_put_image_to_window((*word)->canvas->mlx,(*word)->canvas->win,(*word)->canvas->image->img_ptr,0,0);
}

void	put_square(int x, int y, t_image *image, int color)
{
	float i = 0;
	float j = 0;
	while (i < SMOOTHENESS)
	{
		j = 0;
		while (j < SMOOTHENESS)
		{
			my_pixel_put(y + (int)j, x  + (int)i, image, color);
			j++;
		}
		i++;
	}
}

int		rgb_to_color(t_color	*color)
{
	return (color->r << 16 | color->g << 8 | color->b << 0);
}


void	my_pixel_put(int x, int y, t_image *image, int color)
{
	if (x < 0 || x >= 1000 || y < 0 || y >= 1000)
		return ;
	char *addr = image->addres + x * (image->bpp / 8) + y * image->line;
	*(unsigned int *)addr = color;
}

int	mouse_hook(int b, int x, int y, void *param)
{
	t_canvas *canvas = param;
}

void	init_image(t_image **img, void *mlx)
{
	*img = malloc(sizeof(t_image));
	if (!*img)
		exit(1);
	(*img)->img_ptr = mlx_new_image(mlx,1000,1000);
	(*img)->addres = mlx_get_data_addr((*img)->img_ptr,
		&(*img)->bpp, &(*img)->line, &(*img)->endian);
}

void	black_image(t_image *img)
{
	int i = 0;
	int j = 0;
	while (i < 1000)
	{
		j = 0;
		while (j < 1000)
		{
			my_pixel_put(i, j, img, 0);
			j++;
		}
		i++;
	}
}

int loop_hook(void *param)
{
	t_word	**word = param;
	mlx_put_image_to_window((*word)->canvas->mlx,(*word)->canvas->win,(*word)->canvas->image->img_ptr,0,0);
}


void	render(t_word	**word)
{
	(*word)->wall_size = 10.0;
	(*word)->pixel_size = 10.0 / 1000;
	(*word)->w_x = 0;
	(*word)->w_y = 0;
	(*word)->w_z = 14;


	(*word)->spheres = new_sphere(1);
	(*word)->spheres->m = material(0.9,0,0,0);
	(*word)->spheres->m->color = point(255,0,0);
	set_transform(&(*word)->spheres,new_scale(10,0.01,10),SCALE);
	(*word)->light = new_light();

	(*word)->spheres->next = new_sphere(2);
	(*word)->spheres->next->m = material(0.1,0.9,0.9,20);
	(*word)->spheres->next->m->color = point(255,0,0);
	set_transform(&(*word)->spheres->next,new_translation(0,0,5),SCALE);
	set_transform(&(*word)->spheres->next,new_rotation_y(PI/4),ROT);
	set_transform(&(*word)->spheres->next,new_rotation_x(PI/2),ROT);
	set_transform(&(*word)->spheres->next,new_scale(10,10,0.01),SCALE);


	(*word)->spheres->next->next = NULL;
	if (!(*word)->eye_pos)
		(*word)->eye_pos = point(0,0,-8);
	

	(*word)->light->pos = point(-4,2,-10);
	(*word)->light->intens = point(1,1,1);
	
	for (int i = 0; i<1000; i+=SMOOTHENESS)
	{
		(*word)->w_y = 5 - (*word)->pixel_size * i;
		for (int j = 0; j < 1000; j+=SMOOTHENESS)
		{
			(*word)->w_x = -5 + (*word)->pixel_size * j;


			(*word)->tmp = point((*word)->w_x,(*word)->w_y,(*word)->w_z);
			(*word)->ray_dir = tuple_operation((*word)->tmp,NORM,0);
			
			free((*word)->tmp);
			(*word)->ray = new_ray((*word)->eye_pos,(*word)->ray_dir);
			
			(*word)->intersects = get_sphere_intersections((*word)->spheres,(*word)->ray);
			(*word)->hit = find_hit((*word)->intersects);

			
			if ((*word)->hit)
			{
				
				(*word)->it_pos = position((*word)->ray,(*word)->hit->times[0]);
				(*word)->normal = normal_at((*word)->spheres,(*word)->it_pos);
				(*word)->eye_vec = tuple_operation((*word)->ray->direction,MUL,-1);
				(*word)->color = lighting((*word)->spheres->m,(*word)->light,(*word)->it_pos,(*word)->eye_vec,(*word)->normal);
				
				put_square(i,j,(*word)->canvas->image,(*word)->color);
				free((*word)->it_pos);
				free((*word)->normal);
				free((*word)->eye_vec);
			}
			free_intersections((*word)->intersects);
			free((*word)->ray->direction);
			free((*word)->ray);
		}
	}
	free((*word)->light->intens);
	free((*word)->light->pos);
	free((*word)->light);
	// free((*word)->eye_pos);
	free_spheres((*word)->spheres);
}



void	init_canvas(t_canvas *canvas)
{
	t_word *word;
	word = malloc(sizeof(t_word));
	if (!word)
		exit(1);
	canvas = malloc(sizeof(t_canvas));
	if (!canvas)
		exit(1);
	word->canvas = canvas;
	canvas->mlx = mlx_init();
	canvas->win = mlx_new_window(canvas->mlx,1000,1000, "Minirt");
	init_image(&canvas->image, canvas->mlx);
	render(&word);
	mlx_put_image_to_window(canvas->mlx,canvas->win,canvas->image->img_ptr,0,0);
	mlx_hook(canvas->win,17,0,close,NULL);
	mlx_key_hook(canvas->win,key_hook,&word);
	mlx_loop(canvas->mlx);
}
