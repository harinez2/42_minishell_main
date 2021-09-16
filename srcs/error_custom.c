/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_custom.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonishi <yonishi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 19:40:56 by yonishi           #+#    #+#             */
/*   Updated: 2021/09/16 19:40:57 by yonishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	get_retcode_custom(t_error_no myerrcode)
{
	if (myerrcode == ERR_FAILED_TO_EXEC)
		return (127);
	else if (myerrcode == ERR_HEREDOC)
		return (1);
	else if (myerrcode == ERR_SYNTAX_ERROR)
		return (258);
	else if (myerrcode == ERR_HOME_NOT_SET)
		return (1);
	else if (myerrcode == ERR_NOT_VALID_IDENTIFIER)
		return (1);
	else
		return (1);
}

int	print_custom_error(
	t_error_no myerrcode, char *errcmd, char *argtxt, t_arg *arg)
{
	errmsg_prefix(myerrcode, errcmd, argtxt);
	if (myerrcode == ERR_FAILED_TO_EXEC)
		putstr_stderr("command not found\n");
	else if (myerrcode == ERR_HEREDOC)
		putstr_stderr("heredoc error\n");
	else if (myerrcode == ERR_SYNTAX_ERROR)
		putstr_stderr("syntax error\n");
	else if (myerrcode == ERR_HOME_NOT_SET)
		putstr_stderr("HOME not set\n");
	else if (myerrcode == ERR_NOT_VALID_IDENTIFIER)
		putstr_stderr("not a valid identifier\n");
	else
		putstr_stderr("unexpected error\n");
	arg->last_exit_status = get_retcode_custom(myerrcode);
	return (get_retcode_custom(myerrcode));
}

void	print_custom_error_exit(
			t_error_no myerrcode, char *errcmd, char *argtxt, t_arg *arg)
{
	int		ret;

	ret = print_custom_error(myerrcode, errcmd, argtxt, arg);
	destroy_arg(arg);
	exit(ret);
}
