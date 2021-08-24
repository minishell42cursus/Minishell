#include <stdio.h>

void ft_env(char **env)
{
	int i;

	i = 0;
	while(env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

/*int main (int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	bi_env(env);
}*/
