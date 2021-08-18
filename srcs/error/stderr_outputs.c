/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stderr_outputs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 18:29:54 by carce-bo          #+#    #+#             */
/*   Updated: 2021/08/18 19:19:15 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	multiline_error(int *q_mark_err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("unclosed commas were found on command\n", 2);
	*q_mark_err = 42;
}

void	parse_error_near(char *str, int	*q_mark_err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	write(2, str, 1);
	ft_putstr_fd("\'\n", 2);
	*q_mark_err = 258;
}

void	forbidden_char_found(char *str, int *q_mark_err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("found forbidden char: `", 2);
	write(2, str, 1);
	ft_putstr_fd("\'\n", 2);
	*q_mark_err = 42;
}

void	call_error(void)
{
	ft_putstr_fd("No such thing as minishell scripting...\n\n\n", 2);
	ft_putstr_fd("                                               ...yet\n", 2);
	exit(42);
}

void	command_not_found_error(char **cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("command not found\n", 2);
	exit(0);
}

void	error_msg_relative_to_file(char *file)
{
	char	*str;

	str = strerror(errno);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(0);
}

/*This is the error that is raised after execve fails. */
void	error_msg(void)
{
	char	*str;

	str = strerror(errno);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(0);
}
