#include "minishell.h"

void	ft_exit(t_shell *shell, char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	shell = NULL;
	//free_command(shell);
	printf("exit\n");
	exit(0);
}
