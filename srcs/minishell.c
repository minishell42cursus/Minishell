#include "../includes/minishell.h"

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

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	char *cmd;

	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
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
