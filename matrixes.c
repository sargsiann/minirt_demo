#include "minirt.h"

int	**new_matrix(int rows, int cols)
{
	int	**matrix;
	int	i;

	matrix = malloc(sizeof(int *) * rows);
	if (!matrix)
		exit(1);
	i = 0;
	while (i < rows)
	{
		matrix[i] = malloc(sizeof(int) * cols);
		if (!matrix[i])
			exit(1);
		i++;
	}
	return (matrix);
}

void	print_matrix(int **matrix, int rows, int cols)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			printf("%d ", matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	free_matrix(int **matrix, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	**matrix_mul(int **a, int **b, int rows, int cols)
{
	int	**new;
	int	i;
	int	j;
	int	k;

	new = new_matrix(rows, cols);
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			new[i][j] = 0;
			k = 0;
			while (k < cols)
			{
				new[i][j] += a[i][k] * b[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (new);
}

int	**transpose_matrix(int **matrix, int rows, int cols)
{
	int	**new;
	int	i;
	int	j;

	new = new_matrix(cols, rows);
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			new[j][i] = matrix[i][j];
			j++;
		}
		i++;
	}
	return (new);
}

int	**matrix_operation(int **a, int **b, int rows, int cols, char operation)
{
	int	**new;
	int	i;
	int	j;


	new = new_matrix(rows, cols);
	i = -1;
	while (++i < rows)
	{
		j = -1;
		while (++j < cols)
		{
			if (operation == '+')
				new[i][j] = a[i][j] + b[i][j];
			else if (operation == '-')
				new[i][j] = a[i][j] - b[i][j];
			else if (operation == '*')
			{
				free_matrix(new, rows);
				return (matrix_mul(a, b, rows, cols));
			}
		}	
	}
	return (new);
}