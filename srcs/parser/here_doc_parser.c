#include "minishell.h"

static void	write_line_on_hdoc(char *line, int fd)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
}

static void	clean_other_hdoc(t_nod *node)
{
	//Aquí hace falta una llamada a ft_cd que me lleve de donde esté a la carpeta
	// /Users/carce-bo/Desktop/cursus42/entregas/minishell/.tmp.
	if (node->fdi != 0)
	{
		close(node->fdi);
		unlink(node->hdoc_name);
		free(node->hdoc_name);
	}
	node->hdoc_name = hdoc_filename(1);
	node->fdi = open(node->hdoc_name, O_RDWR | O_CREAT, 00644);
}

static void	open_heredoc(char *eof, t_nod *node)
{
	char	*line;

	chdir("./.tmp");
	clean_other_hdoc(node);
	while (1)
	{
		write(2, "$> ", 3);
		get_next_line(0, &line);
		if (!ft_strncmp(line, eof, ft_maxlen(line, eof)))
		{
			free(line);
			break ;
		}
		else
			write_line_on_hdoc(line, node->fdi);
	}
	chdir("../");
}

static void	clean_hdoc_strings(t_nod *node)
{
	char	*aux;
	int		counter;

	counter = node->n_hdoc;
	aux = node->line_save;
	while (*aux && (counter > 1))
	{
		aux = ft_strnstr(aux, "\\", ft_strlen(aux));
		*aux = ' ';
		counter--;
	}
	aux = ft_strnstr(aux, "\\", ft_strlen(aux));
	if (!aux)
		return ;
	aux++;
	while (*aux == '*' && *aux)
		*aux++ = ' ';
	free(node->line_aux_save);
	node->line = node->line_save;
}

static void	hd_checker(t_nod *node)
{
	char	*aux;
	char	*eof;

	aux = node->line_aux;
	while (*aux)
	{
		aux = ft_strnstr(aux, "<<", ft_strlen(aux));
		if (!aux)
			break ;
		else
			place_str_pointers(&aux, &node->line_aux, &node->line);
		eof = eof_gatherer(&node->line, &node->n_hdoc);
		open_heredoc(eof, node);
		/*printf("this is the hdoc end of file: [%s]\n", eof);
		printf("this is the node line_aux: [%s]\n", node->line_aux);
		printf("this is the node line: [%s]\n", node->line);
		printf("this is the node line_save: [%s]\n", node->line_save);
		printf("this is the node line_aux_save: [%s]\n", node->line_aux_save);
		printf("\n\n");*/
		; //crear el heredoc con su fd, acutallizarlo, y escribir sobre el.
		; // acuerdate de procesar ^D !!!
	}
	clean_hdoc_strings(node);
	printf("this is the hdoc end of file: [%s]\n", eof);
	//printf("this is the node line_aux: [%s]\n", node->line_aux);
	printf("this is the node line: [%s]\n", node->line);
	printf("this is the node line_save: [%s]\n", node->line_save);
	//printf("this is the node line_aux_save: [%s]\n", node->line_aux_save);
	printf("\n\n");
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
