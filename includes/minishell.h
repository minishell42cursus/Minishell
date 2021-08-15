#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <string.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"

# define BUILTINS	"echo:cd:pwd:export:unset:env:exit"

# define OK		1
# define KO		0

typedef struct s_shell
{
	char	*rl;
	char	*rl_tofree;
	char	ac;
	char	**av;
	char	**env;
	int		fdi;
	int		fdo;
	int		n_frk;
	t_list	*lst_env;
	char	**builtin;
}				t_shell;

typedef struct s_pnode
{
	int		p_nbr;
	char	*line; // de top | cat -e < a, del segundo proceso: line = "cat -e < a"
	int		fdi;
	int		fdo;
	char	**cmd; // esto contendría, por ejemplo: cmd[0] = cat, cmd[1] = -e, cmd[2] = hola ... etc
	int		btin;
}			t_pnode;

// inicialise

void	init_megastruct(t_shell	*shell, int ac, char **av, char **env);


// raiser_error

int		print_errno(void);

#endif
