/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:40:32 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/16 19:40:33 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	builtincmd_exit(t_arg *arg, t_cmd *cmd)
{
	int		ret;

	dbg_print_cmdstart(arg, cmd->param[0]);
	dbg_print_str(arg, "=== builtin cmd exit ===\n");
	ret = 0;
	if (cmd->param_cnt > 1)
		ret = ft_atoi(cmd->param[1]);
	while (ret < 0)
		ret += 256;
	ret %= 256;
	if (arg->dbg)
		printf("Exit code:%d\n", ret);
	destroy_arg(arg);
	write(2, "exit\n", 5);
	exit (ret);
}
