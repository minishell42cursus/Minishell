#include "minishell.h"

void	launch_processes(void)
{
	int		i;
	t_nod	*node;

	i = g_shell->n_proc;
	node = g_shell->p_lst;
	if (i == 1)
		launch_from_father(node);
	else
	{
		while (i > 0)
		{
			// do whatever to launch processs;
			node = node->next;
			i--;
		}
	}

