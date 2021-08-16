#include "minishell.h"

void	init_megastruct(t_shell	*shell, int ac, char **av, char **env)
{
	shell = malloc(sizeof(t_shell));
	shell->ac = ac;
	shell->av = av;
	shell->env = env;
	shell->fdi = dup(0);
	shell->fdo = dup(1);
//	shell->lst_env = NULL;
//	while (*env)
//		ft_lstadd_front(&shell->lst_env, ft_lstnew(ft_strdup(*env++)));
//	shell->env = ft_lst_get_array(shell->lst_env);

}
