#include "minishell.h"

void	ft_exit(t_shell *shell, char **env)
{
	int i;

	i = 0;
	(void)shell;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env[i]);
	free(env);
	shell = NULL;
	printf("exit\n");
	exit(0);
}
