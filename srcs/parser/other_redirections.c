#include "minishell.h"

// Laboratorio de pruebas:

void	add_variable_to_local_env(void)
{
	t_var	*nod;

	g_shell->envar = malloc(sizeof(t_var));
	g_shell->envar->name = ft_strdup("var1");
	g_shell->envar->value = ft_strdup("123");
	nod = malloc(sizeof(t_var));
	nod->name = ft_strdup("a2");
	nod->value = ft_strdup("hello");
	nod->next = NULL;
	g_shell->envar->next = nod;
}

/* glitch: Si la variable se llama
 * hola y acaba en hola=, explota. Como ajuste
 * podriamos hacer que '=' no pudiese entrar dentro
 * de llas definiciones de las variables de entorno */
char	*check_env(char *name)
{
	int		i;
	char	*aux;
	char	*value;

	aux = ft_strjoin(name, "=");
	i = 0;
	while (g_shell->env[i])
	{
		if (!ft_strncmp(g_shell->env[i], aux, ft_strlen(aux)))
			break ;
		i++;
	}
	if (!g_shell->env[i])
		value = NULL;
	else
		value = ft_strtrim(g_shell->env[i], aux);
	free(aux);
	return (value);
}

char	*check_local_env(char *name)
{
	t_var	*var;

	var = g_shell->envar;
	while (var)
	{
		if (!ft_strncmp(var->name, name, ft_maxlen(var->name, name)))
			return (ft_strdup(var->value));
		var = var->next;
	}
	return (ft_strdup(""));
}

/*Theres an adjustment so if an apparent environment variable
 * starts with a number and not a letter it only gets that number
 * as the name of the variable, and so it searches for something that
 * doesnt exist and correctly gives a null string as value.*/
char	*get_var_name(char *str)
{
	int		len;
	char	*name;

	len = 0;
	if (!ft_isdigit(str[len++]))
	{
		while (ft_isalnum(str[len]))
			len++;
	}
	name = ft_substr(str, 0, len);
	return (name);
}

char	*get_var_value(char *name)
{
	char	*value;

	value = check_env(name);
	if (!value)
		value = check_local_env(name);
	return (value);
}

/* String is pointing to a \  or &, hardcoded there to be
 * recognised as enviroment variables to be expanded. */
char	*modify_length(char *str, int *len, int *i)
{
	char	*var_name;
	char	*var_value;
	int		length_wo_expansion;

	var_name = get_var_name(str);
	var_value = get_var_value(var_name);
	//printf("var1 value: [%s]\n", var_value);
	length_wo_expansion = ft_strlen(var_name);
	//printf("length of variable wo exp: %i\n", length_wo_expansion);
	//printf("length of var_value: %zu\n", ft_strlen(var_value));
	free(var_name);
	//printf("length before modification: %i\n", *len);
	if (!*var_value)
		*len = *len - length_wo_expansion;
	else
		*len = *len - length_wo_expansion + ft_strlen(var_value);
	*i = *i - length_wo_expansion;
	//printf("length after modification: %i\n", *len);
	free(var_value);
	return (str + length_wo_expansion);
}

void	add_envar_len(int *len, char *str)
{
	int	i;

	i = *len;
	//printf("previous length: [%i]\n", *len);
	//printf("this is the string to be modified: [%s]\n", str);
	while (*str == ' ')
		str++;
	while (i > 0)
	{
		//printf("%i\n", i);
		//printf("string along the buclesito: [%s]\n", str);
		if (*str == '\\' || *str == '&')
		{
			//printf("string when finding dolla sign: [%s]\n", str);
			str = modify_length(++str, len, &i);
			//printf("string after modifying length: [%s]\n", str);
		}
		else if (*str != '*')
		{
			str++;
			i--;
		}
		else
			str++;
	}
	//printf("string before going out of length adder: [%s]\n", str);
	//printf("new length: [%i]\n", *len);
}

/* Same as the get name of variable. It is meant to only get one char
 * if the variable name starts with a number and not a letter*/
void	do_expand_var(char **line, char **filename, int *len, char *var_value)
{
	int	i;

	i = 0;
	**line = ' ';
	*line = *line + 1;
	if (!ft_isdigit((*line)[i++]))
	{
		while (ft_isalnum((*line)[i]))
		{
			(*line)[i] = ' ';
			i++;
		}
	}
	*line = *line + i;
	while (*var_value)
	{
		*((*filename)++) = *var_value++;
		*len = *len - 1;
	}
}

void	expand_var_name(char **line, char **filename, int *len, int *launch)
{
	char	*var_name;
	char	*var_value;
	char	*aux;
	
	//printf("third layer: %p\n", filename);
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
	//printf("XD this is the line: [%s]\n", *line);
}

void	write_filename(char **line, char **filename, int *len, int *launch)
{
	char	*aux;

	//printf("second layer: %p\n", filename);
	aux = *filename;
	//printf("\n\n\n\n\n");
	//printf("line before starting loop: [%s]\n", *line);
	//printf("its pointer: [%p], *[%p]\n", line, *line);
	while (*len > 0 && *launch == OK)
	{
		//printf("line inside writing loop: [%s]\n", *line);
		//printf("its pointer: [%p], *[%p]\n", line, *line);
		//printf("filename inside writing loop: [%s]\n", filename);
		if (**line == '\\' || **line == '&')
		{
			//printf("line before movement: [%s]\n", *line);
			//printf("len before movement: %i\n", *len);
			expand_var_name(line, filename, len, launch);
			//printf("line after movement: [%s]\n", *line);
			//printf("len after movement: %i\n", *len);
		}
		else if (**line != '*' && **line != '\\' && **line != '&' && **line)
		{
			//printf("line before second if movement: [%s]\n", *line);
			*((*filename)++) = **line;
			*((*line)++) = ' ';
			*len = *len - 1;
			//printf("line after second if movement: [%s]\n", *line);
		}
		else
		{
			//printf("line before being blanked: [%s]\n", *line);
			*((*line)++) = ' ';
			//printf("line after being blanked: [%s]\n", *line);
		}
	}
	while (**line == '*')
		*((*line)++) = ' ';
	if (*launch == KO)
		free(aux);
	else
		**filename = '\0';
}

char	*filename_gatherer(char **line, int *launch)
{
	char	*filename;
	char	*aux;
	int		len;

	len = string_length_bash(*line, OK);
	//printf("initial length: %i\n", len);
	add_envar_len(&len, *line);
	//printf("final length: %i\n", len);
	filename = malloc(sizeof(char) * (len + 1));
	aux = filename;
	//printf("first layer: %p\n", &filename);
	write_filename(line, &aux, &len, launch);
	if (*launch == OK)
		;
		//printf("filename: [%s]\n", filename);
	return (filename);
}

void	move_str_pointers(char **str, char **aux, int i)
{
	int	displacement;

	displacement = i;
	while (displacement-- > 0)
		*str = *str + 1;
	displacement = i;
	while (displacement-- > 0)
		*aux = *aux + 1;
}

void	open_on_append_mode(t_nod *node, char *filename)
{
	if (node->fdo != 1)
		close(node->fdo);
	node->fdo = open(filename, O_APPEND | O_RDWR | O_CREAT, 00644);
	if (node->fdo == -1)
		error_msg_relative_to_file(filename, &node->launch);
}

void	open_on_truncate_mode(t_nod *node, char *filename)
{
	if (node->fdo != 1)
		close(node->fdo);
	node->fdo = open(filename, O_CREAT | O_RDWR | O_TRUNC, 00644);
	if (node->fdo == -1)
		error_msg_relative_to_file(filename, &node->launch);
}

int	check_for_hdoc_priority(char *str)
{
	while (*str)
	{
		if (*str == '\\')
			return (-1);
		str++;
	}
	return (0);	
}

void	open_to_input(t_nod *node, char *filename)
{
	int fd;

	fd = check_for_hdoc_priority(node->line);
	if (fd == -1)
	{
		fd = open(filename, O_RDONLY);
		if (fd == -1)
			error_msg_relative_to_file(filename, &node->launch);
	}
	else
	{
		if (node->fdi != 0)
			close(node->fdi);
		node->fdi = open(filename, O_RDONLY);
		if (node->fdi == -1)
			error_msg_relative_to_file(filename, &node->launch);
	}
}

/* red can be single or double, and red_io will give the reader and the code
 * a hint as to what the redirection is redirecting, input or output.*/
void	do_redirection(t_nod *node, char **aux, int red, int red_io)
{
	char	*filename;
	int		displacement;

	place_str_pointers(aux, &node->line_aux, &node->line, red);
	filename = filename_gatherer(&node->line, &node->launch);
	if (node->launch == OK)
	{
		if (red == DOUBLE && red_io == OUTPUT)
			open_on_append_mode(node, filename);
		else if (red == SINGLE && red_io == OUTPUT)
			open_on_truncate_mode(node, filename);
		else
			open_to_input(node, filename);
		free(filename);
	}
	displacement = node->line - node->line_save;
	displacement -= (node->line_aux - node->line_aux_save);
	move_str_pointers(&node->line_aux, aux, displacement);
	//printf("aux: [%s]\n", *aux);
	//printf("node->line: [%s]\n", node->line);
	//printf("node->line_save: [%s]\n", node->line_save);
	//printf("node->line_aux_save: [%s]\n", node->line_aux_save);
	//printf("node->line_aux [%s]\n", node->line_aux); 
}

void	redirection_checker(t_nod *node)
{
	char	*aux;

	aux = node->line_aux;
	while (*aux && node->launch == OK)
	{
		if (*aux == '>' || *aux == '<')
		{
			if (*(aux + 1) == '>')
			{
				aux = aux + 2;
				do_redirection(node, &aux, DOUBLE, OUTPUT);
			}
			else
			{
				if (*aux++ == '>')
					do_redirection(node, &aux, SINGLE, OUTPUT);
				else
					do_redirection(node, &aux, SINGLE, INPUT);
			}
		}
		else
			aux++;
	}
}

void	clean_hdoc_bar(t_nod *node)
{
	char *aux;

	aux = node->line_save;
	while (*aux)
	{
		if (*aux == '\\')
			*aux = ' ';
		aux++;
	}
	free(node->line_aux_save);
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
		clean_hdoc_bar(node);
		node = node->next;
		i--;
	}
}
