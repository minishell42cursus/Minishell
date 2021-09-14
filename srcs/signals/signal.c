/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 23:53:29 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/14 20:04:04 by carce-bo         ###   ########.fr       */
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

/*Fucntion that handles signals, on the three possible cases I can 
 * come up with. First is ON_READ, which is the default state of the shell.
 * Then theres ON_HDOC, which is the status in which the shell is when it is 
 * both reading input from stdin and writing it on an hdoc. The final status
 * is ON_EXE, which is the one that the shell is while commands are
 * being executed.*/ 
void	ft_signal_main(void)
{
	// DE MOMENTO ESTAS SEÑALES SON TODAS IGUALES BUT YOU GET THE DRILL.
	// 3 SITUACIONES DISTINTAS PARA 3 SEÑALES DISTINTAS. 
	if (g_shell->status == ON_READ)
	{
		signal(SIGTERM, SIG_IGN);
		signal(SIGINT, ft_signal_cltr_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (g_shell->status == ON_HDOC)
	{
		signal(SIGTERM, SIG_IGN);
		signal(SIGINT, ft_signal_cltr_c);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGTERM, SIG_IGN);
		signal(SIGINT, ft_signal_cltr_c);
		signal(SIGQUIT, SIG_IGN);
	}	
}
