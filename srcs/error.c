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

// #define ENOTDIR         20      /* Not a directory */
// #define ENOENT           2      /* No such file or directory */
// #define EACCES          13      /* Permission denied */
static int	get_retcode(t_error_no errcode)
{
	if (errcode == ENOTDIR)
		return (1);
	else if (errcode == EACCES)
		return (126);
	else if (errcode == ENOENT)
		return (127);
	else
		return (MASK_7BIT);
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
	exit(get_retcode(err_no));
}
