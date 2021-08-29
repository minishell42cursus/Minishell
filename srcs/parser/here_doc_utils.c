#include "minishell.h"

/* A pointer mover. We work with 2 strings, the one that has something inside
 * the commas, and the one that doesnt. This is because its easier to work with
 * a string that does not look inside "" / '' strings, so we can spot which
 * redirection, pipe or whatever is relevant or not when parsing.
 * Minishell  SHOULD NOT workr when given <<, >>, <, >, | inside commas. These
 *will always have to be gathered as arguments for a command. Just like bash.*/
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

static void	edit_string(char **str, int *i)
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
static int	string_length_bash(char *str)
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
