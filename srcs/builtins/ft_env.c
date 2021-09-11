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
	char *aux;

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
		while (i < 29)
		{
			j = i+1;
			while (j < 29)
			{
				if (strcmp(g_shell->env[i], g_shell->env[j]) > 0)
				{
					//printf("\nAntes%s", g_shell->env[i]);
					aux = g_shell->env[j];
					g_shell->env[j] = g_shell->env[i];
					g_shell->env[i] = aux;
					//printf("\nDespuess%s\n", g_shell->env[i]);
					printf("\nI vale: %d y J vale: %d\n", i, j);
				}
				j++;
			}
			i++;
		}
		i = 0;
		while (g_shell->env[i])
		{
			printf("declare - x %s\n", g_shell->env[i]);
			i++;
		}
	}
}
