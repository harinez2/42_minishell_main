/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_char_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtomiki <rtomiki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 20:15:48 by rtomiki           #+#    #+#             */
/*   Updated: 2021/09/19 21:43:45 by rtomiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	judge_escpae(char c, int *single_quote, int *escape, int *cnt)
{
	if (c == '\'')
		(*single_quote) ^= 1;
	if ((c == '\"' && (*single_quote) == 0 && (*escape) == 0) || c == '\''
		|| ((c == '\\' && (*single_quote) == 0 && (*escape) == 0)))
	{
		if (c == '\\')
			(*escape) = 1;
		(*cnt)++;
		return (1);
	}	
	return (0);
}

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
		if (judge_escpae((*text)[cnt], &single_quote, &escape, &cnt))
			continue ;
		new[i] = (*text)[cnt];
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
