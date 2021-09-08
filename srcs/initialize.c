#include "minishell.h"

static char	**clone_environment(char **env)
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
	shell->ac = ac;
	shell->env = clone_environment(env);
	shell->fdi = dup(0);
	shell->fdo = dup(1);
	shell->q_mark_err = 0;
	shell->n_proc = 0;
	shell->envar = NULL;
	return (shell);
}
