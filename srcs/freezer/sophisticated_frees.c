#include "minishell.h"

void	free_process_list(t_shell *shell)
{
	t_nod	*node;
	t_nod	*aux;

	g_shell->status = ON_READ;
	g_shell->assign_error = OK;
	node = shell->p_lst;
	while (shell->n_proc > 0)
	{
		aux = node;
		node = node->next;
		free_two_ptrs(aux->line, aux);
		shell->n_proc--;
	}
}

void	unlink_all_heredocs(t_shell *shell)
{
	t_nod	*node;
	char	*current_path;
	int		i;

	i = shell->n_proc;
	node = shell->p_lst;
	current_path = getcwd(NULL, 0);
	chdir(PATH_TO_TMP);
	while (i > 0)
	{
		if (node->hdoc_name)
			unlink(node->hdoc_name);
		node = node->next;
		i--;
	}
	chdir(current_path);
	free(current_path);
	shell->n_proc = 0;
	g_shell->pid = 0;
}
