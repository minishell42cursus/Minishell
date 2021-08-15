#include "minishell.h"

void    handler(int signum)
{
    if (signum == SIGINT)
    {   //ctrl + c
	   	printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
    if (signum == SIGQUIT)
   	{
		//ctrl + \ /
		printf("\b\b  \b\b");
	}
}

void    ft_ctrl_d()
{
	//ctrl + d
	//SIGTERM
	printf("exit\n");
	exit(0);
}

int main(int argc, char *argv[], char *env[])
{
	t_shell		shell;
	char 		*cmd;
	(void)argc; //Esto es porque no se usa de momento
	(void)argv; //Esto es porque no se usa de momento

	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	init_megastruct(&shell, argc, argv, env);
	while (1)
   	{
		cmd = readline("minishell> ");
		if (!cmd) //ctrl + d
			ft_ctrl_d();
		printf("%s\n", cmd);
		add_history(cmd);
		free(cmd);
	}
	return (0);
}
