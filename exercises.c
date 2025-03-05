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


// void	put_square(int x, int y, t_image *image, int color)
// {
// 	int i = 0;
// 	int j = 0;
// 	while (i < 5)
// 	{
// 		j = 0;
// 		while (j < 5)
// 		{
// 			my_pixel_put(x + i, y  + j, image, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }
