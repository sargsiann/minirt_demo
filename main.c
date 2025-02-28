#include "minirt.h"

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

	// t_canvas *canvas;
	// init_canvas(canvas);

	// float **a = new_matrix(2,3);

	// a[0][0] = 1;a[0][1] = 2;a[0][2] = 3;
	// a[1][0] = 4;a[1][1] = 5;a[1][2] = 6;

	// print_matrix(a, 2, 3);
	// printf("\n");
	// float **b = transpose(a, 2, 3);
	// print_matrix(b, 3, 2);

	// float **a = new_matrix(2,4);

	// a[0][0] = 1;a[0][1] = 2;a[0][2] = 3;a[0][3] = 4;
	// a[1][0] = 5;a[1][1] = 6;a[1][2] = 7;a[1][3] = 8;

	// float **b = submatrix(a, 2, 4, 1, 0);
	// print_matrix(b, 2, 3);


// 	// | 8 | -5 | 9 | 2 |
// | 7 | 5 | 6 | 1 |
// | -6 | 0 | 9 | 6 |
// | -3 | 0 | -9 | -4 |//


	// float **a = new_matrix(3,3);

	// a[0][0] = 1;a[0][1] = 2;a[0][2] = 6;
	// a[1][0] = -5;a[1][1] = 8;a[1][2] = -4;
	// a[2][0] = 2;a[2][1] = 6;a[2][2] = 4;

	// float **b = inverse(a, 3, 3);

// 	| -5 | 2 | 6 | -8 |
// | 1 | -5 | 1 | 8 |
// | 7 | 7 | -6 | -7 |
// | 1 | -3 | 7 | 4 |

	// print_matrix(b, 3, 3);

	// print_matrix(matrix_mul(a, b, 3, 3), 3, 3);

	// float **a = new_matrix(3,3);

	// a[0][0] = -5;a[0][1] = 2;a[0][2] = 6;
	// a[1][0] = 1;a[1][1] = -5;a[1][2] = 1;	
	// a[2][0] = 7;a[2][1] = 7;a[2][2] = -6;

	// print_matrix(inverse(a, 3, 3), 3, 3);

	// tuple *a = point(1,2,3);
	
	// float **b = new_translation(11, -11, 11);
	// // print_matrix(b, 4, 4);
	// float **c = tuple_to_mx(a);
	// // print_matrix(c, 4, 1);
	// float **d = matrix_mul(b, c, 4, 1);
	// // print_matrix(d,4,1);
	// return (0);

	// t_canvas *c;

	// init_canvas(c);
	
	// t_ray *r = new_ray(point(1,2,3), vector(0,1,0));
	// tuple *p = position(r, 3.5);
	// print_tuple(p);
	
	// t_sphere *s1 = malloc(sizeof(t_sphere));
	// s1->center = point(0,0,0);
	// s1->r = 1;
	// s1->id = 1;

	// t_sphere *s2 = malloc(sizeof(t_sphere));
	// s2->center = point(0,0,0);
	// s2->r = 1;
	// s2->id = 2;

	// t_ray *r = new_ray(point(0,0,-5), vector(0,0,1));
	// t_intersect *i1 = intersect(r, s1);
	// t_intersect *i2 = intersect(r, s2);

	// addIntersection(&i1, i2);
	// print_intersection(i1);
	return (0);
}