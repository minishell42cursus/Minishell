#include "minishell.h"

void	free_process_list(void)
{
	t_nod	*node;
	t_nod	*aux;

	node = g_shell->p_lst;
	while (node)
	{
		free_matrix(node->cmd);
		aux = node;
		node = node->next;
		//fprintf(stderr, "aux->line_save: %p\naux->line_aux_save: %p\naux: %p\n", aux->line_save, aux->line_aux_save, aux); 
		free_three_ptrs(aux->line_save, aux->line_aux_save, aux);
	}
}

void	unlink_all_heredocs(void)
{
	t_nod	*node;
	char	*current_path;
	int		i;

	i = g_shell->n_proc;
	node = g_shell->p_lst;
	current_path = getcwd(NULL, 0);
	chdir(PATH_TO_TMP);
	while (i > 0)
	{
		if (node->hdoc_name)
		{
			unlink(node->hdoc_name);
			free(node->hdoc_name);
		}
		node = node->next;
		i--;
	}
	chdir(current_path);
	free(current_path);
	g_shell->n_proc = 0;
	g_shell->pid = 0;
}
