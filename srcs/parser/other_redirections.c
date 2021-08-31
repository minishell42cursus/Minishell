#include "minishell.h"

void	redirection_checker(t_nod *node)
{
	char	*aux;
	char	*name;

}

void	other_io_redirections(t_shell *shell)
{
	int		i;
	t_nod	*node;

	i = shell->n_proc;
	node = shell->p_lst;
	while (i > 0)
	{
		redirection_checker(node);
		node = node->next;
		i--;
	}
}
