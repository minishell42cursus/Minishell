#include "minishell.h"

/* function that gives a different string for each
 * consecutive entry with reset != 0. It will be used
 * to name all heredocs created.*/
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
		name = ft_strjoin(".here_doc", aux);
		free(aux);
		i = i + 1;
	}
	return (name);
}

char	*eof_gatherer(char **line, int *n_hdoc)
{
	char	*eof;
	char	*aux;
	char	*str;
	int		len;

	len = string_length_bash(*line, KO);
	aux = malloc(sizeof(char) * (len + 1));
	eof = aux;
	str = *line;
	while (len > 0)
	{
		if (*str != '*')
		{
			*aux++ = *str;
			len--;
		}
		*str++ = ' ';
	}
	*aux = '\0';
	*(--str) = '\\';
	*n_hdoc = *n_hdoc + 1;
	return (eof);
}

/*We still need to use 2 different strings to keep parsing, the one
 * that has all strings "muted" (with blanks inside) and the one that doesnt.
 * This essentially sets everything for the next parsing step,
 * other redirections */
void	rebuild_aux_strings(t_nod *node)
{
	node->line_aux = ft_strdup(node->line);
	node->line_aux_save = node->line_aux;
	comma_parser(&node->line_aux, NULL);
}

void	write_line_on_hdoc(char *line, int fd)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
}
