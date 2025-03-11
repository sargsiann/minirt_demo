#include "minirt.h"

float	determinant(float **a, char rows, char cols)
{
	float	res;
	char	i;
	float	**sub;

	res = 0;
	if (rows == 2 && cols == 2)
		return (a[0][0] * a[1][1] - a[0][1] * a[1][0]);
	i = -1;
	while (++i < cols)
	{
		sub = submatrix(a, rows, cols, 0, i);
		res += a[0][i] * pow(-1, i) 
			* determinant(sub, rows - 1, cols - 1);	
		free_matrix(sub, rows - 1);
	}
	return (res);
}

float	cofactor(float **a, char rows, char cols, char r, char c)
{
	float	**sub;
	float	res;

	sub = submatrix(a, rows, cols, r, c);
	res = pow(-1, r + c) * determinant(sub, rows - 1, cols - 1);
	free_matrix(sub, rows - 1);
	return (res);
}

float	**matrix_mul(float **a, float **b,char row,char col, bool free_a, bool free_b)
{
	float	**res;
	char	i;
	char	j;
	char 	k;
	float	sum;

	res = new_matrix(row,col);
	i = -1;
	while (++i < row)
	{
		j = -1;
		while (++j < col)
		{
			sum = 0;
			k = -1;
			while (++k < row)
				sum += a[i][k] * b[k][j];
			res[i][j] = sum;
		}
	}	
	if (free_a)
		free_matrix(a,row);
	if (free_b)
		free_matrix(b,row);
	return (res);
}

void	transpose(float **a, char row, char col)
{
	float	**res;
	char	i;
	char	j;
	float	tmp;

	i = -1;
	while (++i < row)
	{
		j = i;
		while (++j < col)
		{
			tmp = a[i][j];
			a[i][j] = a[j][i];
			a[j][i] = tmp;
		}
	}
}

float	**tuple_to_mx(tuple *a)
{
	float	**res;

	res = new_matrix(4,1);
	res[0][0] = a->x;
	res[1][0] = a->y;
	res[2][0] = a->z;
	res[3][0] = a->id;
	return (res);
}

tuple	*mx_to_tuple(float **a)
{
	tuple	*res;

	res = malloc(sizeof(tuple));
	res->x = a[0][0];
	res->y = a[1][0];
	res->z = a[2][0];
	res->id = a[3][0];
	return (res);
}

float **submatrix(float **a,char rows, char cols, char d_r,char d_c)
{
	float **sub;
	char i;
	char j;
	char sub_i;
	char sub_j;

	sub = new_matrix(rows - 1,cols - 1);
	i = -1;
	sub_i = 0;
	while (++i < rows)
	{
		if (i == d_r)
			i++;
		if (i >= rows)
			break;
		j = -1;
		sub_j = 0;
		while (++j < cols)
		{
			if (j == d_c)
				j++;
			if (j >= cols)
				break;
			sub[sub_i][sub_j] = a[i][j];
			sub_j++;
		}
		sub_i++;
	}
	return (sub);
}

float	**new_matrix(int row, int col)
{
	float	**new_matrix;
	char	i;

	i = 0;
	new_matrix = malloc(sizeof(float *) * row);
	if (!new_matrix)
		return (NULL);
	while (i < row)
	{
		new_matrix[i] = malloc(sizeof(float) * col);
		if (!new_matrix[i])
			return (NULL);
		ft_bzero(new_matrix[i],col);
		i++;
	}
	return new_matrix;
}

float	**inverse(float **a, char rows, char cols)
{
	float	**res;
	float	det;
	char	i;
	char	j;

	det = determinant(a, rows, cols);
	if (det <= 0)
		return (NULL);
	res = new_matrix(rows, cols);
	if (!res)
		return (NULL);
	i = -1;
	while (++i < rows)
	{
		j = -1;
		while (++j < cols)
			res[i][j] = cofactor(a, rows, cols, i, j) / det;
	}
	transpose(res, rows, cols);
	return (res);
}