#include "minishell.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*str1;
	char	*str2;

	str1 = ft_strjoin(s1, "/");
	str2 = ft_strjoin(str1, s2);
	free(str1);
	return (str2);
}

char	*check_pwd(char *str, int opwd, int home)
{
	char	*s;

	s = NULL;
	if (!str)
	{
		if (home != -1)
			s = ft_strdup(g_shell->env[home] + 5);
		else
			printf("minishell: %s: %s\n", "cd", "HOME not set");
	}
	else if (ft_strncmp(str, "-", 2) == 0)
	{
		if (opwd != -1)
		{
			s = ft_strdup(g_shell->env[opwd] + 7);
			printf("%s\n", g_shell->env[opwd] + 7);
		}
		else
			printf("minishell: %s: %s\n", "cd", "OLDPWD not set");
	}
	else
		s = ft_strdup(str);
	return (s);
}

void	cd_env(int i[2])
{
	char	*pwd;
	char	*tmp;

	if (i[0] != -1)
	{
		pwd = ft_strjoin("OLD", g_shell->env[i[0]]);
		//env = ad_arg_exp(env, pwd);
		tmp = getcwd(NULL, 0);
		pwd = ft_strjoin("PWD=", tmp);
		free(tmp);
		g_shell->env[i[0]] = pwd;
	}
}

void	ft_cd(char *str)
{
	char	*s;
	int	i[2];

<<<<<<< HEAD
	i[0] = find_env("ENV");
	i[1] = find_env("OLDPWD");
	s = check_pwd(str, i[1], find_env("HOME"));
	/*if (!s)
		return (env);*/
=======
	i[0] = find_env(env, "ENV");
	i[1] = find_env(env, "OLDPWD");
	s = check_pwd(str, env, i[1], find_env(env, "HOME"));
>>>>>>> master
	if (chdir(s) == -1)
		printf("minishell: cd: %s: %s\n", s, "No such file or directory");
	else
		cd_env(i);
	free(s);
}
