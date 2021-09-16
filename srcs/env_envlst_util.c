/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_envlst_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:40:51 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/16 19:40:52 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_env	*get_node_from_envlst(t_env	*envlst, char *envname)
{
	t_env		*e;

	e = envlst;
	while (e != NULL)
	{
		if (ft_strncmp(e->env, envname, ft_strlen(envname) + 1) == 0)
			return (e);
		e = e->next;
	}
	return (NULL);
}

int	count_envlst(t_arg *arg)
{
	t_env	*e;
	int		ret;

	ret = 0;
	e = arg->envlst;
	while (e)
	{
		ret++;
		e = e->next;
	}
	return (ret);
}

int	is_shellver_char_onechar(char c)
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')
		|| ('0' <= c && c <= '9') || c == '_')
		return (1);
	else
		return (0);
}

int	is_shellver_char(char *s, int start, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if (!s[start + i])
			return (0);
		if (is_shellver_char_onechar(s[start + i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_env_definition(char *s)
{
	int		eqpos;

	eqpos = ft_strchr(s, '=');
	if ((size_t)eqpos != ft_strlen(s)
		&& eqpos != 0
		&& is_shellver_char(s, 0, eqpos - 1) == 1
		&& (is_shellver_char_onechar(s[eqpos - 1]) || s[eqpos - 1] == '+'))
		return (1);
	else
		return (0);
}
