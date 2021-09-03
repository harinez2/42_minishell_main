#include "main.h"

void	dbg_print_cmdstart(t_arg *arg, char *s)
{
	dbg_print_str(arg, "/---Executing:");
	dbg_print_str(arg, s);
	dbg_print_str(arg, "\n");
}

void	dbg_print_cmdend(t_arg *arg, int status)
{
	dbg_print_str(arg, "\\---Exited (Is exited: ");
	dbg_print_int(arg, WIFEXITED(status));
	if (WIFEXITED(status))
	{
		dbg_print_str(arg, ", Exit status: ");
		dbg_print_int(arg, WEXITSTATUS(status));
	}
	dbg_print_str(arg, ")\n");
}

void	connect_pipe(int unused, int old, int new, t_arg *arg)
{
	int		ret;

	if (unused != -1)
	{
		close(unused);
		dbg_print_strint(arg, "[fd] [child] closed: ", unused);
	}
	ret = dup2(old, new);
	if (ret == -1)
		print_perror_exit(errno, NULL, NULL, arg);
	dbg_print_strint(arg, "[fd] [child] dup2: old", old);
	dbg_print_strint(arg, "[fd] [child] dup2: new", new);
	close_pipe(arg, "child", old);
}

void	close_pipe(t_arg *arg, char *who, int fd)
{
	int		ret;

	ret = close(fd);
	if (ret == -1)
		print_perror_exit(errno, NULL, NULL, arg);
	dbg_print_str(arg, "[fd] [");
	dbg_print_str(arg, who);
	dbg_print_strint(arg, "] closed:", fd);
}

void	ignore_toomuch_redirout(t_arg *arg, t_cmd *c)
{
	int		i;
	int		fd;
	int		ret;

	i = 0;
	while (i < c->redir_out_cnt - 1)
	{
		if (c->append_flg[i] == 0)
		{
			fd = open(c->redir_out[i], O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (fd == -1)
				print_perror_exit(errno, NULL, NULL, arg);
			ret = close(fd);
			if (ret == -1)
				print_perror_exit(errno, NULL, NULL, arg);
		}
		i++;
	}
}
