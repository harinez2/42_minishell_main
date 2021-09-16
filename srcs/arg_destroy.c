/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:39:57 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/16 19:40:12 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	destroy_path(t_arg *arg)
{
	int			i;

	i = 0;
	while (i < arg->path_cnt)
		secure_free(arg->path[i++]);
	arg->path_cnt = 0;
}

void	destroy_arg(t_arg *arg)
{
	if (arg->read != arg->argv[2])
		secure_free(arg->read);
	destroy_path(arg);
	secure_free(arg->pwd);
	secure_free(arg->initial_home);
	cmd_destroy(arg);
	destroy_envlst(arg);
}
