/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:42:15 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/16 19:42:16 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_cmd	*cmd_get_last_node(t_cmd *cmd)
{
	if (cmd == NULL)
		return (NULL);
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}

void	remove_cmdparam_head(t_cmd *c)
{
	int		i;

	if (c->param_cnt == 0)
		return ;
	secure_free(c->param[0]);
	i = 0;
	while (i < c->param_cnt)
	{
		c->param[i] = c->param[i + 1];
		i++;
	}
	c->param_cnt--;
}
