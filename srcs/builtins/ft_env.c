#include "minishell.h"

char	**ft_orderenv(char **env)
{
	int			i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	
	return (env);
}

void ft_env(int mode)
{
	int i;

	if (mode == 0)
	{
		i = 0;
		while(g_shell->env[i])
		{
			printf("%s\n", g_shell->env[i]);
			i++;
		}
	}
	else
	{
		i = 0;
		while (g_shell->env[i])
		{
			printf("%s\n", g_shell->env[i]);
			i++;
		}
	}
}
