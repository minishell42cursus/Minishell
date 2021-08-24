#include "minishell.h"

char	**exec_built_in(t_shell *shell, char **env)
{
	if (shell->index == 1)
		ft_echo(shell->argv);
	else if (shell->index == 2)
		ft_pwd(env);
	else if (shell->index == 3)
		ft_env(env);
	else if (shell->index == 4)
		ft_cd(shell->av[1], env);
	else if (shell->index == 5)
		env = ft_export(env, shell->av + 1);
	else if (shell->index == 6)
		env = ft_unset(env, shell->av + 1);
	else if (shell->index == 7)
		env = ft_exit(shell, env);
	return (env);
}
