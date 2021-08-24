#include "minishell.h"

int main(int argc, char *argv[], char *env[])
{
	t_shell		*shell;
	t_nod		*node;

	if (argc != 1) // No lo había pensado, pero esto es bastante importante.
		call_error(); 
	shell = init_megastruct(argc, argv, env); //Función para inicializar datos
	ft_signal_main(); //Función para señales (finalizado)
	env = tabdup(env);
	while (1)
   	{
		shell->rl = readline(MINISHELL);
		if (!initial_parser(shell))
		{
			process_command_parsing(shell); //detección del número de procesos y sus respectivas lineas de comandos.
			(void)node;
			; //apertura de here_docs.
			; //apertura de otros fd's.
			; //Expansión de variables de entorno y strings (están blanqueadas hasta este punto).
			; //recolección de comando + respectivos argv's.
			; //lanzamiento de procesos.
			; //Aquí podríamos hacer una recopilación de todas las cosas que liberaremos después de la ejecucion de los comandos.
			free_process_list(shell);
		}
		else
			printf("$? = %i\n", shell->q_mark_err);
		//run_builtin(&shell, &argv[1]); //Función SOLO para testear builtins, luego esto va fuera
		add_history(shell->rl);
		if (shell->rl)
			free(shell->rl);
		//system("leaks minishell");
	}
	rl_clear_history();
	//system("leaks minishell");
	return (0);
}

//poner despues de process_command_parsing(shell) para testear la correcta creación de la lista y sus respectivas lineas de comando:

			/*node = shell->p_lst;
			while (shell->n_proc > 0)
			{
				//printf("node pointer: %p\nprocess number: %i\nstring: %p\n", node, node->p_nbr, node->line); 
				//printf("process number: %i\n string: |%s|\n", node->p_nbr, node->line); 
				node = node->next;
				shell->n_proc--;
			}*/
