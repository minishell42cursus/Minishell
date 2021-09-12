#include "minishell.h"

int	find_env(char **env, char *word)
{
	int		x;
	int		y;

	x = 0;
	while (env[x])
	{
		y = 0;
		while (env[x][y] && (env[x][y] == word[y] || env[x][y] == 61))
		{
			if (env[x][y] == '=' && (word[y] == ' ' || !word[y]))
				return (x);
			y++;
		}
		x++;
	}
	return (-1);
}

char	**supp_arg(char **env, char *str)
{
	int i;
	int j;
	int b;
	char **env2;

	b = 0;
	j = 0;
	i = find_env(env, str);
	printf("%s %d\n", str, i);
	if (i == -1)
		return (env);
	env2 = malloc(sizeof(char *) * tablen(env));
	while(env[j + b])
	{
			if (j == i)
				b = 1;
			env2[j] = env[j + b];
			j++;
	}
	env2[j] = NULL;
	free(env);
	return(env2);
}

char	**ft_unset(char **env, char **av)
{
	int i;

	i = 0;
	while(av[i])
	{

		env = supp_arg(env, av[i]);
		i++;
	}
	return (env);
}
