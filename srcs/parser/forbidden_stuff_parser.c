#include "minishell.h"
/*
#include "stdlib.h"
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
void	fbdn_parser(char **str)
{
	char	*aux;

	aux = *str;
	while (*aux)
	{
		if (*aux == ')' || *aux == ')' || *aux == ';'
			|| *aux == '*' || (*aux == '\\') || *aux == '&')
			exit(0);//raise_invalid_char_error();
		aux++;
	}
}

char	*r_redirection_piece(char *str)
{
	str++;
	if (*str == '>')
	   str++;
	while (*str == ' ' && *str)
		str++;
	if (*str != '>' && *str != '<' && *str != '|' && *str)
		return (str);
	else
		exit(0); //raise_invalid_parse_error
}

char	*l_redirection_piece(char *str)
{
	str++;
	if (*str == '<')
	   str++;
	while (*str == ' ' && *str)
		str++;
	if (*str != '>' && *str != '<' && *str != '|' && *str)
		return (str);
	else
		exit(0); //raise_invalid_parse_error
}

char	*pipe_piece(char *str)
{
	str++;
	while (*str == ' ' && *str)
		str++;
	if (*str != '|' && *str)
		return (str);
	else
		exit(0); //raise_invalid_parse_error
}

void	redirection_pipe_parser(char **str)
{
	char	*aux;

	aux = *str;
	while (*aux == ' ')
		aux++;
	if (*aux == '|')
		exit(0);//raise_invalid_parse_error;
	while (*aux)
	{
		if (*aux == '>' || *aux == '<' || *aux == '|')
		{
			if (*aux == '>')
				aux = r_redirection_piece(aux);
			else if (*aux == '<')
				aux = l_redirection_piece(aux);
			else
				aux = pipe_piece(aux);
		}
		aux++;
	}
	printf("succesfully parsed!\n string: |%s|\n", *str);
}
/*
int	main()
{
	char	*str;

	str = ft_strdup("<< a >> l < b <<c >>lol  | < a | << l");
	redirection_pipe_parser(&str);
	return (0);
}*/
