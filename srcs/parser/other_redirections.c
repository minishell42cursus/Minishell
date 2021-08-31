#include "minishell.h"

char	*filename_gatherer(char **line)
{
	char	*filename;
	char	*aux;
	char	*str;
	int		len;

	len = string_length_bash(*line);
	aux = malloc(sizeof(char) * (len + 1));
	filename = aux;
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
	return (filename);
}

void	double_right_red(t_nod *node, char **aux)
{
	char	*filename;

	place_str_pointers(aux, &node->line_aux, &node->line, 2);
	filename = filename_gatherer(&node->line);
	printf("filename: [%s]\n", filename);
	printf("node->line_aux: [%s]\n", node->line_aux);
	printf("node->line: [%s]\n", node->line);
}

void	redirection_checker(t_nod *node)
{
	char	*aux;

	aux = node->line_aux;
	while (*aux)
	{
		if (*aux == '>' || *aux == '<')
		{
			if (*(aux + 1) == '>')
			{
				aux = aux + 2;
				double_right_red(node, &aux);
			}
			else
			{
				aux = aux + 1;
				//single_red(node, &aux);
			}
		}
		else
			aux++;
	}
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
