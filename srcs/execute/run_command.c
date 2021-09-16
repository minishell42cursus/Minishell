#include "minishell.h"

int     ft_isbuiltin(char **args)
{
        if (ft_strlen(args[0]) == 3 && !ft_strncmp(args[0], "pwd", 3))
                return (1);
        else if (ft_strlen(args[0]) == 2 && !ft_strncmp(args[0], "cd", 2))
                return (1);
        else if (ft_strlen(args[0]) == 4 && !ft_strncmp(args[0], "echo", 4))
                return (1);
        else if (ft_strlen(args[0]) == 3 && !ft_strncmp(args[0], "env", 3))
                return (1);
        else if (ft_strlen(args[0]) == 6 && !ft_strncmp(args[0], "export", 6))
                return (1);
        else if (ft_strlen(args[0]) == 5 && !ft_strncmp(args[0], "unset", 5))
                return (1);
        else if (ft_strlen(args[0]) == 4 && !ft_strncmp(args[0], "exit", 4))
                return (1);
        else if (ft_strlen(args[0]) == 5 && !ft_strncmp(args[0], "clear", 5))
                return (1);
        else
                return (0);
}

void    ft_isrun(char **args)
{
        if (!args)
                return ;
        if (ft_strlen(args[0]) == 3 && !ft_strncmp(args[0], "pwd", 3))
                ft_pwd();
        else if (ft_strlen(args[0]) == 4 && !ft_strncmp(args[0], "echo", 4))
                ft_echo(args);
        else if (ft_strlen(args[0]) == 6 && !ft_strncmp(args[0], "export", 6))
                ft_export(args);
        else if (ft_strlen(args[0]) == 3 && !ft_strncmp(args[0], "env", 3))
                ft_env(0);
        else if (ft_strlen(args[0]) == 4 && !ft_strncmp(args[0], "exit", 4))
                ft_exit();
        /*else if (ft_strlen(args[0]) == 2 && !ft_strncmp(args[0], "cd", 2))
                ft_cd(args[1], g_shell->env);*/
        /*else if (ft_strlen(args[0]) == 5 && !ft_strncmp(args[0], "unset", 5))
                ft_unset(args);*/
}

