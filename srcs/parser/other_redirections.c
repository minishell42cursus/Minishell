#include "minishell.h"

void	correctly_write_filename(char *line, char *aux, int len)
{
	while (len > 0)
	{
		if (*line != '*' && *line != '\\')
		{
			*aux++ = *line;
			len--;
		}
		*line++ = ' ';
	}
	*aux = '\0';
}

char	*get_var_name(char *str)
{
	int		len;
	char	*name;

	len = 0;
	while (ft_isalnum(++(*str)))
		len++;
	name = ft_substr(str, 0, len);
	return (name);
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
char	*add_length(char *str, int *len)
{
	char	*varname;
	char	*var_value;
	int		length_wo_expansion;

	varname = get_var_name(str);
	var_value = get_var_value(varname);
	length_wo_expansion = ft_strlen(varname) + 1;	
	free(varname);
	if (!var_value)
		*len = *len - length_wo_expansion;
	else
		*len = *len - length_wo_expansion + ft_strlen(var_value);
	str = str + ft_strlen(var_value);
	free(var_value);
	return (str);
}

void	add_envar_len(int *len, char *str)
{
	while (*str == ' ')
		str++;
	while (*str != ' ' && *str != '<' && *str != '>' && *str)
	{
		if (*str == '\\' || *str == '&')
			str = add_length(str, len);
		else
			str++;
	}
}

char	*filename_gatherer(char **line)
{
	char	*filename;
	int		len;

	len = string_length_bash(*line, OK);
	add_envar_len(&len, *line);
	printf("string after modifications(node->*line): [%s]\n", *line);
	filename = malloc(sizeof(char) * (len + 1));
	correctly_write_filename(*line, filename, len);
	return (filename);
}

void	double_right_red(t_nod *node, char **aux)
{
	char	*filename;

	place_str_pointers(aux, &node->line_aux, &node->line, 2);
	printf("LA LINEA FTER PLACE_STR_POINTERS:[%s]\n", node->line);
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
