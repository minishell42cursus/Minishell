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
	/*printf("g_shell->q_mark_err: %p\nshell->q_mark_err: %p\n", &g_shell->q_mark_err, &shell->q_mark_err);
	g_shell->q_mark_err = 123;
	printf("g_shell->q_mark_err: %i\nshell->q_mark_err: %i\n", g_shell->q_mark_err, shell->q_mark_err);*/
	shell->n_proc = 0;
	shell->envar = new_env_var(ft_strdup("?"), ft_itoa(g_shell->q_mark_err));
	shell->status = ON_READ;
	shell->assign_error = OK;
	return (g_shell);
}
