#include "minishell.h"

int	*copy_new_pipe_into_old(int p[2])
{
	int	*output;

	output = malloc(sizeof(int) * 2);
	output[0] = p[0];
	output[1] = p[1];
	return (output);
}

void	subst_fd_for_pipe(int *node_fd, int new_fd, int fd)
{
	if (fd == IN)
	{
		if (*node_fd == 0)
			*node_fd = new_fd;
		else
			close(new_fd);
	}
	else if (fd == OUT)
	{
		if (*node_fd == 1)
			*node_fd = new_fd;
		else
			close(new_fd);
	}
}

void	wait_and_get_q_mark(void)
{
	int	stat;

	waitpid(g_shell->pid, &stat, 0);
	if (g_shell->assign_error == OK)
	{
		if (WIFEXITED(stat))
			update_q_mark_variable(WEXITSTATUS(stat));
		else if (WIFSIGNALED(stat))
			update_q_mark_variable(WTERMSIG(stat) + 128);
		else if (WIFSTOPPED(stat))
			update_q_mark_variable(WSTOPSIG(stat));
	}
	g_shell->assign_error = OK;
}

void	launch_from_childs(t_nod *node, int i)
{
	int		new_pip[2];
	int		*old_pip;

	while (i > 0)
	{
		pipe(new_pip);
		g_shell->pid = fork();
		if (g_shell->pid == 0)
		{
			close(new_pip[0]);
			if (node->launch == OK)
			{
				clear_envar_defs(&node->cmd);
				open_hdoc_fd(node);
				//printf("proceso numero %i:\n", node->p_nbr);
				if (node->p_nbr != 1)
					subst_fd_for_pipe(&node->fdi, old_pip[0], IN);
				//printf("number of process: %i\n", node->p_nbr);
				//printf("number of processes: %i\n", g_shell->n_proc);
				if (node->p_nbr != g_shell->n_proc)
					subst_fd_for_pipe(&node->fdo, new_pip[1], OUT);
				else
					close(new_pip[1]);
				if (node->cmd[0])
				{
					if (ft_isbuiltin(node->cmd))
					{
						dup_stdin_stdout_and_close(node->fdi, node->fdo);
						exec_builtin(node->cmd, CHILD);
					}
					else
						call_execve(node);
				}
			}
			else
				exit(g_shell->q_mark_err);
		}
		else
		{
			ft_signal_main();
			close(new_pip[1]);
			if (node->p_nbr != 1)
				close(old_pip[0]);
			if (node->p_nbr == g_shell->n_proc)
			{
				wait_and_get_q_mark();
				close(new_pip[0]);
			}
			else
				old_pip = copy_new_pipe_into_old(new_pip);
			close_all_fds(node);
		}
		node = node->next;
		i--;
	}
	//write(2, "\n\nI came out of the buclesito\n\n", ft_strlen("\n\nI came out of the busclesito\n\n"));
	g_shell->status = ON_READ;
}
