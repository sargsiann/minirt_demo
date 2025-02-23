#include "minirt.h"

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

// t_projectile tick(t_projectile p, t_env e)
// {
// 	p.pos = (tuple *)(tuples_operation(p.pos,p.velocity,ADD));
// 	p.velocity = (tuple *)(tuples_operation(p.velocity,
// 		(tuple *)(tuples_operation(e.gravity,e.wind,ADD)),ADD));
// 	print_tuple(p.pos); 
// 	return (p);
// }


int main()
{
	// t_projectile p;
	// t_env e;

	// p.pos = point(0,1,0);
	// p.velocity = vector(1,1,0);
	// e.gravity = vector(0,-0.3,0);
	// e.wind = vector(0,0,0.3);
	// int i = 0;
	// while (p.pos->y >= 0)
	// {
	// 	p = tick(p,e);
	// 	i++;
	// }
	// printf("%d",i);
	// // free(res);
	// tuple *x = tuple_operation(&a, NORM, 0);
	// print_tuple(x);
	// printf("mag: %2.f\n",*(float *)tuple_operation(x, MAG, 0));
	// tuple *res = tuples_operation(&a, &b, DIV);
	// printf("x: %f, y: %f, z: %f\n", res->x, res->y, res->z);
	
	// printf("x: %f, y: %f, z: %f\n", res->x, res->y, res->z);
	// free(res);
	// res = tuples_operation(&a, &b, VEC_MUL);
	// printf("x: %f, y: %f, z: %f\n", res->x, res->y, res->z);
	// free(res);
}