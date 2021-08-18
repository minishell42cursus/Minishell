#include "minishell.h"

t_shell	*init_megastruct(int ac, char **av, char **env)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	printf("%p\n", shell);
	shell->ac = ac;
	shell->av = av;
	shell->env = env;
	shell->fdi = dup(0);
	shell->fdo = dup(1);
	shell->q_mark_err = 0;
	shell->n_frk = 0;
	return (shell);
//	shell->lst_env = NULL;
//	while (*env)
//		ft_lstadd_front(&shell->lst_env, ft_lstnew(ft_strdup(*env++)));
//	shell->env = ft_lst_get_array(shell->lst_env);

}
