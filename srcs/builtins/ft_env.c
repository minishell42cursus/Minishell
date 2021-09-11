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
	int j;
	char temp[40];

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
		while (i++ < 3)
		{
			j = i;
			while (j++ < 3)
			{
				if (strcmp(g_shell->env[i], g_shell->env[j]) > 0)
				{
					strcpy(temp, g_shell->env[i]);
					strcpy(g_shell->env[i], g_shell->env[j]);
					strcpy(g_shell->env[j],temp);
				}
			}
		}
		while (g_shell->env[i])
		{
			printf("declare - x %s\n", g_shell->env[i]);
			i++;
		}
	}
}
