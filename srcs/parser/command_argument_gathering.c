/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comand_argument_gathering.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:37:06 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/10 23:55:01 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_next_comma(char **str, int *i, char comma)
{
	(*i)++;
	*str = *str + 1;
	while (**str != comma)
	{
		*str = *str + 1;
		(*i)++;
	}
	*str = *str + 1;
	(*i)++;
}

int		ft_strlen_wo_dollars(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == '\"')
			wait_for_next_comma(&str, &i, '\"');
		else if (*str == '\'')
			wait_for_next_comma(&str, &i, '\'');
		else if (*str =='$' && ft_isalpha(*(str + 1)))
			str++;
		else
		{
			str++;
			i++;
		}
	}
	return (i);
}

void	put_ampersands_on_envars(char **line)
{
	char	*aux;

	aux = *line;
	while (*aux)
	{
		if (*aux == '\'')
		{
			while (*(++aux) != '\'')
				;
			aux++;
		}
		else if (*aux == '$' && ft_isalpha(*(aux + 1)))
			*aux++ = '&';
		else
			aux++;
	}
}

void	expand_vars_outside_strings(t_nod *node)
{
	int		len;

	len = ft_strlen_wo_dollars(node->line);
	put_ampersands_on_envars(&node->line); 
	add_envar_len(&len, node->line, FULL_LINE);
	node->line_aux = malloc(sizeof(char) * (len + 1));
	node->line_aux_save = node->line_aux;
	write_str_w_envar(&node->line, &node->line_aux, &len, &node->launch);
	free(node->line_save);
	node->line_save = ft_strdup(node->line_aux_save);
	node->line = node->line_save;
	free(node->line_aux_save);
}

void	prepare_line_for_split(char *str)
{
	while (*str)
	{
		if (*str == '\'')
		{
			while (*(++str) != '\'')
			{
				if (*str == ' ')
					*str = '*';
			}
			str++;
		}
		else if (*str == '\"')
		{
			while (*(++str) != '\"')
			{
				if (*str == ' ')
					*str = '*';
			}
			str++;
		}
		else
			str++;
	}
}

void	gather_args(t_nod *node)
{
	printf("this is the line before the modification: [%s]\n", node->line);
	prepare_line_for_split(node->line);
	printf("this is the line after the modification: [%s]\n", node->line);
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
			expand_vars_outside_strings(node);
			gather_args(node);
		}
		node = node->next;
		i--;
	}
}
