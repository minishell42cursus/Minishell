#include "minishell.h"

void	ft_exit(void)
{
	int i;

	i = 0;
	while (g_shell->env[i])
	{
		free(g_shell->env[i]);
		i++;
	}
	free(g_shell->env[i]);
	free(g_shell->env);
	g_shell = NULL;
	printf("exit\n");
	exit(0);
}
