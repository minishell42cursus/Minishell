#include "minishell.h"

void	free_process_list(t_shell *shell)
{
	t_nod	*node;
	t_nod	*aux;

	node = shell->p_lst;
	while (shell->n_proc > 0)
	{
		free_matrix(node->cmd);
		aux = node;
		node = node->next;
		fprintf(stderr, "aux->line_save: %p\naux->line_aux_save: %p\naux: %p\n", aux->line_save, aux->line_aux_save, aux); 
		free_three_ptrs(aux->line_save, aux->line_aux_save, aux);
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
