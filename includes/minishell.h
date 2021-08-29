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
//# define MINISHELL	"\033[32m$🔥🔥>  \033[0m"
# define MINISHELL	"$🔥💀minihell💀🔥> "


# define OK		1
# define KO		0

// index value:
//	0 : echo
//	1 : pwd
//	2 : env
//	3 : cd
//	4 : export
//	5 : unset
//	6 : exit

typedef struct s_nod
{
	int				p_nbr;
	char			*line; // de top | cat -e < a, del segundo proceso: line = "cat -e < a"
	char			*line_aux;
	char			*line_save;
	char			*line_aux_save;
	int				fdi;
	int				fdo;
	char			**cmd; // esto contendría, por ejemplo: cmd[0] = cat, cmd[1] = -e, cmd[2] = hola ... etc
	int				btin;
	char			*hdoc_name;
	struct s_nod	*next;
}			t_nod;

typedef struct s_shell
{
	int	index;
	char	*rl;
	char	*parse_rl;
	char	*rl_tofree;
	char	*rl_aux;
	char	ac;
	char	**av;
	char	**env;
	int		fdi;
	int		fdo;
	int		n_proc;
	t_list	*lst_env;
	t_nod	*p_lst;
	int		q_mark_err;
}				t_shell;

// inicialise

t_shell	*init_megastruct(int ac, char **av, char **env);
t_nod	*create_pnode(char **aux, char **str, int *n_proc);

// errno_outputs

int		print_errno(void);
void	multiline_error(int *q_mark_err);
void	parse_error_near(char *str, int *q_mark_err);
void	forbidden_char_found(char *str, int *q_mark_err);
void	command_not_found(char **cmd);
void	error_msg_relative_to_file(char *file);
void	call_error(void);

// signals / signal

void	ft_signal_main(void);

// execute / run_command

char    **exec_built_in(t_shell *shell, char **env);

// builtins
int     ft_echo(char *argv[]);
void	ft_env(char **env);
void    ft_exit(t_shell *shell, char **env);
void    ft_pwd(void);
char	**ft_cd(char *str, char **env);
char    **ft_export(char **env, char **argv);
char    **ft_unset(char **env, char **av);
int		len_name(char *str);

// parser_fts

int		initial_parser(t_shell *shell);
int		comma_parser(char **str, int *q_mark_err);
int		redirection_pipe_parser(char **str, int *q_mark_err);
void	process_command_parsing(t_shell *shell);

// here_doc_related

void	heredoc_piece(t_shell *shell);
void	place_str_pointers(char **aux, char **str_blank, char **str_full);
char	*hdoc_filename(int reset);
char	*eof_gatherer(char **line);
void	unlink_all_heredocs(t_shell *shell);

// free  functions

void	free_process_list(t_shell *shell);
void	free_command(t_shell *shell);

//Get next line utils:

# define BUFFER_SIZE 100

char	*ft_strjoin_n_free(char *s1, char *s2);
int		get_next_line(int fd, char **line);
int		tablen(char **tab);
char	**tabdup(char **tab);

#endif
