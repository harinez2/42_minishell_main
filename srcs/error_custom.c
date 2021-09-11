#include "main.h"

static int	get_retcode(t_error_no errcode)
{
	if (errcode == ERR_FAILED_TO_EXEC)
		return (127);
	else if (errcode == ERR_HEREDOC)
		return (1);
	else if (errcode == ERR_SYNTAX_ERROR)
		return (258);
	else if (errcode == ERR_HOME_NOT_SET)
		return (1);
	else if (errcode == ERR_NOT_VALID_IDENTIFIER)
		return (1);
	else
		return (1);
}

int	print_custom_error(t_error_no errcode, char *errcmd, char *argtxt)
{
	errmsg_prefix(errcode, errcmd, argtxt);
	if (errcode == ERR_FAILED_TO_EXEC)
		putstr_stderr("command not found\n");
	else if (errcode == ERR_HEREDOC)
		putstr_stderr("heredoc error\n");
	else if (errcode == ERR_SYNTAX_ERROR)
		putstr_stderr("syntax error\n");
	else if (errcode == ERR_HOME_NOT_SET)
		putstr_stderr("HOME not set\n");
	else if (errcode == ERR_NOT_VALID_IDENTIFIER)
		putstr_stderr("not a valid identifier\n");
	else
		putstr_stderr("unexpected error\n");
	return (get_retcode(errcode));
}

void	print_custom_error_exit(
			t_error_no errcode, char *errcmd, char *argtxt, t_arg *arg)
{
	print_custom_error(errcode, errcmd, argtxt);
	destroy_arg(arg);
	exit(MASK_7BIT);
}
