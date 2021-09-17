#include "minishell.h"

int	check_export_arg(char *arg)
{
	if (ft_isvalid_env_start(*arg, Q_MARK_KO))
	{
		while (ft_isvalid_env_core(*arg))
			arg++;
		if (*arg == '=' || !*arg)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

int	parse_argument(char *arg)
{
	char	*name;
	char	*value;

	if (check_export_arg(arg))
	{
		name = get_var_name(arg);
		if (!*(arg + ft_strlen(name)))
		{
			free(name);
			return (NOTDEFINED);
		}
		value = check_env(name);
		free(name);
		if (!value)
			return (DEFINITION);
		else
		{
			free(value);
			return (REDEFINITION);
		}
	}
	else
		return (EXPORT_ERROR);
}

void	check_for_local_value(char *name, char **prev_value)
{
	char	*local_value;

	local_value = get_var_value(name, EXPORT_CALL);
	if (*local_value != '\\')
	{
		free(*prev_value);
		*prev_value = local_value;
	}
	else
		free(local_value);
}

void	add_to_global_env(char *name, char *value, int stat)
{
	int		i;
	char	*aux;
	char	**new_env;

	new_env = malloc(sizeof(char *) * ((int)ft_matrixlen(g_shell->env) + 2));
	i = 0;
	while (g_shell->env[i])
	{
		new_env[i] = ft_strdup(g_shell->env[i]);
		i++;
	}
	aux = ft_strjoin(name, "=");
	if (stat == NOTDEFINED)
		check_for_local_value(name, &value);
	new_env[i++] = ft_strjoin(aux, value);
	new_env[i] = NULL;
	free_four_ptrs(aux, name, value, g_shell->env);
	g_shell->env = new_env;
}

void	ft_export(char **argv)
{
	int		i;
	int		arg_type;
	char	*value;
	char	*name;

	i = 1;
	update_q_mark_variable(0);
	if (!argv[1])
		ft_env(1);
	while (argv[i])
	{
		arg_type = parse_argument(argv[i]);
		name = get_var_name(argv[i++]);
		if (arg_type != NOTDEFINED && arg_type != EXPORT_ERROR)
			value = ft_strdup(argv[i - 1] + ft_strlen(name) + 1);
		if (arg_type == DEFINITION)
			add_to_global_env(name, value, DEFINITION);
		else if (arg_type == REDEFINITION)
			overwrite_env_value(name, value);
		else if (arg_type == NOTDEFINED)
			add_to_global_env(name, ft_strdup("\\"), NOTDEFINED);
		else
			export_error(argv[i - 1], name);
	}
}
