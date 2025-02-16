#include "minirt.h"

int main(int argc, char **argv)
{
	canvas	canvas;

	int **a;
	int **b;
	a = new_matrix(4, 4);

	a[0][0] =  8;
	a[0][1] = -5;
	a[0][2] =  9;
	a[0][3] =  2;
	a[1][0] =  7;
	a[1][1] =  5;
	a[1][2] =  6;
	a[1][3] =  1;
	a[2][0] = -6;
	a[2][1] =  0;
	a[2][2] =  9;
	a[2][3] =  6;
	a[3][0] = -3;
	a[3][1] =  0;
	a[3][2] = -9;
	a[3][3] = -4;
	b = inverse_matrix(a, 4, 4);
	printf("%d", b[0][0]);
	// print_matrix(b, 4, 4);
	return (0);
}