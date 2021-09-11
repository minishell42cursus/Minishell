#include "minishell.h"

void	ft_orderenv(void)
{
	int			i;
	int			j;
	int			k;
	char		*aux;

	k = 0;
	while (g_shell->env[k])
		k++;
	i = 0;
	while (i < k - 1)
	{
		j = i + 1;
		while (j < k - 1)
		{
			if (strcmp(g_shell->env[i], g_shell->env[j]) > 0)
			{
				aux = g_shell->env[j];
				g_shell->env[j] = g_shell->env[i];
				g_shell->env[i] = aux;
			}
			j++;
		}
		i++;
	}
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
		ft_orderenv();
		i = 0;
		while (g_shell->env[i])
		{
			printf("declare - x %s\n", g_shell->env[i]);
			i++;
		}
	}
}
