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
	while (*str != ' ' && *str)
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

	aux = malloc(sizeof(char) * (string_length_bash(*aux) + 1));
	eof = aux;
	str = *line;
	while (len > 0)
	{
		if (*str != '*')
			*aux++ = *str++;
		str++;
		len--;
	}
	*aux = '\0';
	return (eof);	
}

void	place_str_pointers(char **aux, char **str_blank, char **str_full)
{
	long double	displacement;

	*aux = *aux + 2;
	while (**aux == ' ')
		*(*aux)++;
	displacement = *aux - *str_blank;
	*str_full = *str_full + displacement;
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
		eof = eof_gatherer(&aux, &node->line);
		printf("%s\n", eof);
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
