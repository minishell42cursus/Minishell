#include "../../includes/minishell.h"

int	ft_echo(char *argv[])
{
	int	i;
	int	flag;

	i = 1;
	flag = 1;
	if (argv[1])
	{
		if (ft_strcmp(argv[1], "-n") == 0)
			flag = 0;
		while (argv[i])
		{
			if (ft_strcmp(argv[i], "-n") != 0)
			{
				ft_putstr_fd(argv[i], 1);
				if (argv[i + 1] && ft_strlen(argv[i + 1]))
					write(1, " ", 1);
			}
			i++;
		}
	}
	if (flag)
		write(1, "\n", 1);
	return (0);
}
/*
int	main(int argc, char *argv[])
{
	int	value;

	(void)argc;
	value = ft_echo(argv);
	printf("%d", value);
	return (1);
}
*/
