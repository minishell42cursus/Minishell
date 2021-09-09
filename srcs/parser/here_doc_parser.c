/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:31:31 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/09 22:35:25 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_line_on_hdoc(char *line, int fd);
void	rebuild_aux_strings(t_nod *node);

static void	clean_other_hdoc(t_nod *node)
{
	if (node->fdi != 0)
	{
		close(node->fdi);
		unlink(node->hdoc_name);
		free(node->hdoc_name);
	}
	node->hdoc_name = hdoc_filename(1);
	node->fdi = open(node->hdoc_name, O_RDWR | O_CREAT, 00644);
}

/* Aquí hace falta meter que me devuelva a la carpeta en la
 * que se encontraba antes de entrar en el directorio de tmp.
 * De momento es tal que vuelve a la carpeta minishell si es que
 * estaba allí, pero podría ser que estuviese en otro sitio.*/
static void	open_heredoc(char *eof, t_nod *node)
{
	char	*line;

	chdir(PATH_TO_TMP);
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
		{
			aux = aux + 2;
			place_str_pointers(&aux, &node->line_aux, &node->line, 2);
		}
		eof = eof_gatherer(&node->line, &node->n_hdoc);
		open_heredoc(eof, node);
	}
	clean_hdoc_strings(node);
}

void	heredoc_piece(void)
{
	int		i;
	t_nod	*node;

	i = g_shell->n_proc;
	node = g_shell->p_lst;
	while (i > 0)
	{
		hd_checker(node);
		rebuild_aux_strings(node);
		node = node->next;
		i--;
	}
	hdoc_filename(0);
}
