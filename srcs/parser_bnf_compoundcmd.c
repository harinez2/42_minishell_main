/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bnf_compoundcmd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:41:54 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/16 19:41:55 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// <redirection> ::=
// 	"<" string
// 	|	">" string
// 	|	"<<" string
// 	|	">>" string
int	bnf_redirection(
	t_arg *arg, int token_info[][3], int *i, int leftflg)
{
	if (arg->dbg)
		printf("%2d <redirection>\n", *i);
	if (token_info[*i][0] == TKN_REDIR_LEFT
		|| token_info[*i][0] == TKN_REDIR_RIGHT
		|| token_info[*i][0] == TKN_HEREDOC
		|| token_info[*i][0] == TKN_REDIR_APPEND)
	{
		(*i)++;
		if (token_info[*i][0] == TKN_STRING)
		{
			if (arg->dbg)
				printf("   =string: redir filename=\n");
			bnf_redirection_op(arg, token_info, i, leftflg);
			(*i)++;
		}
		else
			return (-1);
	}
	else
		return (-1);
	return (0);
}

// <param_redir> ::=
// 	string
// 	|	<redirection>
int	bnf_param_redir(t_arg *arg, int token_info[][3], int *i)
{
	if (arg->dbg)
		printf("%2d <param_redir>\n", *i);
	if (token_info[*i][0] == TKN_STRING)
	{
		if (arg->dbg)
			printf("   =string: param=\n");
		cmd_add_param(arg, arg->read + token_info[*i][1],
			token_info[*i][2] - token_info[*i][1]);
		(*i)++;
	}
	else if (bnf_redirection(arg, token_info, i, 0) == 0)
		;
	else
		return (-1);
	return (0);
}

// <command_elements> ::=
// 	<param_redir> 
// 	|	<param_redir>  <command_elements>
int	bnf_command_elements(t_arg *arg, int token_info[][3], int *i)
{
	if (arg->dbg)
		printf("%2d <command_elements>\n", *i);
	if (bnf_param_redir(arg, token_info, i) == 0)
	{
		bnf_command_elements(arg, token_info, i);
	}
	else
		return (-1);
	return (0);
}

// <simple_command> ::=
// 	string
int	bnf_simple_command(t_arg *arg, int token_info[][3], int *i)
{
	if (arg->dbg)
		printf("%2d <simple_command>\n", *i);
	if (token_info[*i][0] == TKN_STRING)
	{
		if (arg->dbg)
			printf("   =string: cmd=\n");
		cmd_create_node_with_param(arg, arg->read + token_info[*i][1],
			token_info[*i][2] - token_info[*i][1]);
		(*i)++;
	}
	else
		return (-1);
	return (0);
}

// <compoud_command> ::=
// 	<redirection> <simple_command>
// 	|	<redirection> <simple_command> <command_elements>
// 	|	<simple_command>
// 	|	<simple_command> <command_elements>
int	bnf_compoud_command(t_arg *arg, int token_info[][3], int *i)
{
	if (arg->dbg)
		printf("%2d <compoud_command>\n", *i);
	if (bnf_redirection(arg, token_info, i, 1) == 0)
	{
		if (bnf_simple_command(arg, token_info, i) == 0)
		{
			bnf_command_elements(arg, token_info, i);
		}
		else
			return (-1);
	}
	else if (bnf_simple_command(arg, token_info, i) == 0)
	{
		bnf_command_elements(arg, token_info, i);
	}
	else
		return (-1);
	return (0);
}
