/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:41:48 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/16 21:08:05 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	putstr_stderr(char *s)
{
	if (!s)
		return ;
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
