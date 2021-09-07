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

void	unlink_all_heredocs(t_shell *shell)
{
	t_nod	*node;
	int		i;

	i = shell->n_proc;
	node = shell->p_lst;
	chdir("./tmp");
	while (i > 0)
	{
		if (node->hdoc_name)
			unlink(node->hdoc_name);
		node = node->next;
		i--;
	}
	chdir("../");
	shell->n_proc = 0;
}
