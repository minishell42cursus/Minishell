#include "minishell.h"

int	print_errno(void)
{
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 2);
	return (1);
}
