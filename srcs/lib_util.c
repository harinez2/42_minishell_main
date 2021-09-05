#include "main.h"

void	putstr_stderr(char *s)
{
	write(2, s, ft_strlen(s));
}

void	copy_array(t_env *to[], t_env *from[], int len, int offset_to)
{
	int		i;

	i = 0;
	while (i < len)
	{
		to[offset_to + i] = from[i];
		i++;
	}
}

void	secure_free(void *p)
{
	if (p != NULL)
	{
		free(p);
		p = NULL;
	}
}
