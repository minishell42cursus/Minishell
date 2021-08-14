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
}				t_shell;

typedef struct s_pnode
{
	int		p_nbr;
	char	*line; // de top | cat -e < a, del segundo proceso: line = "cat -e < a"
	int		fdi = 0;
	int		fdo = 1;
	char	**cmd; // esto contendría, por ejemplo: cmd[0] = cat, cmd[1] = -e, cmd[2] = hola ... etc
	int		btin;
}

#endif
