/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:59:57 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/17 15:49:54 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*construct_prompt(void)
{
	char	*cwd;
	char	*pmt;
	char	*aux;
	char	*aux2;

	cwd = getcwd(NULL, 0);
	aux = ft_strjoin(PROMPT_START, cwd); 
	aux2 = ft_strjoin(BLUE_BOLD, aux);
	free_two_ptrs(aux, cwd);
	aux = ft_strjoin(aux2, GREEN_BOLD);
	free(aux2);
	aux2 = ft_strjoin(aux, " > ");
	pmt = ft_strjoin(aux2, UNSET);
	free_two_ptrs(aux, aux2);
	return (pmt);
}

static const char	*get_prompt(void)
{
	char	*pmt;

	pmt = construct_prompt();
	if (!g_shell->pmt)
		g_shell->pmt = pmt;
	else
	{
		if (!ft_strncmp(g_shell->pmt, pmt, ft_maxlen(g_shell->pmt, pmt)))
			free(pmt);
		else
		{
			free(g_shell->pmt);
			g_shell->pmt = pmt;
		}
	}
	return ((const char *)g_shell->pmt);
}

int	main(int argc, char *argv[], char *env[])
{
	t_shell		*shell;

	if (argc != 1)
		call_error();
	shell = init_megastruct(argc, argv, env);
	while (1)
	{
		ft_signal_main();
		g_shell->rl = readline(get_prompt());
		if (!initial_parser())
		{
			process_command_parsing();
			heredoc_piece();
			other_io_redirections();
			gather_process_arguments();
			launch_processes();
			unlink_all_heredocs(shell);
			free_process_list(shell);
		}
	}
	rl_clear_history();
	return (0);
}
