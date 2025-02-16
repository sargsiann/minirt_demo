#include "minirt.h"

float	cofactor(int **matrix, int rows, int cols, int row, int col)
{
	int	**sub;
	int	sign;
	float	det;

	sub = submatrix(matrix, rows, cols, row, col);
	sign = (row + col) % 2 == 0 ? 1 : -1;
	det = sign * determinant(sub, rows - 1);
	free_matrix(sub, rows - 1);
	return (det);
}

float	determinant(int **matrix, int rows)
{
	float	det;
	int		**sub;
	int		i;
	int		j;
	int		sign;

	if (rows == 1)
		return (matrix[0][0]);
	det = 0;
	sign = 1;
	i = -1;
	while (++i < rows)
	{
		sub = submatrix(matrix, rows, rows, 0, i);
		det += sign * matrix[0][i] * determinant(sub, rows - 1);
		sign *= -1;
		free_matrix(sub, rows - 1);
	}
	return (det);
}

int	**submatrix(int **matrix, int rows, int cols, int row, int col)
{
	int	**sub;
	int sub_i;
	int i;
	int j;
	int sub_j;

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

int **inverse_matrix(int **matrix, int rows, int cols)
{
	int	**inverse;
	int	i;
	int	j;

	inverse = (int **)malloc(sizeof(int *) * 4);
	if (determinant(matrix, rows) <= 0)
		return (NULL);
	// inverse = new_matrix(rows, cols);
	// i = -1;
	// while (++i < rows)
	// {
	// 	j = -1;
	// 	while (++j < cols)
	// 		inverse[i][j] = cofactor(matrix, rows, cols, i, j);
	// }
	// inverse = transpose_matrix(inverse, rows, cols);
	// i = -1;
	// j = -1;
	// while (++i < rows)
	// 	while (++j < cols)
	// 		inverse[i][j] /= determinant(matrix, rows);
	// return (inverse);
}