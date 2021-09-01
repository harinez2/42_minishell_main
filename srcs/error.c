#include "main.h"

static void	errmsg_prefix(char *errcmd)
{
	putstr_stderr("minishell: ");
	if (errcmd)
	{
		putstr_stderr(errcmd);
		putstr_stderr(": ");
	}
}

void	print_error(int errcode, char *errcmd, char *txt)
{
	errmsg_prefix(errcmd);
	if (errcode == ERR_CD_INVALIDPATH)
		perror(txt);
}

void	error_exit(int errcode, char *errcmd, t_arg *arg)
{
	errmsg_prefix(errcmd);
	if (errcode == ERR_ENV_INVALID)
		perror("error");
	else if (errcode == ERR_NOT_ENOUGH_PARAM)
		perror("error");
	else if (errcode == ERR_FAILED_TO_OPEN_FILE)
		perror("error");
	else if (errcode == ERR_PIPE)
		perror("error");
	else if (errcode == ERR_FAILED_TO_FORK)
		perror("error");
	else if (errcode == ERR_FAILED_TO_EXEC)
		putstr_stderr("command not found\n");
	else if (errcode == ERR_FAILED_TO_MALLOC)
		perror("error");
	else if (errcode == ERR_HEREDOC)
		putstr_stderr("heredoc error\n");
	else if (errcode == ERR_SYNTAX_ERROR)
		putstr_stderr("syntax error\n");
	else
		putstr_stderr("unexpected error\n");
	if (arg != NULL)
		free(arg->path[0]);
	cmd_destroy(arg);
	exit(-1);
}
