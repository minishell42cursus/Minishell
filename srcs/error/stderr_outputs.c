/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stderr_outputs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 18:29:54 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/19 20:34:32 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ambiguous_redirect_error(char *name, int *launch)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("$", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	*launch = KO;
	update_q_mark_variable(1);
}

void	error_msg_relative_to_file(char *file, int *launch)
{
	char	*str;

	*launch = KO;
	str = strerror(errno);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	update_q_mark_variable(1);
}

/*This is the error that is raised after execve fails. */
void	error_msg(void)
{
	char	*str;

	str = strerror(errno);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(errno);
}
