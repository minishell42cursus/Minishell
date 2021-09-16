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
# include <limits.h>

# define BUILTINS	"echo:cd:pwd:export:unset:env:exit"
# define MINISHELL	"$🔥💀minihell💀🔥> "
# define PATH_TO_TMP	"/tmp/"


// General macros

# define OK			1
# define KO			0

// Redirection macros

# define DOUBLE 	2
# define SINGLE		1
# define OUTPUT		1
# define INPUT		0

// Hdoc_utils_macros

# define START		0
# define END		1

// parse macros

# define ARGUMENT	0
# define FULL_LINE	1

// signal macros

# define ON_READ		0
# define ON_HDOC		1
# define ON_EXE			2

// Export macros

# define NODEFINED		0
# define DEFINITION		1
# define REDEFINITION	2
# define EXPORT_ERROR	3

/*Process node structure*/
typedef struct s_nod
{
	int				p_nbr;
	char			*line;
	char			*line_aux;
	char			*line_save;
	char			*line_aux_save;
	int				fdi;
	int				fdo;
	char			**cmd;
	int				btin;
	char			*hdoc_name;
	int				n_hdoc;
	int				launch;
	struct s_nod	*next;
}					t_nod;

/*Environment variable struct*/
typedef struct	s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
}					t_var;

/*General shell struct*/
typedef struct s_shell
{
	int		index;
	char	*rl;
	char	*parse_rl;
	char	*rl_tofree;
	char	*rl_aux;
	char	ac;
	char	**env;
	int		fdi;
	int		fdo;
	int		n_proc;
	t_nod	*p_lst;
	int		q_mark_err;
	t_var	*envar;
	int		status;
	int		assign_error;
	pid_t	pid;
}				t_shell;

t_shell	*g_shell;

// inicialise

t_shell	*init_megastruct(int ac, char **av, char **env);
t_nod	*create_pnode(char **aux, char **str, int *n_proc);
t_var	*new_env_var(char *name, char *value);

// errno_outputs

int		print_errno(void);
void	multiline_error(int *q_mark_err);
void	parse_error_near(char *str, int *q_mark_err);
void	forbidden_char_found(char *str, int *q_mark_err);
void	command_not_found_error(char *cmd);
void	error_msg_relative_to_file(char *file, int *launch);
void	call_error(void);
void	ambiguous_redirect_error(char *name, int *launch);
void	error_msg(void);
void	export_error(char *arg, char *name);
void	cd_error(char *path);
void	exit_error(char *arg, int type);
void	unset_error(char *arg);

// $? utils

void	update_q_mark_variable(int new_value);
void	print_and_update(char *str, int new_value);

// signals / signal

void	ft_signal_main(void);

// execute / run_command

int     ft_isbuiltin(char **args);
void    ft_isrun(char **args);
void	clear_envar_defs(char ***cmd);
char	**clone_environment(char **env);
char	*find_exec_path(char *cmd);
void	launch_processes(void);

// builtins

void	ft_echo(char *argv[]);
void	ft_env(int mode);
void	ft_exit(char **args);
void	ft_pwd(void);
void	ft_cd(char *str, char **env);
void	ft_export(char **argv);
void	ft_unset(char **av);
int		len_name(char *str);
char	**ad_arg(char **env, char *str);
int		find_env(char **env, char *word);

// error control parser fts

int		initial_parser(void);
int		comma_parser(char **str, int *q_mark_err);
int		redirection_pipe_parser(char **str, int *q_mark_err);
void	process_command_parsing(void);

// redirection related

void	heredoc_piece(void);
char	*hdoc_filename(int reset);
char	*eof_gatherer(char **line, int *n_hdoc);
void	unlink_all_heredocs(t_shell *shell);
void	other_io_redirections(void);

// command argument gathering related

void	gather_process_arguments(void);
void	add_envar_len(int *len, char *str, int full_line);
void	write_str_w_envar(char **line, char **fname, int *len, int *launch);

// STRING PRESTIDIGITATION

void	place_str_pointers(char **aux, char **str_blank, char **str_full, int i);
void	edit_string(char **str, int *i, int envar);
int		string_length_bash(char *str, int envar);

// free  functions

void	free_process_list(t_shell *shell);
void	free_command(t_shell *shell);
void	free_matrix(char **matrix);

// env search related functions

char	*get_var_name(char *str);
char	*get_var_value(char *name);
int		ft_isvalid_env_start(char a, int consider_q_mark_err);
int		ft_isvalid_env_core(char a);
void	add_to_local_env(char *name, char *value);
int		check_if_def(char *str);
char	*check_env(char *name);
void	overwrite_env_value(char *name, char *value);

//Get next line utils:

# define BUFFER_SIZE 100

char	*ft_strjoin_n_free(char *s1, char *s2);
int		get_next_line(int fd, char **line);
int		tablen(char **tab);
char	**tabdup(char **tab);

#endif
