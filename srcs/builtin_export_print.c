/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:40:35 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/16 19:40:36 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	get_bigger_len(t_env *s1, t_env *s2)
{
	int		ret;

	ret = ft_strlen(s1->env);
	if (ret < (int)ft_strlen(s2->env))
		ret = ft_strlen(s2->env);
	return (ret);
}

static void	mergesort_merge_env(t_env *env_i[], int start, int end)
{
	int		i;
	int		j;
	int		mid;
	t_env	*sorted[MAX_ENVP];
	int		s;

	mid = start + (end - start) / 2;
	i = start;
	j = mid;
	s = 0;
	while (i < mid && j < end)
	{
		if (ft_strncmp((env_i[i])->env, (env_i[j])->env,
				get_bigger_len(env_i[i], env_i[j])) < 0)
			sorted[s++] = env_i[i++];
		else
			sorted[s++] = env_i[j++];
	}
	if (i == mid)
		while (j < end)
			sorted[s++] = env_i[j++];
	else
		while (i < mid)
			sorted[s++] = env_i[i++];
	copy_array(env_i, sorted, s, start);
}

static void	mergesort_env(t_env *env_i[], int start, int end)
{
	int		mid;

	if (start == end || start + 1 == end)
		return ;
	mid = start + (end - start) / 2;
	mergesort_env(env_i, start, mid);
	mergesort_env(env_i, mid, end);
	mergesort_merge_env(env_i, start, end);
}

void	print_env_export(t_arg *arg)
{
	int		cnt;
	int		i;
	t_env	*env_i[MAX_ENVP];
	t_env	*e;

	e = arg->envlst;
	cnt = 0;
	while (e != NULL)
	{
		env_i[cnt] = e;
		cnt++;
		e = e->next;
	}
	mergesort_env(env_i, 0, cnt);
	i = 0;
	while (i < cnt)
	{
		if (env_i[i]->value != NULL)
			printf("declare -x %s=\"%s\"\n", env_i[i]->env, env_i[i]->value);
		else
			printf("declare -x %s\n", env_i[i]->env);
		i++;
	}
}
