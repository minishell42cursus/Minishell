#include "minishell.h"

int main(int argc, char *argv[], char *env[])
{
	t_shell		shell;
	(void)argv; //Esto es porque no se usa de momento

	if (argc != 1) // No lo había pensado, pero esto es bastante importante.
		call_error(); 
	init_megastruct(&shell, argc, argv, env); //Función para inicializar datos
	ft_signal_main(); //Función para señales (finalizado)
	while (1)
   	{
		shell.rl = readline(MINISHELL);
		if (!initial_parser(&shell))
		{
			; //detección del número de procesos y sus respectivas lineas de comandos.
			; //apertura de here_docs.
			; //apertura de otros fd's.
			; //recolección de comando + respectivos argv's.
			; //lanzamiento de procesos.
		}
		else
			printf("$? = %i\n", shell.q_mark_err);
		//run_builtin(&shell, &argv[1]); //Función SOLO para testear builtins, luego esto va fuera
		add_history(shell.rl);
		free(shell.rl);
	}
	rl_clear_history();
	//system("leaks minishell");
	return (0);
}
