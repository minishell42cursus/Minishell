#include "minishell.h"

void	ft_echo(char *argv[])
{
        int             i;
        bool    flag;

        flag = 0;
        i = 0;
	if (ft_strcmp(argv[0], "echo") == 0 && ft_strlen(*argv) == 4)
	{
                ft_putstr_fd("\n", STDOUT_FILENO);
		return ;
	}
        while (argv[++i] && !ft_strncmp(argv[i], "-n", 3))
                flag = 1;
	while (argv[i])
		ft_putstr_fd(argv[i++], STDOUT_FILENO);
	if (flag == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
