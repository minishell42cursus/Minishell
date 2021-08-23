#include "minishell.h"

char	*ft_strdup_n_free(char *src)
{
	char	*output_str;
	int		i;

	output_str = (char *) malloc(sizeof (*src) * (ft_strlen(src) + 1));
	if (!output_str)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		output_str[i] = src[i];
		i++;
	}
	output_str[i] = '\0';
	free(src);
	return (output_str);
}

char	*ft_strjoin_n_free(char *s1, char *s2)
{
	char	*str;
	char	*aux_str;
	char	*aux_s1;
	char	*aux_s2;

	if (!s1)
	{
		str = ft_strdup_n_free(s2);
		return (str);
	}
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	aux_s1 = s1;
	aux_s2 = s2;
	aux_str = str;
	while (*aux_s1)
		*aux_str++ = *aux_s1++;
	while (*aux_s2)
		*aux_str++ = *aux_s2++;
	*aux_str = '\0';
	free(s1);
	free(s2);
	return (str);
}
