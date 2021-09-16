/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_ft2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:41:34 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/16 19:41:34 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		i;

	i = 0;
	while (i + 1 < dstsize)
	{
		dst[i] = src[i];
		if (src[i] == '\0')
			break ;
		i++;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		j;
	char	*p;

	if (s1 == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
		i++;
	p = (void *)malloc(sizeof(char) * (i + 1));
	if (!p)
		return (NULL);
	j = 0;
	while (j < i)
	{
		p[j] = s1[j];
		j++;
	}
	p[j] = '\0';
	return (p);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1len;
	int		s2len;
	int		i;
	char	*t;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	t = malloc(sizeof(char) * (s1len + s2len + 1));
	if (!t)
		return (NULL);
	i = 0;
	while (i < s1len)
	{
		t[i] = s1[i];
		i++;
	}
	while (i < (s1len + s2len))
	{
		t[i] = s2[i - s1len];
		i++;
	}
	t[i] = '\0';
	return (t);
}

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	int		s1len;
	int		s2len;
	int		s3len;
	int		i;
	char	*t;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	s3len = ft_strlen(s3);
	t = malloc(sizeof(char) * (s1len + s2len + s3len + 1));
	if (!t)
		return (NULL);
	i = ft_strlcpy(t, s1, s1len + 1);
	i += ft_strlcpy(t + s1len, s2, s2len + 1);
	i += ft_strlcpy(t + s1len + s2len, s3, s3len + 1);
	return (t);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		srclen;
	size_t		dstlen;
	size_t		i;
	char		*t;

	srclen = (size_t)ft_strlen(s);
	if ((size_t)start < srclen)
	{
		dstlen = len;
		if ((size_t)start + len > srclen)
			dstlen = srclen - (size_t)start;
	}
	else
		dstlen = 0;
	t = malloc(sizeof(char) * (dstlen + 1));
	if (!t)
		return (NULL);
	i = 0;
	while (i < dstlen)
	{
		t[i] = s[(size_t)start + i];
		i++;
	}
	t[i] = '\0';
	return (t);
}
