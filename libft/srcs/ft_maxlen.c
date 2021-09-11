#include "libft.h"

size_t	ft_maxlen(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 >= len2)
		return (len1);
	else
		return (len2);
}
