#include "minirt.h"

// INITING MUTEX FOR ONE AT ONCE ACCESING SAME MEMORY

void render(t_word	**word);

int	close(int s)
{
	exit(s);
}


int	key_hook(int key, void *param)
{
	t_word **word = param;
	if (key == ESC)
		close(0);
	if (key == 32)
	{
		render(word);
	}
	if (key == UP)
	{
		(*word)->eye_pos->y += 1;
	}
	if (key == DOWN)
	{
		(*word)->eye_pos->y -= 1;
	}
}

void	put_square(int x, int y, t_image *image, int color)
{
	int i = 0;
	int j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			my_pixel_put(x + i, y  + j, image, color);
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
	// put_square(x, y, canvas->image, rgb_to_color(255, 0, 0));
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
	(*word)->spheres->m = material(0.1,0.9,0.9,10);
	set_transform(&(*word)->spheres,new_scale(2,2,2),SCALE);
	(*word)->spheres->m->color = point(255,0,0);

	(*word)->light = new_light();
	(*word)->eye_pos = point(0,0,-8);
	

	(*word)->light->pos = point(4,2,-10);
	(*word)->light->intens = point(1,1,1);
	
	for (int i = 0; i<1; i+=4)
	{
		(*word)->w_y = 5 - (*word)->pixel_size * i;
		for (int j = 0; j < 1; j+=4)
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
				
				put_square(j, i, (*word)->canvas->image, (*word)->color);
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
	free((*word)->eye_pos);
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
	mlx_hook(canvas->win,17,0,close,NULL);
	mlx_mouse_hook(canvas->win,mouse_hook,canvas);
	mlx_key_hook(word->canvas->win,key_hook,&word);
	mlx_loop_hook(word->canvas->mlx,loop_hook,&word);
	mlx_loop(canvas->mlx);
}