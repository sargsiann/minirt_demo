#include "minirt.h"

float	**new_translation(float x, float y, float z)
{
	float **translation;

	translation = new_matrix(4,4);
	translation[0][3] = x;
	translation[1][3] = y;
	translation[2][3] = z;
	translation[3][3] = 1;
	translation[2][2] = 1;
	translation[1][1] = 1;
	translation[0][0] = 1;
	return (translation);
}

float	**new_scale(float x, float y, float z)
{
	float **scale;

	scale = new_matrix(4,4);
	scale[0][0] = x;
	scale[1][1] = y;
	scale[2][2] = z;
	scale[3][3] = 1;
	return (scale);
}

float	**new_rotation_x(float rad)
{
	float **rotation;

	rotation = new_matrix(4,4);
	rotation[0][0] = 1;
	rotation[1][1] = cos(rad);
	rotation[1][2] = -sin(rad);
	rotation[2][1] = sin(rad);
	rotation[2][2] = cos(rad);
	rotation[3][3] = 1;
	return (rotation);
}

float	**new_rotation_y(float rad)
{
	float **rotation;

	rotation = new_matrix(4,4);
	rotation[0][0] = cos(rad);
	rotation[0][2] = sin(rad);
	rotation[1][1] = 1;
	rotation[2][0] = -sin(rad);
	rotation[2][2] = cos(rad);
	rotation[3][3] = 1;
	return (rotation);
}

float	**new_rotation_z(float rad)
{
	float **rotation;

	rotation = new_matrix(4,4);
	rotation[0][0] = cos(rad);
	rotation[0][1] = -sin(rad);
	rotation[1][0] = sin(rad);
	rotation[1][1] = cos(rad);
	rotation[2][2] = 1;
	rotation[3][3] = 1;
	return (rotation);
}

float **new_shearing(float xy, float xz, float yx, float yz, float zx, float zy)
{
	float **shearing;

	shearing = new_matrix(4,4);
	shearing[0][0] = 1;
	shearing[0][1] = xy;
	shearing[0][2] = xz;
	shearing[1][0] = yx;
	shearing[1][1] = 1;
	shearing[1][2] = yz;
	shearing[2][0] = zx;
	shearing[2][1] = zy;
	shearing[2][2] = 1;
	shearing[3][3] = 1;
	return (shearing);
}