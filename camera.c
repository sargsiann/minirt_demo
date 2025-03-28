#include "minirt.h"

float **view_transform(tuple *from, tuple *to, tuple *up){
	tuple	*forward;
	tuple	*tmp;
	tuple	*upn;
	tuple	*left;
	tuple	*true_up;

	tmp = tuples_operation(to,from,SUB);
	forward = tuple_operation(tmp,NORM,0);

	upn = tuple_operation(up,NORM,0);

	left = tuples_operation(forward,upn,VEC_MUL);

	true_up = tuples_operation(left,forward,VEC_MUL);

	float **orientation = new_matrix(4,4);
	orientation[0][0] = left->x;
	orientation[0][1] = left->y;
	orientation[0][2] = left->z;
	orientation[0][3] = 0;
	orientation[1][0] = true_up->x;
	orientation[1][1] = true_up->y;
	orientation[1][2] = true_up->z;
	orientation[1][3] = 0;
	orientation[2][0] = -forward->x;
	orientation[2][1] = -forward->y;
	orientation[2][2] = -forward->z;
	orientation[2][3] = 0;
	orientation[3][0] = 0;
	orientation[3][1] = 0;
	orientation[3][2] = 0;
	orientation[3][3] = 1;

	free(forward);
	free(left);
	free(upn);
	free(true_up);
	
	float x = -from->x;
	float y = -from->y;
	float z = -from->z;

	free(from);
	return matrix_mul(orientation,new_translation(x,y,z),4,4,true,true);
}