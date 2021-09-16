#include "minishell.h"

int	check_export_arg(char *arg)
{
	if (ft_isvalid_env_start(*arg, KO))
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
			return (NODEFINED);
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

void	add_to_global_env(char *name, char *value)
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
	new_env[i++] = ft_strjoin(aux, value);
	new_env[i] = NULL;
	free(aux);
	free_matrix(g_shell->env);
	free(name);
	free(value);
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
		if (arg_type != NODEFINED && arg_type != EXPORT_ERROR)
			value = ft_strdup(argv[i - 1] + ft_strlen(name) + 1);
		if (arg_type == DEFINITION)
			add_to_global_env(name, value);
		else if (arg_type == REDEFINITION)
			overwrite_env_value(name, value);
		else if (arg_type == NODEFINED)
			add_to_global_env(name, ft_strdup("\\"));
		else
			export_error(argv[i - 1], name);
	}
}
