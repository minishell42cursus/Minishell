/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comand_argument_gathering.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:37:06 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/12 18:27:07 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_next_comma(char **str, int *i, char comma)
{
	(*i)++;
	*str = *str + 1;
	while (**str != comma)
	{
		if (comma == '\"')
		{
			if (**str == '$' && ft_isvalid_env_start(*(*str + 1)))
				(*i)--;
		}
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
		else if (*str =='$' && ft_isvalid_env_start(*(str + 1)))
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
		else if (*aux == '$' && ft_isvalid_env_start(*(aux + 1)))
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

void	convert_argument_correctly(char **arg)
{
	char	*actual_arg;
	char	*aux;
	char	*str;
	int		len;

	len = string_length_bash(*arg, KO);
	actual_arg = malloc(sizeof(char) * (len + 1));
	aux = actual_arg;
	str = *arg;
	while (len > 0)
	{
		if (*str != '*')
		{
			*aux++ = *str;
			len--;
		}
		str++;
	}
	*aux = '\0';
	free(*arg);
	*arg = actual_arg;
}

void	clean_args_on_cmd(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '*')
				cmd[i][j] = ' ';
			j++;
		}
		i++;
	}
	i = 0;	
	while (cmd[i])
	{
		convert_argument_correctly(&cmd[i]);
		i++;
	}
}

void	gather_args(t_nod *node)
{
	int	i;

	i = 0;
	prepare_line_for_split(node->line);
	node->cmd = ft_split(node->line, ' ');
	/*while (node->cmd[i])
	{
		printf("cmd[%i]: [%s]\n", i, node->cmd[i]);
		i++;
	}*/
	free(node->line);
	clean_args_on_cmd(node->cmd);
	/*while (node->cmd[i])
	{
		printf("cmd[%i]: [%s]\n", i, node->cmd[i]);
		i++;
	}*/
	clear_envar_defs(&node->cmd);
	i = 0;
	while (node->cmd[i])
	{
		printf("cmd[%i]: [%s]\n", i, node->cmd[i]);
		i++;
	}
	if (!*node->cmd)
	{
		free_matrix(node->cmd);
		node->launch = KO;
	}
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
