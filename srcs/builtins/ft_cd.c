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

char	*check_pwd(char *str, char **env, int opwd, int home)
{
	char	*s;

	s = NULL;
	if (!str)
	{
		if (home != -1)
			s = ft_strdup(env[home] + 5);
		else
			print_and_update("minishell: cd: HOME not set", 1); 
	}
	else if (ft_strncmp(str, "-", 2) == 0)
	{
		if (opwd != -1)
		{
			s = ft_strdup(env[opwd] + 7);
			print_and_update(env[opwd] + 7, 0);
		}
		else
			print_and_update("minishell: cd: OLDPWD not set", 1);
	}
	else
		s = ft_strdup(str);
	return (s);
}

char	**cd_env(char **env, int i[2])
{
	char	*pwd;
	char	*tmp;

	if (i[0] != -1)
	{
		pwd = ft_strjoin("OLD", env[i[0]]);
		tmp = getcwd(NULL, 0);
		pwd = ft_strjoin("PWD=", tmp);
		free(tmp);
		env[i[0]] = pwd;
	}
	return (env);
}

void	ft_cd(char *str, char **env)
{
	char	*s;
	int	i[2];

	i[0] = find_env(env, "ENV");
	i[1] = find_env(env, "OLDPWD");
	s = check_pwd(str, env, i[1], find_env(env, "HOME"));
	if (chdir(s) == -1)
		cd_error(s);
	else
	{
		env = cd_env(env, i);
		update_q_mark_variable(0);
	}
	free(s);
}
