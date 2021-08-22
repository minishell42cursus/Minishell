#include "minishell.h"

void	free_process_list(t_shell *shell)
{
	t_nod	*node;
	t_nod	*aux;

	node = shell->p_lst;
	while (shell->n_proc > 0)
	{
		aux = node;
		node = node->next;
		free(aux->line);
		free(aux);
		shell->n_proc--;
	}
}
