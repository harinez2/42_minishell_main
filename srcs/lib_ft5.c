/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_ft5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:41:41 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/16 19:41:42 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
