#include "minirt.h"

// ADDING MATRIX OK
// SUBSTRACTING MATRIX OK
// MULTIPLYING MATRIX OK
// TRANSPOSING MATRIX OK
// FINDING SUBMATRIX OK
// FINDING DETERMINANT OK
// FINDING COFACTOR OK
// FINDING INVERSE OK

float	cofactor(float **matrix, int rows, int cols, int row, int col)
{
	float	**sub;
	int	sign;
	float	det;

	sub = submatrix(matrix, rows, cols, row, col);
	sign = (row + col) % 2 == 0 ? 1 : -1;
	det = sign * determinant(sub, rows - 1);
	free_matrix(sub, rows - 1);
	return (det);
}

float	determinant(float **matrix, int rows)
{
	float	det;
	float	**sub;
	int		i;
	int		sign;

	if (rows == 2)
		return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
	det = 0;
	i = -1;
	sign = 1;
	while (++i < rows)
	{
		sub = submatrix(matrix, rows, rows, 0, i);
		det += sign * matrix[0][i] * determinant(sub, rows - 1);
		sign *= -1;
		free_matrix(sub, rows - 1);
	}
	return (det);
}

float	**submatrix(float **matrix, int rows, int cols, int row, int col)
{
	float	**sub;
	int		sub_i;
	int		i;
	int		j;
	int		sub_j;

	sub = new_matrix(rows - 1, cols - 1);
	sub_i = -1;
	sub_j = -1;
	i = j = -1;
	while (++i < rows)
	{
		if (i == row)
			continue ;
		sub_i++;
		j = -1;
		while (++j < cols)
		{
			if (j == col)
				j++;
			if (j == cols)
				break ;
			sub[sub_i][++sub_j] = matrix[i][j];
		}
		sub_j = -1;
	}
	return (sub);
}

float **inverse_matrix(float **matrix, int rows, int cols)
{
	float	**inverse;
	int	i;
	int	j;

	inverse = new_matrix(rows, cols);
	if (!inverse)
		exit(1);
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			inverse[i][j] = cofactor(matrix, rows, cols, i, j);
			j++;
		}
		i++;
	}
	inverse = transpose_matrix(inverse, rows, cols);
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			inverse[i][j] /= determinant(matrix, rows);
			j++;
		}
		i++;
	}
	return (inverse);
}