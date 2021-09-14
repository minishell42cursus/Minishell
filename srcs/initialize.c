#include "minishell.h"

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
	shell->status = ON_READ;
	return (shell);
}
