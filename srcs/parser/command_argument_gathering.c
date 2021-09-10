/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comand_argument_gathering.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:37:06 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/10 14:06:53 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_vars_outside_strings(node)
{


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
			expand_envars_outside_strings(node);
			check_for_local_envar_defs(node);
			gather_args(node);
		}
		node = node->next;
		i--;
	}
}
