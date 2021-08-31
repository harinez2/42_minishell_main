#include "main.h"

void	print_error(int errcode, char *txt)
{
	if (errcode == ERR_CD_INVALIDPATH)
	{
		write(2, "Error : ", 8);
		write(2, txt, ft_strlen(txt));
		perror(" ");
	}
}

void	error_exit(int errcode, char *errtxt, t_arg *arg)
{
	putstr_stderr("minishell: ");
	if (errtxt)
	{
		putstr_stderr(errtxt);
		putstr_stderr(": ");
	}
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
