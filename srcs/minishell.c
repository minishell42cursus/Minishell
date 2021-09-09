#include "minishell.h"

int main(int argc, char *argv[], char *env[])
{
	t_shell		*shell;
	t_nod		*node;

	if (argc != 1) // No lo había pensado, pero esto es bastante importante.
		call_error(); 
	shell = init_megastruct(argc, argv, env);
	add_variable_to_local_env();
	ft_signal_main(); //Función para señales (finalizado)
	//env = tabdup(env);
	while (1)
   	{
		shell->rl = readline(MINISHELL);
		if (!initial_parser(shell))
		{
			add_history(shell->rl);
			process_command_parsing();
			heredoc_piece();
			other_io_redirections();
			//gather_process_arguments();
			(void)node;
			; //Expansión de variables de entorno y strings (están blanqueadas hasta este punto).
			; //recolección de comando + respectivos argv's.
			if(ft_isbuiltin(&shell->rl))
			{
				printf("\nEs builting\n");
				ft_isrun(&shell->rl);
			}
			; //lanzamiento de procesos.
			; //Aquí podríamos hacer una recopilación de todas las cosas que liberaremos después de la ejecucion de los comandos.
			unlink_all_heredocs(shell);
			free_process_list(shell);
		}
		else
			printf("$? = %i\n", shell->q_mark_err);
		//system("leaks minishell");
	}
	rl_clear_history();
	//system("leaks minishell");
	return (0);
}
