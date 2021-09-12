#include "libft.h"

/* Returns the number of sttrings inside an
 * array of strings. It does not count the last
 * NULL pointer.*/
size_t	ft_matrixlen(char **matrix)
{
	size_t	len;

	len = 0;
	if (!matrix)
		return (0);
	while (matrix[len])
		len++;
	return (len);
}
