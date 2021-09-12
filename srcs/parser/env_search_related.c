/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_search_related.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:31:17 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/12 21:39:54 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* glitch: Si la variable se llama
 * hola y acaba en hola=, explota. Como ajuste
 * podriamos hacer que '=' no pudiese entrar dentro
 * de llas definiciones de las variables de entorno */
char	*check_env(char *name)
{
	int		i;
	char	*aux;
	char	*value;

	aux = ft_strjoin(name, "=");
	i = 0;
	while (g_shell->env[i])
	{
		if (!ft_strncmp(g_shell->env[i], aux, ft_strlen(aux)))
			break ;
		i++;
	}
	if (!g_shell->env[i])
		value = NULL;
	else
		value = ft_strdup(g_shell->env[i] + ft_strlen(name) + 1);
	free(aux);
	return (value);
}

static char	*check_local_env(char *name)
{
	t_var	*var;

	var = g_shell->envar;
	while (var)
	{
		if (!ft_strncmp(var->name, name, ft_maxlen(var->name, name)))
			return (ft_strdup(var->value));
		var = var->next;
	}
	return (ft_strdup(""));
}

/*Theres an adjustment so if an apparent environment variable
 * starts with a number and not a letter it only gets that number
 * as the name of the variable, and so it searches for something that
 * doesnt exist and correctly gives a null string as value.*/
char	*get_var_name(char *str)
{
	int		len;
	char	*name;

	len = 0;
	if (ft_isvalid_env_start(str[len++]))
	{
		while (ft_isvalid_env_core(str[len]))
			len++;
	}
	else if (*str == '?')
		return (ft_itoa(g_shell->q_mark_err));	
	name = ft_substr(str, 0, len);
	return (name);
}

char	*get_var_value(char *name)
{
	char	*value;

	value = check_env(name);
	if (!value)
		value = check_local_env(name);
	return (value);
}
