#include "minishell.h"

int main(int argc, char *argv[], char *env[])
{
	t_shell		*shell;

	if (argc != 1) // No lo había pensado, pero esto es bastante importante.
		call_error(); 
	shell = init_megastruct(argc, argv, env);
	ft_signal_main(); //Función para señales (finalizado)
	while (1)
   	{
		g_shell->rl = readline(MINISHELL);
		if (!initial_parser())
		{
			process_command_parsing();
			heredoc_piece();
			other_io_redirections();
			gather_process_arguments();
			//launch_processes();
			if(ft_isbuiltin(&shell->rl))
			{
				printf("\nEs builting\n");
				ft_isrun(&shell->rl);
			}
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
