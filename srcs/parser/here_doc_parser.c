#include "minishell.h"

size_t	max_len(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 >= len2)
		return (len1);
	else
		return (len2);
}

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

void	edit_string(char **str, int *i)
{
	if (**str == '\"')
	{
		**str = '*';
		while (*(++(*str)) != '\"')
			(*i)++;
	}
	else
	{
		**str = '*';
		while (*(++(*str)) != '\'')
			(*i)++;
	}
	**str = '*';
}

/* computes the length of the string that it has to take out
 * from the piece of command. it should exactly coincide with
 * the mesure of the strings bash uses as args/filenames, 
 * exhibiting commas and allowing appended strings to start or
 * ends of comma strings when not spaced. An example of this would
 * be: << "hey""dude" is a heredoc whichs EOF is heydude, and so is 
 * << "hey"dude, <<hey"dude", and any combination you can imagine
 * from this. Tedious.
 * This function apart from computing this length it marks with a
 * '*' those chars that will not have to be written inside the 
 * final string that has to be gathered. 2 in 1 :D*/
int	string_length_bash(char *str)
{
	int	i;

	i = 0;
	while (*str == ' ')
		str++;
	while (*str != ' ' && *str != '<' && *str != '>' && *str)
	{
		if (*str == '\"' || *str == '\'')
			edit_string(&str, &i);
		else
			i++;
		str++;
	}
	return (i);
}

char	*eof_gatherer(char **line)
{
	char	*eof;
	char	*aux;
	char	*str;
	int		len;

	len = string_length_bash(*line);
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
	return (eof);
}

/* A pointer mover. We work with 2 strings, the one that has something inside 
 * the commas, and the one that doesnt. This is because its easier to work with
 * a string that does not look inside "" / '' strings, so we can spot which 
 * redirection, pipe or whatever is relevant or not when parsing.
 * Minishell  SHOULD NOT workr when given <<, >>, <, >, | inside commas. These
 * will always have to be gathered as arguments for a command. Just like bash.*/
void	place_str_pointers(char **aux, char **str_blank, char **str_full)
{
	long double	displacement;

	*aux = *aux + 2;
	while (**aux == ' ')
		(*aux)++;
	displacement = *aux - *str_blank;
	while (displacement-- > 0)
		*str_full = *str_full + 1;
	displacement = *aux - *str_blank;
	while (displacement-- > 0)
		*str_blank = *str_blank + 1;
}

void	open_heredoc(char *eof, t_nod *node)
{
	char	*line;

	chdir("./.tmp");
	node->fdi = open(hdoc_filename(1), O_CREAT); 
	while (1)
	{
		write(node->fdi, "$> ", 3);
		get_next_line(node->fdi, &line);
		if (!ft_strncmp(line, eof, max_len(line, eof)))
		{
			free(line);
			break ;
		}
		else
		{
			write(node->fdi, line, ft_strlen(line));
			write(node->fdi, "\n", 1);
			free(line);
		}
	}
	chdir("../");
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
		else
			place_str_pointers(&aux, &node->line_aux, &node->line);
		eof = eof_gatherer(&node->line);
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
	shell->n_proc = 0;
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
