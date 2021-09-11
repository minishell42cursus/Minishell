#include "minishell.h"

/* String is pointing to a \  or &, hardcoded there to be
 * recognised as enviroment variables to be expanded. */
static char	*modify_length(char *str, int *len, int *i)
{
	char	*var_name;
	char	*var_value;
	int		length_wo_expansion;

	var_name = get_var_name(str);
	var_value = get_var_value(var_name);
	length_wo_expansion = ft_strlen(var_name);
	free(var_name);
	if (!*var_value)
		*len = *len - length_wo_expansion;
	else
		*len = *len - length_wo_expansion + ft_strlen(var_value);
	*i = *i - length_wo_expansion;
	free(var_value);
	return (str + length_wo_expansion);
}

void	add_envar_len(int *len, char *str, int full_line)
{
	int	i;

	i = *len;
	if (full_line == KO)
	{
		while (*str == ' ')
			str++;
	}
	while (i > 0)
	{
		if (*str == '\\' || *str == '&')
			str = modify_length(++str, len, &i);
		else if (*str != '*')
		{
			str++;
			i--;
		}
		else
			str++;
	}
}

/* Same as the get name of variable. It is meant to only get one char
 * if the variable name starts with a number and not a letter*/
static void	do_expand_var(char **line, char **filename, int *len, char *var_value)
{
	int	i;

	i = 0;
	*((*line)++) = ' ';
	if (!ft_isdigit((*line)[i++]))
	{
		while (ft_isalnum((*line)[i]))
		{
			(*line)[i] = ' ';
			i++;
		}
	}
	**line = ' ';
	*line = *line + i;
	while (*var_value)
	{
		*((*filename)++) = *var_value++;
		*len = *len - 1;
	}
}

static void	expand_var_name(char **line, char **filename, int *len, int *launch)
{
	char	*var_name;
	char	*var_value;
	char	*aux;

	var_name = get_var_name((*line + 1));
	var_value = get_var_value(var_name);
	if (**line == '\\' && var_value)
	{
		aux = ft_strnstr(var_value, " ", ft_maxlen(var_value, " "));
		if (aux)
			ambiguous_redirect_error(var_name, launch);
	}
	if (*launch == OK)
		do_expand_var(line, filename, len, var_value);
	free(var_name);
	free(var_value);
}

void	write_str_w_envar(char **line, char **filename, int *len, int *launch)
{
	char	*aux;

	aux = *filename;
	while (*len > 0 && *launch == OK)
	{
		printf("esto es len durante el proceso de mierdas: %i\n", *len);
		printf("esto es la linea: [%s]\n", *line);
		if (**line == '\\' || **line == '&')
		{
			printf("esto es la linea before primer if: [%s]\n", *line);
			expand_var_name(line, filename, len, launch);
			printf("esto es la linea after primer if: [%s]\n", *line);
		}
		else if (**line != '*' && **line != '\\' && **line != '&' && **line)
		{
			printf("esto es la linea before segundo if: [%s]\n", *line);
			*((*filename)++) = **line;
			*((*line)++) = ' ';
			*len = *len - 1;
			printf("esto es la linea after segundo if: [%s]\n", *line);
		}
		else
		{
			printf("esto es la linea before tercer if: [%s]\n", *line);
			*((*line)++) = ' ';
			printf("esto es la linea after tercer if: [%s]\n", *line);
		}

	}
	while (**line == '*')
		*((*line)++) = ' ';
	if (*launch == KO)
		free(aux);
	else
		**filename = '\0';
}