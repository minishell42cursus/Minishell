#include "minishell.h"

int main(int argc, char *argv[], char *env[])
{
	t_shell		shell;
	char 		*cmd;
	(void)argc; //Esto es porque no se usa de momento
	(void)argv; //Esto es porque no se usa de momento

	init_megastruct(&shell, argc, argv, env); //Función para inicializar datos
	ft_signal_main(); //Función para señales (finalizado)
	while (1)
   	{
		cmd = readline(MINISHELL);
		if (!cmd)
		{
			cmd = ft_strdup("exit");
			printf("%s", cmd);
			exit(0);
		}
		printf("%s\n", cmd);
		//run_builtin(&shell, &argv[1]); //Función SOLO para testear builtins, luego esto va fuera
		add_history(cmd);
		free(cmd);
	}
	rl_clear_history();
	//system("leaks minishell");
	return (0);
}
