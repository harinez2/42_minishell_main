#include "main.h"

static void	errmsg_prefix(char *errcmd, char *argtxt)
{
	putstr_stderr("minishell: ");
	if (errcmd)
	{
		putstr_stderr(errcmd);
		putstr_stderr(": ");
	}
	if (argtxt)
	{
		putstr_stderr(argtxt);
		putstr_stderr(": ");
	}
}

void	print_perror(int err_no, char *errcmd, char *argtxt)
{
	errmsg_prefix(errcmd, argtxt);
	putstr_stderr(strerror(err_no));
	putstr_stderr("\n");
}

void	print_custom_error(t_error_no errcode, char *errcmd, char *argtxt)
{
	errmsg_prefix(errcmd, argtxt);
	if (errcode == ERR_FAILED_TO_EXEC)
		putstr_stderr("command not found\n");
	else if (errcode == ERR_HEREDOC)
		putstr_stderr("heredoc error\n");
	else if (errcode == ERR_SYNTAX_ERROR)
		putstr_stderr("syntax error\n");
	else if (errcode == ERR_HOME_NOT_SET)
		putstr_stderr("HOME not set\n");
	else
		putstr_stderr("unexpected error\n");
}

void	print_perror_exit(int err_no, char *errcmd, char *argtxt, t_arg *arg)
{
	print_perror(err_no, errcmd, argtxt);
	destroy_arg(arg);
	exit(-1);
}

void	print_custom_error_exit(
			t_error_no errcode, char *errcmd, char *argtxt, t_arg *arg)
{
	print_custom_error(errcode, errcmd, argtxt);
	destroy_arg(arg);
	exit(-1);
}
