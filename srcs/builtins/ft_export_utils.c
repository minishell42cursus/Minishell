/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:48:14 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/21 12:52:45 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_new_environment(char *name, char *value)
{
	char	**new_env;
	char	*aux;
	int		i;

	new_env = malloc(sizeof(char *) * ((int)ft_matrixlen(g_shell->env) + 2));
	i = 0;
	while (g_shell->env[i])
	{
		new_env[i] = ft_strdup(g_shell->env[i]);
		i++;
	}
	aux = ft_strjoin(name, "=");
	new_env[i++] = ft_strjoin(aux, value);
	new_env[i] = NULL;
	free_three_ptrs(aux, name, value);
	free_matrix(g_shell->env);
	g_shell->env = new_env;
}

void	check_for_already_defined(char *name, char *value)
{
	int		prev_def;
	int		entry;
	char	*aux;

	aux = value;
	check_for_local_value(name, &value);
	if (aux == value)
		prev_def = KO;
	else
	{
		prev_def = OK;
		free(aux);
	}
	if (prev_def == OK)
	{
		entry = find_env(name);
		aux = ft_strjoin(name, "=");
		free(g_shell->env[entry]);
		g_shell->env[entry] = ft_strjoin(aux, value);
		free(aux);
	}	
	else
		create_new_environment(name, value);
}

void	add_to_global_env(char *name, char *value, int stat)
{
	if (stat == NOTDEFINED)
		check_for_already_defined(name, value);
	else
		create_new_environment(name, value);
}
