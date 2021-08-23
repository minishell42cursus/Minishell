#include "minishell.h"

char	*hdoc_filename(int reset)
{
	char		*aux;
	char		*name;
	static int	i;

	if (!i)
		i = 0;
	aux = NULL;
	name = NULL;
	if (reset == 0)
		i = 0;
	else
	{
		aux = ft_itoa(i);
		name = ft_strjoin("here_doc", aux);
		free(aux);
		i = i + 1;
	}
	return (name);
}

void	hd_checker(t_nod *node)
{
	char	*aux;
	char	*eof;

	aux = node->line_aux;
	while (*aux)
	{
		aux = ft_strnstr(aux, "<<", ft_strlen(aux));
		if (!aux)
			break ;
		eof = eof_gatherer(&aux, &node->line);
		; //crear el heredoc con su fd, acutallizarlo, y escribir sobre el.
		; // acuerdate de procesar ^D !!!
	}
}


void	heredoc_piece(t_shell *shell)
{
	int		i;
	t_nod	*node;

	i = shell->n_proc;
	node = shell->p_lst;
	while (i > 0)
	{
		hd_checker(node);
		node = node->next;
		i--;
	}
	hdoc_filename(0);
}

/*void	here_doc_input(t_pip *p, int pip[2])
{
	char	*line;

	write(p->fdo, "$> ", 3);
	get_next_line(p->fdi, &line);
	if (!ft_strncmp(line, p->argv[2], max_len(line, p->argv[2])))
	{
		free(line);
		close(pip[1]);
		exit(0);
	}
	else
	{
		write(pip[1], line, ft_strlen(line));
		write(pip[1], "\n", 1);
		free(line);
		here_doc_input(p, pip);
	}
}*/


/*
int main()
{
	int	i;

	i = 0;
	while (i++ < 20)
		printf("%s\n", hdoc_filename(1));
	printf("%s\n", hdoc_filename(0));
	i = 0;
	while (i++ < 20)
		printf("%s\n", hdoc_filename(1));
	return (0);
}*/
