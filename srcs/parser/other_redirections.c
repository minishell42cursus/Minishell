/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:40:37 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/10 17:17:30 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rebuild_aux_strings(t_nod *node);

void	add_variable_to_local_env(void)
{
	t_var	*nod;

	g_shell->envar = malloc(sizeof(t_var));
	g_shell->envar->name = ft_strdup("a");
	g_shell->envar->value = ft_strdup("123");
	nod = malloc(sizeof(t_var));
	nod->name = ft_strdup("a2");
	nod->value = ft_strdup("hello");
	nod->next = NULL;
	g_shell->envar->next = nod;
}

/* String is pointing to a \  or &, hardcoded there to be
 * recognised as enviroment variables to be expanded. */
char	*modify_length(char *str, int *len, int *i)
{
	char	*var_name;
	char	*var_value;
	int		length_wo_expansion;

	var_name = get_var_name(str);
	var_value = get_var_value(var_name);
	length_wo_expansion = ft_strlen(var_name);
	free(var_name);
	if (!*var_value)
		*len = *len - length_wo_expansion;
	else
		*len = *len - length_wo_expansion + ft_strlen(var_value);
	*i = *i - length_wo_expansion;
	free(var_value);
	return (str + length_wo_expansion);
}

void	add_envar_len(int *len, char *str)
{
	int	i;

	i = *len;
	while (*str == ' ')
		str++;
	while (i > 0)
	{
		if (*str == '\\' || *str == '&')
			str = modify_length(++str, len, &i);
		else if (*str != '*')
		{
			str++;
			i--;
		}
		else
			str++;
	}
}

/* Same as the get name of variable. It is meant to only get one char
 * if the variable name starts with a number and not a letter*/
void	do_expand_var(char **line, char **filename, int *len, char *var_value)
{
	int	i;

	i = 0;
	*((*line)++) = ' ';
	if (!ft_isdigit((*line)[i++]))
	{
		while (ft_isalnum((*line)[i]))
		{
			(*line)[i] = ' ';
			i++;
		}
	}
	**line = ' ';
	*line = *line + i;
	while (*var_value)
	{
		*((*filename)++) = *var_value++;
		*len = *len - 1;
	}
}

void	expand_var_name(char **line, char **filename, int *len, int *launch)
{
	char	*var_name;
	char	*var_value;
	char	*aux;

	var_name = get_var_name((*line + 1));
	var_value = get_var_value(var_name);
	if (**line == '\\' && var_value)
	{
		aux = ft_strnstr(var_value, " ", ft_maxlen(var_value, " "));
		if (aux)
			ambiguous_redirect_error(var_name, launch);
	}
	if (*launch == OK)
		do_expand_var(line, filename, len, var_value);
	free(var_name);
	free(var_value);
}

void	write_str_w_envar(char **line, char **filename, int *len, int *launch)
{
	char	*aux;

	aux = *filename;
	while (*len > 0 && *launch == OK)
	{
		if (**line == '\\' || **line == '&')
			expand_var_name(line, filename, len, launch);
		else if (**line != '*' && **line != '\\' && **line != '&' && **line)
		{
			*((*filename)++) = **line;
			*((*line)++) = ' ';
			*len = *len - 1;
		}
		else
			*((*line)++) = ' ';
	}
	while (**line == '*')
		*((*line)++) = ' ';
	if (*launch == KO)
		free(aux);
	else
		**filename = '\0';
}

char	*filename_gatherer(char **line, int *launch)
{
	char	*filename;
	char	*aux;
	int		len;

	len = string_length_bash(*line, OK);
	add_envar_len(&len, *line);
	filename = malloc(sizeof(char) * (len + 1));
	aux = filename;
	write_str_w_envar(line, &aux, &len, launch);
	return (filename);
}

void	move_str_pointers(char **str, char **aux, int i)
{
	int	displacement;

	displacement = i;
	while (displacement-- > 0)
		*str = *str + 1;
	displacement = i;
	while (displacement-- > 0)
		*aux = *aux + 1;
}

void	open_on_append_mode(t_nod *node, char *filename)
{
	if (node->fdo != 1)
		close(node->fdo);
	node->fdo = open(filename, O_APPEND | O_RDWR | O_CREAT, 00644);
	if (node->fdo == -1)
		error_msg_relative_to_file(filename, &node->launch);
}

void	open_on_truncate_mode(t_nod *node, char *filename)
{
	if (node->fdo != 1)
		close(node->fdo);
	node->fdo = open(filename, O_CREAT | O_RDWR | O_TRUNC, 00644);
	if (node->fdo == -1)
		error_msg_relative_to_file(filename, &node->launch);
}

int	check_for_hdoc_priority(char *str)
{
	while (*str)
	{
		if (*str == '\\')
			return (-1);
		str++;
	}
	return (0);
}

void	open_to_input(t_nod *node, char *filename)
{
	int	fd;

	fd = check_for_hdoc_priority(node->line);
	if (fd == -1)
	{
		fd = open(filename, O_RDONLY);
		if (fd == -1)
			error_msg_relative_to_file(filename, &node->launch);
	}
	else
	{
		if (node->fdi != 0)
			close(node->fdi);
		node->fdi = open(filename, O_RDONLY);
		if (node->fdi == -1)
			error_msg_relative_to_file(filename, &node->launch);
	}
}

/* red can be single or double, and red_io will give the reader and the code
 * a hint as to what the redirection is redirecting, input or output.*/
void	do_redirection(t_nod *node, char **aux, int red, int red_io)
{
	char	*filename;
	int		displacement;

	place_str_pointers(aux, &node->line_aux, &node->line, red);
	filename = filename_gatherer(&node->line, &node->launch);
	if (node->launch == OK)
	{
		if (red == DOUBLE && red_io == OUTPUT)
			open_on_append_mode(node, filename);
		else if (red == SINGLE && red_io == OUTPUT)
			open_on_truncate_mode(node, filename);
		else
			open_to_input(node, filename);
		free(filename);
	}
	displacement = node->line - node->line_save;
	displacement -= (node->line_aux - node->line_aux_save);
	move_str_pointers(&node->line_aux, aux, displacement);
}

void	redirection_checker(t_nod *node)
{
	char	*aux;

	aux = node->line_aux;
	while (*aux && node->launch == OK)
	{
		if (*aux == '>' || *aux == '<')
		{
			if (*(aux + 1) == '>')
			{
				aux = aux + 2;
				do_redirection(node, &aux, DOUBLE, OUTPUT);
			}
			else
			{
				if (*aux++ == '>')
					do_redirection(node, &aux, SINGLE, OUTPUT);
				else
					do_redirection(node, &aux, SINGLE, INPUT);
			}
		}
		else
			aux++;
	}
}

void	clean_hdoc_bar(t_nod *node)
{
	char	*aux;

	aux = node->line_save;
	while (*aux)
	{
		if (*aux == '\\')
			*aux = ' ';
		aux++;
	}
	node->line = node->line_save;
	free(node->line_aux_save);
}

void	other_io_redirections(void)
{
	int		i;
	t_nod	*node;

	i = g_shell->n_proc;
	node = g_shell->p_lst;
	while (i > 0)
	{
		redirection_checker(node);
		if (node->launch == OK)
		{
			clean_hdoc_bar(node);
			rebuild_aux_strings(node);
		}
		node = node->next;
		i--;
	}
}
