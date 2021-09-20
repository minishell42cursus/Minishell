/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 19:23:13 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 19:23:35 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_shell_level(char *str)
{
	int		shell_level;
	char	*catch_itoa;
	char	*new_shlvl_entry;

	shell_level = ft_atoi(str + 6);
	shell_level++;
	catch_itoa = ft_itoa(shell_level);
	new_shlvl_entry = ft_strjoin("SHLVL=", catch_itoa);
	free(catch_itoa);
	return (new_shlvl_entry);
}

char	*set_pwd(void)
{
	char	*path;
	char	*new_pwd_entry;

	path = getcwd(NULL, 0);
	new_pwd_entry = ft_strjoin("PWD=", path);
	free(path);
	return (new_pwd_entry);
}

char	**clone_environment(char **env, int c)
{
	char	**out;
	int		i;

	i = 0;
	while (env[i])
		i++;
	out = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "SHLVL=", ft_strlen("SHLVL=")) && c == OK)
			out[i] = new_shell_level(env[i]);
		else if (!ft_strncmp(env[i], "PWD=", ft_strlen("PWD=")) && c == OK)
			out[i] = set_pwd();
		else
			out[i] = ft_strdup(env[i]);
		i++;
	}
	out[i] = NULL;
	return (out);
}

t_shell	*init_megastruct(int ac, char **av, char **env)
{
	t_shell	*shell;

	(void)av;
	shell = malloc(sizeof(t_shell));
	g_shell = shell;
	g_shell->p_lst = NULL;
	shell->ac = ac;
	shell->env = clone_environment(env, OK);
	shell->fdi = dup(0);
	shell->fdo = dup(1);
	shell->q_mark_err = 0;
	shell->n_proc = 0;
	shell->envar = new_env_var(ft_strdup("?"), ft_itoa(g_shell->q_mark_err));
	shell->status = ON_READ;
	shell->assign_error = OK;
	shell->pmt = NULL;
	return (g_shell);
}
