/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_builtin_nofork.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:41:02 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/16 19:41:03 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	run_builtin_nofork(t_arg *arg, t_cmd *c, int *status)
{
	int		ret;

	if (c->param[0] == NULL)
		ret = 0;
	else if (ft_strncmp("cd", c->param[0], 3) == 0)
		ret = builtincmd_cd(arg, c);
	else if (ft_strncmp("export", c->param[0], 7) == 0 && c->param_cnt > 1)
		ret = builtincmd_export_witharg(arg, c);
	else if (ft_strncmp("unset", c->param[0], 6) == 0)
		ret = builtincmd_unset(arg, c);
	else if (ft_strncmp("exit", c->param[0], 5) == 0)
		ret = builtincmd_exit(arg, c);
	else
		return (1);
	*status = ret << 8 & 0xff00;
	return (0);
}
