/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 23:53:29 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/16 17:11:03 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal_cltr_c(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_signal_kill(int sig)
{
	(void)sig;
	kill(g_shell->pid, SIGKILL);
	write(1, "\n", 1);
	update_q_mark_variable(1);
	g_shell->assign_error = KO;
}

void	ft_signal_kill_bar(int sig)
{
	(void)sig;
	kill(g_shell->pid, SIGKILL);
	write(1, "Quit: 3\n", 8);
	update_q_mark_variable(131);
	g_shell->assign_error = KO;
}

void	ft_signal_stop_all_process_launch(int sig)
{
	t_nod	*node;
	int		i;

	(void)sig;
	node = g_shell->p_lst;
	i  = g_shell->n_proc;
	while (i > 0)
	{
		node->launch = KO;
		node = node->next;
		i--;
	}
	update_q_mark_variable(1);
	g_shell->assign_error = KO;
}

void	ft_exit_child(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(0);
}

/*Fucntion that handles signals, on the three possible cases I can 
 * come up with. First is ON_READ, which is the default state of the shell.
 * Then theres ON_HDOC, which is the status in which the shell is when it is 
 * both reading input from stdin and writing it on an hdoc. The final status
 * is ON_EXE, which is the one that the shell is while commands are
 * being executed.*/ 
void	ft_signal_main(void)
{
	int	stat;

	if (g_shell->status == ON_READ)
	{
		signal(SIGTERM, SIG_IGN);
		signal(SIGINT, ft_signal_cltr_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (g_shell->status == ON_HDOC)
	{
		if (g_shell->pid != 0)
			signal(SIGINT, ft_signal_stop_all_process_launch);
		else
			signal(SIGINT, ft_exit_child);
		signal(SIGTERM, SIG_IGN);
		waitpid(g_shell->pid, &stat, 0);
	}
	else
	{
		signal(SIGTERM, SIG_IGN);
		signal(SIGINT, ft_signal_kill);
		signal(SIGQUIT, ft_signal_kill_bar);
	}
}
