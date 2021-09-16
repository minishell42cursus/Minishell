#include "minishell.h"

void	ft_putstr_space(char *argv[])
{
	int	cont;
	int	j;

	cont = 0;
	while (argv[cont])
		cont++;
	j = 0;
	if (j < cont)
		ft_putstr_fd(" ", STDOUT_FILENO);
}

void	ft_echo(char *argv[])
{
	int		i;
	bool	flag;
	
	flag = 0;
	i = 0;
	if (!argv[1])
	{
		print_and_update("\0", 0);
		return ;
	}
	while (argv[++i] && !ft_strncmp(argv[i], "-n", ft_maxlen(argv[i], "-n")))
		flag = 1;
	while (argv[i])
	{
		ft_putstr_fd(argv[i++], STDOUT_FILENO);
		ft_putstr_space(argv);
	}
	if (flag == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	update_q_mark_variable(0);
}
