#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = ft_calloc(4096, 1);
	if (getcwd(pwd, 4096))
	{
		ft_putstr_fd(pwd, 1);
		free(pwd);
		write(1, "\n", 1);
		return (0);
	}
	else
	{
		print_errno();
		free(pwd);
		return (1);
	}
}
/*
int	main(int argc, char *argv[])
{	
	int	value;

	value = ft_pwd();
	printf("\n\n\n\n%d%d%s", value, argc, *argv);
}*/
