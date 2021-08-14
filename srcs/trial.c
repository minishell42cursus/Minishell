#include "../includes/minishell.h"

void	init_megastruct(t_shell	*shell, int ac, char **av, char **env)
{
	shell = malloc(sizeof(t_shell));
	shell->ac = ac;
	shell->av = av;
	shell->env = env;
	shell->fdi = dup(0);
	shell->fdo = dup(1);
}

int main(int ac, char **av, char **env)
{
	t_shell	shell;
	char	*str;
	char	*aux;

	init_megastruct(&shell, ac, av, env);
	while (1)
	{
		str = readline("$>");
		if (ctr+D)
			exit (0);
		aux = str;
		parse_error(str);
		process_building(str);
		printf("%s\n", str);
		//str = "puta";
		//rl_redisplay();
		if (notseñalctr+C)
			add_history(str);
		//rl_replace_line(str, 1);
		free(aux);
		//rl_on_new_line();
		//rl_clear_history();
		//break;
	}
	rl_clear_history();
	return (0);
}
