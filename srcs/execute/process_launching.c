#include "minishell.h"

char	**clone_environment(char **env)
{
	char	**out;
	int		i;

	i = 0;
	while (env[i])
		i++;
	out = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		out[i] = ft_strdup(env[i]);
		i++;
	}
	out[i] = NULL;
	return (out);
}

/* Function that comes in VERY handy when working with pipes. It
 * duplicates the STDIN fildescriptor to some new_in, and does the
 * same for STDOUT, then proceeds to close these new_in/new_out fd's,
 * since they are now accessible through 0 and 1, respectively.*/
void	dup_stdin_stdout_and_close(int new_in, int new_out)
{
	if (new_in != 0)
	{
		if (dup2(new_in, 0) == -1)
			error_msg();
		close(new_in);
	}
	if (new_out != 1)
	{
		if (dup2(new_out, 1) == -1)
			error_msg();
		close(new_out);
	}
}

void	call_execve(t_nod *node)
{
	char	*path;
	char	**env;

	path = find_exec_path(node->cmd[0]);
	env = clone_environment(g_shell->env);
	if (execve(path, node->cmd, env) == -1)
		error_msg();
}

void	truly_launch_from_father(t_nod *node)
{
	int		fdi;
	int		fdo;

	fdi = dup(0);
	fdo = dup(1);
	dup_stdin_stdout_and_close(node->fdi, node->fdo);	
	ft_isrun(node->cmd);
	dup_stdin_stdout_and_close(fdi, fdo);
}

void	launch_from_fork(t_nod *node)
{
	int		stat;
	pid_t	pid;

	g_shell->status = ON_EXE;
	pid = fork();
	if (pid == 0)
	{
		dup_stdin_stdout_and_close(node->fdi, node->fdo);
		call_execve(node);
	}
	else
	{
		waitpid(pid, &stat, 0);
	}
}

void	launch_builtins_from_father(t_nod *node)
{
	//int	i = 0;

	if (node->launch == OK)
	{
		clear_envar_defs(&node->cmd);
		/*while (node->cmd[i])
		{
			printf("node->cmd[%i]: [%s]\n", i, node->cmd[i]);
			i++;
		}*/
		if (node->cmd[0])
		{
			if (ft_isbuiltin(node->cmd))
				truly_launch_from_father(node);
			else
				launch_from_fork(node);
		}
	}
}

void	launch_processes(void)
{
	int		i;
	t_nod	*node;

	i = g_shell->n_proc;
	node = g_shell->p_lst;
	if (i == 1)
		launch_builtins_from_father(node);
	else
		;
		//launch_from_childs(node, i);
}
