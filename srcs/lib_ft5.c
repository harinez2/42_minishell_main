#include "main.h"

void	remove_char_in_heap(char **s, int i)
{
	char	*left;
	char	*right;

	left = ft_strdup2(*s, i);
	right = ft_strdup2(&((*s)[i + 1]), ft_strlen(*s) - i);
	secure_free(*s);
	*s = ft_strjoin(left, right);
	secure_free(left);
	secure_free(right);
}
