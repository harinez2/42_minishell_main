#include "main.h"

static void	connect_pipe(int unused, int old, int new, t_arg *arg)
{
	int		ret;

	if (unused != -1)
		close(unused);
	ret = dup2(old, new);
	if (ret == -1)
		error_exit(ERR_PIPE, arg);
	ret = close(old);
	if (ret == -1)
		error_exit(ERR_PIPE, arg);
}

static int	open_infile(char *filename, t_arg *arg)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_exit(ERR_FAILED_TO_OPEN_FILE, arg);
	return (fd);
}

static int	open_outfile(char *filename, t_arg *arg)
{
	int		fd;
	char	outfilepath[300];

	ft_strlcpy(outfilepath, "./", 3);
	ft_strlcat(outfilepath, filename, ft_strlen(filename) + 3);
	fd = open(outfilepath, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (fd == -1)
		error_exit(ERR_FAILED_TO_OPEN_FILE, arg);
	return (fd);
}

static void	executer_childprocess(t_arg *arg, t_cmd	*c)
{
	if (c->redir_out != NULL)
		connect_pipe(-1, open_outfile(c->redir_out, arg), 1, arg);
	else if (c->nxtcmd_relation == CONN_PIPE)
		connect_pipe(c->pipe[PP_READ], c->pipe[PP_WRITE], 1, arg);
	if (c->redir_in != NULL)
		connect_pipe(-1, open_infile(c->redir_in, arg), 0, arg);
	else if (c->prev != NULL && c->prev->nxtcmd_relation == CONN_PIPE)
		connect_pipe(c->prev->pipe[PP_WRITE],
			c->prev->pipe[PP_READ], 0, arg);
	exec_command(c, arg);
}

int	executer(t_arg *arg)
{
	pid_t	pid;
	t_cmd	*c;
	int		status;

	c = arg->cmdlst;
	while (c != NULL)
	{
		check_and_exit_program(arg, c);
		if (c->nxtcmd_relation == CONN_PIPE)
			pipe(c->pipe);
		pid = fork();
		if (pid == -1)
			error_exit(ERR_FAILED_TO_FORK, arg);
		else if (pid == 0)
			executer_childprocess(arg, c);
		waitpid(pid, &status, 0);
		if (c->nxtcmd_relation == CONN_PIPE)
			close(c->pipe[PP_WRITE]);
		if (c->prev != NULL && c->prev->nxtcmd_relation == CONN_PIPE)
			close(c->prev->pipe[PP_READ]);
		if (arg->dbg == 1)
			print_cmdend(status);
		c = c->next;
	}
	return (0);
}
