#include "minishell.h"

/*Returns the length of the "process command string". Example:
 * cmd: [ls -l < a >> c | < lol >c cat | grep >> lulz < a hi].
 * ret1 = len(ls -l < a >> c ),
 * ret2 = len( < lol >c cat ),
 * ret3 = len( grep >> lulz < a hi).*/
static size_t	process_str_length(char	*str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (i);
		i++;
	}
	return (i);
}

static void	pointer_mover(char **aux, char **str, size_t len)
{
	if (*(*aux + len) == '|')
	{
		*str = *str + len + 1;
		*aux = *aux + len + 1;
	}
	else
	{
		*str = *str + len;
		*aux = *aux + len;
	}
}

t_nod	*create_pnode(char **aux, char **str, int *n_proc)
{
	t_nod	*process;
	size_t	len;

	process = malloc(sizeof(t_nod));
	process->p_nbr = ++(*n_proc);
	process->fdi = 0;
	process->fdo = 1;
	len = process_str_length(*aux);
	process->line = ft_substr(*str, 0, len);
	process->line_aux = ft_substr(*aux, 0, len);
	process->line_save = process->line;
	process->line_aux_save = process->line_aux;
	pointer_mover(aux, str, len);
	return (process);
}

void	process_command_parsing(t_shell *shell)
{
	t_nod	*p_nd;

	shell->parse_rl = shell->rl_tofree;
	shell->rl_aux = shell->rl;
	p_nd = create_pnode(&shell->parse_rl, &shell->rl_aux, &shell->n_proc);
	shell->p_lst = p_nd;
	while (*shell->parse_rl)
	{
		p_nd->next = create_pnode(&shell->parse_rl, &shell->rl_aux, &shell->n_proc);
		p_nd = p_nd->next;
	}
	free(shell->rl_tofree);
}
