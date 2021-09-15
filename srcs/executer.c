#include "main.h"

static int	open_infile(char *filename, t_arg *arg)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_perror_exit(errno, NULL, NULL, arg);
	dbg_print_strint(arg, "  [fd] [child] open infile: ", fd);
	return (fd);
}

static int	open_outfile(char *filename, t_cmd *c, t_arg *arg)
{
	int		fd;

	if (c->append_flg[c->redir_out_cnt - 1])
		fd = open(filename, O_WRONLY | O_APPEND, 0);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		print_perror_exit(errno, NULL, NULL, arg);
	dbg_print_strint(arg, "  [fd] [child] open outfile: ", fd);
	return (fd);
}

static void	executer_childprocess(t_arg *arg, t_cmd *c)
{
	int		fd;

	ignore_toomuch_redirout(arg, c);
	if (c->redir_out_cnt != 0)
	{
		fd = open_outfile(c->redir_out[c->redir_out_cnt - 1], c, arg);
		connect_pipe(-1, fd, 1, arg);
	}
	else if (c->nxtcmd_relation == CONN_PIPE)
		connect_pipe(c->pipe[PP_READ], c->pipe[PP_WRITE], 1, arg);
	if (c->redir_in != NULL)
	{
		fd = open_infile(c->redir_in, arg);
		connect_pipe(-1, fd, 0, arg);
	}
	else if (c->prev != NULL && c->prev->nxtcmd_relation == CONN_PIPE)
		connect_pipe(c->prev->pipe[PP_WRITE],
			c->prev->pipe[PP_READ], 0, arg);
	exec_command(c, arg);
}

static void	executer_parentprocess(t_arg *arg, t_cmd *c)
{
	if (c->nxtcmd_relation == CONN_PIPE)
		close_pipe(arg, "parent", c->pipe[PP_WRITE]);
	if (c->prev != NULL && c->prev->nxtcmd_relation == CONN_PIPE)
		close_pipe(arg, "parent", c->prev->pipe[PP_READ]);
}

int	executer(t_arg *arg)
{
	pid_t	pid;
	t_cmd	*c;
	int		status;

	if (arg->dbg)
		printf(COL_TX_CYAN"<<< executer results >>>\n"COL_TX_RESET);
	c = arg->cmdlst;
	while (c != NULL)
	{
		if (run_builtin_nofork(arg, c, &status) == 1)
		{
			if (c->nxtcmd_relation == CONN_PIPE)
				pipe(c->pipe);
			pid = fork();
			if (pid == -1)
				print_perror_exit(errno, NULL, NULL, arg);
			else if (pid == 0)
				executer_childprocess(arg, c);
			waitpid(pid, &status, 0);
			executer_parentprocess(arg, c);
		}
		handling_exit_status(arg, status);
		c = c->next;
	}
	return (arg->last_exit_status);
}
