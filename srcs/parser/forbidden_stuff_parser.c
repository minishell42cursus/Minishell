#include "minishell.h"

void	fbdn_parser(char **aux)
{
	char	*aux;

	aux = *aux;
	while (*aux)
	{
		if (*aux == ')' || *aux == ')' || *aux == ';'
			|| *aux == '*' || *aux == '\\')
			//raise_error();
		aux++;
	}
}
