/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:42:10 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/16 19:42:11 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// in:0, out:1
int	cmd_add_redir_filename(t_arg *arg, int inout, char *read, int len)
{
	t_cmd	*c;
	char	*filename;

	c = cmd_get_last_node(arg->cmdlst);
	if (c == NULL)
		return (-1);
	filename = malloc(sizeof(char) * (len + 1));
	if (!filename)
		print_perror_exit(errno, NULL, NULL, arg);
	ft_strlcpy(filename, read, len + 1);
	if (inout == 0)
	{
		if (c->redir_in != NULL)
			free(c->redir_in);
		c->redir_in = filename;
	}
	else
	{
		c->redir_out[c->redir_out_cnt] = filename;
		c->append_flg[c->redir_out_cnt++] = 0;
	}
	return (0);
}

int	cmd_add_flg(t_arg *arg, t_token_type t, int flg)
{
	t_cmd	*c;

	c = cmd_get_last_node(arg->cmdlst);
	if (c == NULL)
		return (-1);
	if (t == TKN_SINGLE_OR || t == TKN_AMP)
		c->nxtcmd_relation = flg;
	else if (t == TKN_HEREDOC)
		c->heredoc_flg = 1;
	else if (t == TKN_REDIR_APPEND)
		c->append_flg[c->redir_out_cnt - 1] = 1;
	return (0);
}

int	cmd_add_param(t_arg *arg, char *cmdtxt, int len)
{
	t_cmd	*c;

	c = cmd_get_last_node(arg->cmdlst);
	if (c == NULL)
		return (-1);
	c->param[c->param_cnt++] = ft_substr(cmdtxt, 0, len);
	c->param[c->param_cnt] = NULL;
	return (0);
}
