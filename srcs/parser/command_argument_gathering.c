/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comand_argument_gathering.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:37:06 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/10 17:17:51 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	expand_vars_outside_strings(node)
{
	char	*aux;
	int		len;

	printf("length of node->line: %i\n", (int)ft_strlen(node->line));
	printf("length of node->line_aux: %i\n", (int)ft_strlen(node->line_aux));
	len = (int)ft_strlen(node->line_aux);
	aux == node->line_aux;
	while (*aux)
	{
		if (*aux++ == '$')
			*(aux - 1) = '\\';
	}
	add_envar_len(&len, node->line);
	free(node->line_aux_save);
	node->line_aux = malloc(sizeof(char) * (len + 1));
	node->line_aux_save = node->line_aux;
	write_str_w_envar(&node->line, &node->line_aux, &len, &node->launch);
	printf("the line is now this one: [%s]\n", node->line_aux_save); 
}



void	gather_process_arguments(void)
{
	int		i;
	t_nod	*node;

	i = g_shell->n_proc;
	node = g_shell->p_lst;
	while (i > 0)
	{
		if (node->launch == OK)
		{
			printf("line: [%s]\n", node->line);
			printf("line_aux: [%s]\n", node->line_aux);
			//expand_envars_outside_strings(node);
			//check_for_local_envar_defs(node);
			//gather_args(node);
		}
		node = node->next;
		i--;
	}
}
