#include "main.h"

void	expander_char_quote(char **text)
{
	char	*new;
	int		cnt;
	int		i;
	int		escape;
	int		single_quote;

	new = (char *)malloc(ft_strlen(*text));
	cnt = 0;
	i = 0;
	escape = 0;
	single_quote = 0;
	while ((*text)[cnt])
	{
		if ((*text)[cnt] == '\'')
		{
			single_quote ^= 1;
			cnt ++;
			continue ;
		}
		if ((*text)[cnt] == '\\' && single_quote == 0 && escape == 0)
		{
			escape = 1;
			cnt ++;
			continue ;
		}
		if ((*text)[cnt] == '\"' && escape == 0)
		{
			cnt ++;
			continue ;			
		}
		new[i] = (*text)[cnt];
		i ++;
		cnt ++;
		if (escape == 1)
			escape = 0;
	}
	free(*text);
	printf("%s\n%d\n%s\n%d\n%d\n", (*text), (int)ft_strlen(*text), new, i, (int)ft_strlen(new));
	(*text) = ft_strdup2(new, i);
	free(new);
}
