#include "main.h"

void	expander_char_quote(char **text)
{
	char	*new;
	int		cnt;
	int		i;
	int		escape;
	int		single_quote;

	new = (char *)malloc(ft_strlen(*text) + 1);
	cnt = 0;
	i = 0;
	escape = 0;
	single_quote = 0;
	while ((*text)[cnt])
	{
		if ((*text)[cnt] == '\'')
			single_quote ^= 1;
		if (((*text)[cnt] == '\"' && escape == 0) || (*text)[cnt] == '\''
			|| (((*text)[cnt] == '\\' && single_quote == 0 && escape == 0)))
		{
			if ((*text)[cnt] == '\\')
				escape = 1;
			cnt ++;
			continue ;
		}
		new[i] = (*text)[cnt];
		printf("character: %c\nescape: %d\nsingle_quote: %d\n---------\n", (*text)[cnt], escape, single_quote);
		i ++;
		cnt ++;
		if (escape == 1)
			escape = 0;
	}
	new[i] = '\0';
	free(*text);
	(*text) = ft_strdup2(new, i);
	free(new);
}
