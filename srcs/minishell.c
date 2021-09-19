/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:59:57 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/19 18:58:31 by carce-bo         ###   ########.fr       */
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
	if (g_shell->q_mark_err == 0)
		aux = ft_strjoin(aux2, GREEN_BOLD);
	else
		aux = ft_strjoin(aux2, RED_BOLD);
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

void	fprintf_matrix_pointers(char **mat)
{
	int	i;

	i = 0;
	if (!mat)
		fprintf(stderr, "matrix does not exist already/yet\n");
	else
	{	
		fprintf(stderr, "mat pointer: %p\n", mat);
		while (mat[i])
		{
			fprintf(stderr, "mat[%i] = %p\n", i, mat[i]);
			i++;
		}
		fprintf(stderr, "mat[%i] = %p\n", i, mat[i]);
	}
}

void	fprintf_process_node_list(t_nod *node)
{
	if (!node)
		fprintf(stderr, "the list does not exist yet\n");
	else
	{
		while (node)
		{
			fprintf(stderr, "node pointer: %p\n", node);
			fprintf(stderr, "node->line: %p\n", node->line);
			fprintf(stderr, "node->line_aux: %p\n", node->line_aux);
			fprintf(stderr, "node->line_save: %p\n", node->line_save);
			fprintf(stderr, "node->line_aux_save: %p\n", node->line_aux_save);
			fprintf(stderr, "node->cmd:\n");
			fprintf_matrix_pointers(node->cmd);
			fprintf(stderr, "hdoc_name: %p\n", node->hdoc_name);
			fprintf(stderr, "node->next: %p\n\n", node->next);
			node = node->next;
		}
	}
}


void	fprintf_local_environment_node_list(t_var *node)
{
	if (!node)
		fprintf(stderr, "the list does not exist yet\n");
	else
	{
		while (node)
		{
			fprintf(stderr, "node pointer: %p\n", node);
			fprintf(stderr, "node->name: %p\n", node->name);
			fprintf(stderr, "node->value: %p\n", node->value);
			fprintf(stderr, "node->next: %p\n", node->next);
			node = node->next;
		}
	}
}

void	print_all_pointers_in_structs(void)
{
	fprintf(stderr, "g_shell->rl: %p\n", g_shell->rl);
	fprintf(stderr, "g_shell->parse_rl: %p\n", g_shell->parse_rl);
	fprintf(stderr, "g_shell->rl_tofree: %p\n", g_shell->rl_tofree);
	fprintf(stderr, "g_shell->rl_aux: %p\n", g_shell->rl_aux);
	fprintf(stderr, "\ng_shell->env:\n");
	fprintf_matrix_pointers(g_shell->env);
	fprintf(stderr, "\n\nprocess node list:\n\n");
	fprintf_process_node_list(g_shell->p_lst);
	fprintf(stderr, "\n\nlocal environment variables list:\n\n");
	fprintf_local_environment_node_list(g_shell->envar);
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
			//system("leaks minishell");
			gather_process_arguments();
			launch_processes();
			print_all_pointers_in_structs();
			unlink_all_heredocs(shell);
			free_process_list(shell);
		}
	}
	rl_clear_history();
	return (0);
}
