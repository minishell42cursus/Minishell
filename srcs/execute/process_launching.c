#include "minishell.h"

/* Function that comes in VERY handy when working with pipes. It
 * duplicates the STDIN fildescriptor to some new_in, and does the
 * same for STDOUT, then proceeds to close these new_in/new_out fd's,
 * since they are now accessible through 0 and 1, respectively.*/
void	dup_stdin_stdout_and_close(int new_in, int new_out)
{
	if (dup2(new_in, 0) == -1)
		error_msg();
	close(new_in);
	if (dup2(new_out, 1) == -1)
		error_msg();
	close(new_out);
}

void	call_execve(t_nod *node)
{
	char	*path;

	path = find_exec_path(node->cmd[0]);


void	launch_from_father(t_nod *node)
{
	pid_t	pid;

	if (node->launch == OK)
	{
		if (ft_isbuiltin(node->cmd))
			truly_launch_from_father(node);
		else
		{
			pid = fork();
			if (pid == 0)
			{




void	launch_processes(void)
{
	int		i;
	t_nod	*node;

	i = g_shell->n_proc;
	node = g_shell->p_lst;
	if (i == 1)
		launch_from_father(node);
	else
		launch_from_childs(node, i);
}
