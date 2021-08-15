#include "minishell.h"

void	run_builtin(t_shell *shell, char **name)
{
	(void)shell;
	if (!ft_strncmp(*name, "echo", ft_strlen(*name)))
		printf("entra");
//		ft_echo(shell->av);
	/*else if (!ft_strncmp(name, "cd", ft_strlen(name)))
		ft_cd(cmnd->arg, msh);
	else if (!ft_strncmp(name, "pwd", ft_strlen(name)))
		ft_pwd();
	else if (!ft_strncmp(name, "export", ft_strlen(name)))
		ft_export(cmnd->arg, msh);
	else if (!ft_strncmp(name, "unset", ft_strlen(name)))
		ft_unset(cmnd->arg, msh);
	else if (!ft_strncmp(name, "env", ft_strlen(name)))
		ft_env(cmnd->arg, msh->env, msh);
	else if (!ft_strncmp(name, "exit", ft_strlen(name)))
		ft_exit(cmnd->arg, msh);
	else
		ft_putendl_fd("Impossible!", 2);*/
}
