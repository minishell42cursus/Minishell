#include "minishell.h"

void	select_index(t_shell *shell, char **env)
{
	if (shell->index == 1)
		ft_echo(shell->argv);
	else if (shell->index == 2)
		ft_pwd(env);
	else if (shell->index == 3)
		ft_env(env);
	exit(0);
}
