#include "minirt.h"

void	*bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t	i;

	ptr = s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
	return (s);
}

float	**new_matrix(int rows, int cols)
{
	float	**matrix;
	int	i;

	matrix = malloc(sizeof(float *) * rows);
	if (!matrix)
		exit(1);
	i = 0;
	while (i < rows)
	{
		matrix[i] = malloc(sizeof(float) * cols);
		bzero(matrix[i], sizeof(float) * cols);
		if (!matrix[i])
			exit(1);
		i++;
	}
	return (matrix);
}

void	print_matrix(float **matrix, int rows, int cols)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			printf("%f ", matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	free_matrix(float **matrix, int rows)
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

float	**matrix_mul(float **a, float **b, int rows, int cols)
{
	float	**new;
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

float	**transpose_matrix(float **matrix, int rows, int cols)
{
	float	**new;
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

float	**matrix_operation(float **a, float **b, int rows, int cols, char operation)
{
	float	**new;
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