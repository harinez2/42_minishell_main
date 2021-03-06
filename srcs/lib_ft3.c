/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_ft3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:41:36 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/16 19:41:36 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

ssize_t	ft_strchr(const char *s, int c)
{
	ssize_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (i);
}

char	*ft_strdup2(const char *s1, ssize_t n)
{
	ssize_t	i;
	char	*p;

	p = (char *)malloc(sizeof(char) * (n + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && i < n)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
