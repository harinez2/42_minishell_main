#include "main.h"

void	errmsg_prefix(t_error_no errcode, char *errcmd, char *argtxt)
{
	putstr_stderr("minishell: ");
	if (errcmd)
	{
		putstr_stderr(errcmd);
		putstr_stderr(": ");
	}
	if (argtxt)
	{
		if (errcode == ERR_NOT_VALID_IDENTIFIER)
		{
			putstr_stderr("`");
			putstr_stderr(argtxt);
			putstr_stderr("'");
		}
		else
			putstr_stderr(argtxt);
		putstr_stderr(": ");
	}
}

void	print_perror(int err_no, char *errcmd, char *argtxt)
{
	errmsg_prefix(-1, errcmd, argtxt);
	putstr_stderr(strerror(err_no));
	putstr_stderr("\n");
}

void	print_perror_exit(int err_no, char *errcmd, char *argtxt, t_arg *arg)
{
	print_perror(err_no, errcmd, argtxt);
	destroy_arg(arg);
	exit(err_no);
}
