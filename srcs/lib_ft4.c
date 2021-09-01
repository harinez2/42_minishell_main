#include "main.h"

char	*ft_searchinstr(const char *s, int c)
{
	unsigned long long		i;

	if (!s)
		return (NULL);
	i = 0;
	while (1)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		else if (s[i] == '\0')
			break ;
		i++;
	}
	return (NULL);
}
