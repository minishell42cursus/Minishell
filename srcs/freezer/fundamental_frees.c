/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reasonably_util_frees.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 11:03:39 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/17 14:48:30 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_four_ptrs(void *s1, void *s2, void *s3, void *s4)
{
	free(s1);
	free(s2);
	free(s3);
	free(s4);
}

void	free_three_ptrs(void *str1, void *str2, void *str3)
{
	free(str1);
	free(str2);
	free(str3);
}

void	free_two_ptrs(void *s1, void *s2)
{
	free(s1);
	free(s2);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix[i]);
	free(matrix);
}
