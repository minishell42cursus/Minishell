#include "minishell.h"
/*#include "stdlib.h"
#include "stdio.h"
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}
char	*ft_strdup(const char *src)
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
	return (output_str);
}*/
/* Function that is called whenever a \" is found inside a str, outside
 * a \' string. This is extremely important, since \' is silenced by \" and
 * viceversa */
char	*d_comma_str_parser(char *str)
{
	str++;
	while (*str != '\"' && *str)
		*str++ = ' ';
	if (!*str)
		exit(0); //multiline_error();
	else
		return (str);
	return (str);
}

char	*s_comma_str_parser(char *str)
{
	str++;
	while (*str != '\'' && *str)
		*str++ = ' ';
	if (!*str)
		exit(0);//multiline_error();
	else
		return (str);
	return (str);
}

/* The string that commes in here should be the one duplicated
 * from the readline output. It will be formatted in such a way
 * anything between a correct string will be turned into spaces, 
 * so it can correctly work as bash process strings:
 * in: cat a ">> b << lol <<<<<<< >>>>>>>>>>>>>>>>>>"
 * parsed: cat a "                                    "
 * so i dont raise a parse error from the <<< or >>>.*/
void	comma_parser(char **str)
{
	char	*aux;

	aux = *str;
	while (*aux)
	{
		if (*aux == '\"' || *aux == '\'')
		{
			if (*aux == '\"')
				aux = d_comma_str_parser(aux);
			else
				aux = s_comma_str_parser(aux);
		}
		aux++;
	}
	printf("succesfully_parsed!\nstring: |%s|\n", *str);
}
/*
int main()
{
	char *str;

	str = ft_strdup("\'\'\'\'\'\'\"\"\"\" \' \"lol\"");
	comma_parser(&str);
	return (0);
}*/
