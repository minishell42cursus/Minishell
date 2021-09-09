#include "minishell.h"

int	len_name(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int 	check_in_env(char *str, char **env)
{
	int sz;
	int i;

	i = 0;
	sz = len_name(str);
	while (env[i])
	{
		if (ft_memcmp(env[i], str, sz + 1) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	**ad_arg(char **env, char *str)
{
	char	**env2;
	int	i;

	i = check_in_env(str, env);
	if (i != -1)
	{
		free (env[i]);
		env[i] = str;
		return (env);
	}
	else
	{
		env2 = malloc(sizeof(char *) * tablen(env) + 2);
		while(env[i])
		{
			env2[i] = env[i];
			i++;
		}
		printf("%s\n", str);
		env2[i] = ft_strdup(str);
		env2[i + 1] = NULL;
		free(env);
	}
	return (env2);
}

void	ft_export(char **env, char **argv)
{
	int i;

	i = 0;
	(void)argv;
	//if (!argv[0])
	ft_env(env, 1);
	return ;
	while(argv[i])
	{
		env = ad_arg(env, argv[i]);
		i++;
	}
}

/*int main(int argc, char **argv, char **env)
{
	(void)argc;
	ft_export(env, argv);
	return (0);

}*/
