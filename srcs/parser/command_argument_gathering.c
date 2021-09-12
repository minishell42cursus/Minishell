/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comand_argument_gathering.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:37:06 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/12 04:21:26 by carce-bo         ###   ########.fr       */
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
			if (**str == '$' && ft_isalpha(*(*str + 1)))
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


void	add_to_local_env(char *name, char *value)
{
	t_var	*nod;
	int		assigned;

	assigned = 0;
	nod = g_shell->envar;
	while (nod && assigned == 0)
	{
		if (!ft_strncmp(nod->name, name, ft_maxlen(nod->name, name)))
		{
			free(name);
			free(nod->value);
			nod->value = value;
			assigned = 1;
		}
		nod = nod->next;
	}
	if (assigned == 0)
	{
		nod = malloc(sizeof(t_var));
		nod->name = name;
		nod->value = value;
		nod->next = NULL;
	}
}

/* Function that will clear the local environment variable
 * declaration from the command matrix, resizing it correctly.
 * Example: [a="hello ls] will be just [ls] after assigning a.*/ 
void	rebuild_cmd(char ***cmd)
{
	char	**aux;
	char	**new_cmd;
	int		i;

	new_cmd = malloc(sizeof(char *) * ft_matrixlen(*cmd));
	aux = *cmd;
	i = 1;
	while (aux[i])
	{
		new_cmd[i - 1] = ft_strdup(aux[i]); 
		i++;
	}
	new_cmd[i - 1] = NULL;
	free_matrix(*cmd);
	*cmd = new_cmd;
}

int	check_if_def(char *str)
{
	if (!str)
		return (0);
	if (ft_isalpha(*str))
	{
		while (ft_isalnum(*str))
			str++;
		if (*str == '=')
			return (1);
	}
	return (0);
}

void	clear_envar_defs(char ***cmd)
{
	char	**aux;
	char	*aux2;
	char	*name;
	char	*value;

	aux = *cmd;
	aux2 = NULL;
	if (check_if_def(*aux) == OK)
	{
		aux2 = *aux;
		name = get_var_name(aux2);
		aux2 = aux2 + ft_strlen(name) + 1;
		value = ft_strdup(aux2);
		add_to_local_env(name, value);
		rebuild_cmd(cmd);
		clear_envar_defs(cmd);
	}
}

void	gather_args(t_nod *node)
{
	prepare_line_for_split(node->line);
	node->cmd = ft_split(node->line, ' ');
	free(node->line);
	clean_args_on_cmd(node->cmd);
	clear_envar_defs(&node->cmd);
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
