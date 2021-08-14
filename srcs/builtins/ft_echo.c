#include "../../includes/minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, s++, 1);
	}
}

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

int	main(int argc, char *argv[])
{
	int	value;

	(void)argc;
	value = ft_echo(argv);
	printf("%d", value);
	return (1);
}
