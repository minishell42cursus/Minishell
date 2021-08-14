#include "../../includes/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
}

int	print_errno(void)
{
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 2);
	return (1);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	void	*aux;
	size_t	len;

	len = count * size;
	ptr = malloc(len);
	if (!ptr)
		return (NULL);
	aux = ptr;
	while (len-- > 0)
		*(unsigned char *)aux++ = '\0';
	return (ptr);
}

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
