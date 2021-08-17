#include "minishell.h"

int	initial_parser(t_shell *shell)
{
	if (!shell->rl)
	{
		write(1, "exit\n", 6);
		exit(0);
	}
	shell->parse_rl = ft_strdup(shell->rl);
	shell->rl_tofree = shell->rl;
	if (comma_parser(&shell->parse_rl))
	{
		shell->q_mark_err = 42;
		return (1);
	}
	if (redirection_pipe_parser(&shell->parse_rl, &shell->q_mark_err))
		return (1);
	return (0);
}
