#include "minishell.h"

int main(int argc, char *argv[], char *env[])
{
	t_shell		*shell;

	if (argc != 1)
		call_error();
	shell = init_megastruct(argc, argv, env);
	while (1)
   	{
		ft_signal_main();
		g_shell->rl = readline(MINISHELL);
		if (!initial_parser())
		{
			process_command_parsing();
			heredoc_piece();
			other_io_redirections();
			gather_process_arguments();
			launch_processes();
			; //Aquí podríamos hacer una recopilación de todas las cosas que liberaremos después de la ejecucion de los comandos.
			unlink_all_heredocs(shell);
			free_process_list(shell);
		}
		else
			printf("$? = %i\n", shell->q_mark_err);
	}
	rl_clear_history();
	return (0);
}
