/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bnf_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:41:56 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/20 17:44:44 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	bnf_redirection_left(
	t_arg *arg, int token_info[][3], int *i, int leftflg)
{
	if (arg->dbg)
		printf("   =<=\n");
	if (leftflg)
		cmd_create_node_with_redir(arg, 0,
			arg->read + token_info[*i][1],
			token_info[*i][2] - token_info[*i][1]);
	else
		cmd_add_redir_filename(arg, 0,
			arg->read + token_info[*i][1],
			token_info[*i][2] - token_info[*i][1]);
}

static void	bnf_redirection_right(
	t_arg *arg, int token_info[][3], int *i, int leftflg)
{
	if (arg->dbg)
		printf("   =>=\n");
	if (leftflg)
		cmd_create_node_with_redir(arg, 1,
			arg->read + token_info[*i][1],
			token_info[*i][2] - token_info[*i][1]);
	else
		cmd_add_redir_filename(arg, 1,
			arg->read + token_info[*i][1],
			token_info[*i][2] - token_info[*i][1]);
}

static void	bnf_redirection_heredoc(
	t_arg *arg, int token_info[][3], int *i, int leftflg)
{
	char	*filename;
	char	*eof_name;

	if (arg->dbg)
		printf("   =<<=\n");
	eof_name = ft_substr(arg->read, token_info[*i][1],
			token_info[*i][2] - token_info[*i][1]);
	filename = heredoc_read(arg, eof_name);
	if (leftflg)
		cmd_create_node_with_redir(arg, 0, filename,
			HEREDOC_FILENAME_LEN);
	else
		cmd_add_redir_filename(arg, 0, filename,
			HEREDOC_FILENAME_LEN);
	cmd_add_flg(arg, TKN_HEREDOC, 1);
	secure_free(filename);
	secure_free(eof_name);
}

static void	bnf_redirection_append(
	t_arg *arg, int token_info[][3], int *i, int leftflg)
{
	if (arg->dbg)
		printf("   =>>=\n");
	bnf_redirection_right(arg, token_info, i, leftflg);
	cmd_add_flg(arg, TKN_REDIR_APPEND, 1);
}

void	bnf_redirection_op(
	t_arg *arg, int token_info[][3], int *i, int leftflg)
{
	if (token_info[*i - 1][0] == TKN_REDIR_LEFT)
		bnf_redirection_left(arg, token_info, i, leftflg);
	else if (token_info[*i - 1][0] == TKN_REDIR_RIGHT)
		bnf_redirection_right(arg, token_info, i, leftflg);
	else if (token_info[*i - 1][0] == TKN_HEREDOC)
		bnf_redirection_heredoc(arg, token_info, i, leftflg);
	else if (token_info[*i - 1][0] == TKN_REDIR_APPEND)
		bnf_redirection_append(arg, token_info, i, leftflg);
}
