#include "minishell.h"

void	update_q_mark_variable(int new_value)
{
	g_shell->q_mark_err = new_value;
	add_to_local_env(ft_strdup("?"), ft_itoa(new_value));
}

void	print_and_update(char *str, int value)
{
	if (value == 0)
	{
		ft_putstr_fd(str, 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		ft_putstr_fd(str, 1);
		ft_putstr_fd("\n", 1);
	}
	update_q_mark_variable(value);
}
