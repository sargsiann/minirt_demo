#include "minirt.h"

float	**translation(float **matrix, float x, float y, float z)
{
	float	**translation;
	float	**result;

	translation = new_matrix(4, 4);
	translation[0][0] = 1;
	translation[1][1] = 1;
	translation[2][2] = 1;
	translation[3][3] = 1;
	translation[0][3] = x;
	translation[1][3] = y;
	translation[2][3] = z;
	result = matrix_mul(matrix, translation, 4, 4);
	free_matrix(translation, 4);
	return (result);
}

float	**scale(float **matrix, float x, float y, float z)
{
	float	**scale;
	float	**result;

	scale = new_matrix(4, 4);
	scale[0][0] = x;
	scale[1][1] = y;
	scale[2][2] = z;
	scale[3][3] = 1;
	result = matrix_mul(matrix, scale, 4, 4);
	free_matrix(scale, 4);
	return (result);
}

float	**rotation_x(float **matrix, float rad, int cols)
{
	float	**rotation;
	float	**result;

	rotation = new_matrix(4, 4);
	rotation[0][0] = 1;
	rotation[3][3] = 1;
	rotation[1][1] = cos(rad);
	rotation[1][2] = -sin(rad);
	rotation[2][1] = sin(rad);
	rotation[2][2] = cos(rad);
	result = matrix_mul(matrix, rotation, 4, cols);
	print_matrix(result, 4, 4);
	printf("\n");
	free_matrix(rotation, 4);
	return (result);
}

float	**rotation_y(float **matrix, float rad)
{
	float	**rotation;
	float	**result;

	rotation = new_matrix(4, 4);
	rotation[1][1] = 1;
	rotation[3][3] = 1;
	rotation[0][0] = cos(rad);
	rotation[0][2] = sin(rad);
	rotation[2][0] = -sin(rad);
	rotation[2][2] = cos(rad);
	result = matrix_mul(matrix, rotation, 4, 4);
	free_matrix(rotation, 4);
	return (result);
}

float	**rotation_z(float **matrix, float rad)
{
	float	**rotation;
	float	**result;

	rotation = new_matrix(4, 4);
	rotation[2][2] = 1;
	rotation[3][3] = 1;
	rotation[0][0] = cos(rad);
	rotation[0][1] = -sin(rad);
	rotation[1][0] = sin(rad);
	rotation[1][1] = cos(rad);
	result = matrix_mul(matrix, rotation, 4, 4);
	free_matrix(rotation, 4);
	return (result);
}

float	**shearing(float **matrix, float xy, float xz, float yx, float yz, float zx, float zy)
{
	float	**shearing;
	float	**result;

	shearing = new_matrix(4, 4);
	shearing[0][0] = 1;
	shearing[1][1] = 1;
	shearing[2][2] = 1;
	shearing[3][3] = 1;
	shearing[0][1] = xy;
	shearing[0][2] = xz;
	shearing[1][0] = yx;
	shearing[1][2] = yz;
	shearing[2][0] = zx;
	shearing[2][1] = zy;
	result = matrix_mul(matrix, shearing, 4, 4);
	free_matrix(shearing, 4);
	return (result);
}