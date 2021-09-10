/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:31:42 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/09 22:40:09 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_exit(t_shell *shell)
{
	rl_clear_history();
	free(shell);
	write(1, "exit\n", 6);
	exit(0);
}

int	initial_parser(t_shell *shell)
{
	if (!shell->rl)
		clean_exit(shell);
	shell->parse_rl = ft_strdup(shell->rl);
	shell->rl_tofree = shell->parse_rl;
	if (comma_parser(&shell->parse_rl, &shell->q_mark_err)
		|| redirection_pipe_parser(&shell->parse_rl, &shell->q_mark_err))
	{
		free(shell->rl_tofree);
		return (1);
	}
	return (0);
}
