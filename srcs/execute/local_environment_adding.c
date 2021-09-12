#include "minishell.h"

void	replace_value_on_local_env(t_var *nod, char *name, char *value)
{
	free(name);
	free(nod->value);
	nod->value = value;
}

t_var	*new_env_var(char *name, char *value)
{
	t_var	*nod;

	nod = malloc(sizeof(t_var));
	nod->name = name;
	nod->value = value;
	nod->next = NULL;
	return (nod);
}

void	add_to_local_env(char *name, char *value)
{
	t_var	*nod;
	t_var	**aux;

	nod = g_shell->envar;
	while (nod)
	{
		if (!ft_strncmp(nod->name, name, ft_maxlen(nod->name, name)))
		{
			replace_value_on_local_env(nod, name, value);
			break ;
		}
		if (nod->next == NULL)
			aux = &nod->next;
		nod = nod->next;
	}
	if (!nod)
	{
		nod = new_env_var(name, value);
		if (aux)
			(*aux) = nod;
		else
			g_shell->envar = nod;
	}
}

/* Function that will clear the local environment variable
 * declaration from the command matrix, resizing it correctly.
 * Example: [a="hello ls] will be just [ls] after assigning a.*/
static void	rebuild_cmd(char ***cmd)
{
	char	**aux;
	char	**new_cmd;
	int		i;

	new_cmd = malloc(sizeof(char *) * ft_matrixlen(*cmd));
	aux = *cmd;
	i = 1;
	while (aux[i])
	{
		new_cmd[i - 1] = ft_strdup(aux[i]);
		i++;
	}
	new_cmd[i - 1] = NULL;
	free_matrix(*cmd);
	*cmd = new_cmd;
}

int	check_if_def(char *str)
{
	if (!str)
		return (0);
	if (ft_isvalid_env_start(*str))
	{
		while (ft_isvalid_env_core(*str))
			str++;
		if (*str == '=')
			return (1);
	}
	return (0);
}

void	overwrite_env_value(char *name, char *value)
{
	char	*aux;
	int		i;

	i = 0;
	aux = ft_strjoin(name, "=");
	while (g_shell->env[i])
	{
		if (!ft_strncmp(g_shell->env[i], aux, ft_strlen(aux)))
			break ;
		i++;
	}
	free(g_shell->env[i]);
	g_shell->env[i] = ft_strjoin(aux, value);
	free(name);
	free(value);
	free(aux);
}

void	add_to_env(char *name, char *value)
{
	char	*prev_value;

	prev_value = check_env(name);
	if (!prev_value)
		add_to_local_env(name, value);
	else
		overwrite_env_value(name, value);
}

void	clear_envar_defs(char ***cmd)
{
	char	**aux;
	char	*aux2;
	char	*name;
	char	*value;

	aux = *cmd;
	aux2 = NULL;
	if (check_if_def(*aux) == OK)
	{
		aux2 = *aux;
		name = get_var_name(aux2);
		aux2 = aux2 + ft_strlen(name) + 1;
		value = ft_strdup(aux2);
		add_to_env(name, value);
		rebuild_cmd(cmd);
		clear_envar_defs(cmd);
	}
}
