#include "minishell.h"

// Laboratorio de pruebas:

void	add_variable_to_local_env(void)
{
	t_var	*nod;

	g_shell->envar = malloc(sizeof(t_var));
	g_shell->envar->name = ft_strdup("var1");
	g_shell->envar->value = ft_strdup("hey");
	nod = malloc(sizeof(t_var));
	nod->name = ft_strdup("lmaoo");
	nod->value = ft_strdup("42");
	nod->next = NULL;
	g_shell->envar->next = nod;
}

/* glitch: Si la variable se llama
 * hola y acaba en hola=, explota. Como ajuste
 * podriamos hacer que '=' no pudiese entrar dentro
 * de llas definiciones de las variables de entorno */
char	*check_env(char *name)
{
	char	**env;
	int		i;
	char	*aux;
	char	*value;

	env = g_shell->env;
	i = 0;
	while (env[i])
	{
		aux = ft_strjoin(name, "=");
		if (!ft_strncmp(env[i], aux, ft_strlen(aux)))
			break ;
		free(aux);
		i++;
	}
	if (!env[i])
		return (NULL);
	value = ft_strtrim(env[i], aux);
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
	return (NULL);
}

char	*get_var_name(char *str)
{
	int		len;
	char	*name;

	len = 0;
	while (ft_isalnum(str[len]))
		len++;
	name = ft_substr(str, 0, len);
	//printf("var name: [%s]\n", name); 
	return (name);
}

char	*get_var_value(char *name)
{
	char	*value;

	value = check_env(name);
	if (!value)
		value = check_local_env(name);
	if (!value)
		return (NULL);
	else
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
	if (!var_value)
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
		else
		{
			str++;
			i--;
		}
	}
	//printf("string before going out of length adder: [%s]\n", str);
	//printf("new length: [%i]\n", *len);
}

void	ambiguous_redirect_check(char *var_name, char *var_value, int *launch)
{
	char	*aux;

	aux = ft_strnstr(var_value, " ", ft_maxlen(var_value, " "));
	if (aux)
	{
		ambiguous_redirect_error(var_name, launch);
		free(var_name);
		free(var_value);
	}
}

void	do_expand_var(char **line, char **filename, int *len, char *var_value)
{
	int	i;

	i = 0;
	//printf("fourth layer: %p\n", filename);
	//printf("vaue of variable: [%s]\n", var_value);
	//printf("line before movement: [%s]\n", *line);
	*line = *line + 1;
	while (ft_isalnum((*line)[i]))
		i++;
	//printf("length of var: %i\n", i);
	*line = *line + i;
	//printf("line after movement: [%s]\n", *line);
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
	
	//printf("third layer: %p\n", filename);
	var_name = get_var_name((*line + 1));
	var_value = get_var_value(var_name);
	if (**line == '\\' && var_value)
		ambiguous_redirect_check(var_name, var_value, launch);
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
	printf("line before starting loop: [%s]\n", *line);
	//printf("its pointer: [%p], *[%p]\n", line, *line);
	while (*len > 0 && *launch == OK)
	{
		printf("line inside writing loop: [%s]\n", *line);
		//printf("its pointer: [%p], *[%p]\n", line, *line);
		//printf("filename inside writing loop: [%s]\n", filename);
		if (**line == '\\' || **line == '&')
		{
			printf("line before movement: [%s]\n", *line);
			printf("len before movement: %i\n", *len);
			expand_var_name(line, filename, len, launch);
			printf("line after movement: [%s]\n", *line);
			printf("len after movement: %i\n", *len);
		}
		else if (**line != '*' && **line != '\\' && **line != '&' && **line)
		{
			printf("line before second if movement: [%s]\n", *line);
			*((*filename)++) = *((*line)++);
			*len = *len - 1;
			printf("line after second if movement: [%s]\n", *line);
		}
		else
		{
			printf("line before being blanked: [%s]\n", *line);
			*((*line)++) = ' ';
			printf("line after being blanked: [%s]\n", *line);
		}
	}
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
	printf("initial length: %i\n", len);
	add_envar_len(&len, *line);
	printf("final length: %i\n", len);
	filename = malloc(sizeof(char) * (len + 1));
	aux = filename;
	//printf("first layer: %p\n", &filename);
	write_filename(line, &aux, &len, launch);
	printf("filename: [%s]\n", filename);
	return (filename);
}

void	double_right_red(t_nod *node, char **aux)
{
	char	*filename;

	place_str_pointers(aux, &node->line_aux, &node->line, 2);
	//printf("LA LINEA FTER PLACE_STR_POINTERS:[%s]\n", node->line);
	filename = filename_gatherer(&node->line, &node->launch);
	/*printf("filename: [%s]\n", filename);
	printf("node->line_aux: [%s]\n", node->line_aux);
	printf("node->line: [%s]\n", node->line);*/
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