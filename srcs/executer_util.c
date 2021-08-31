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

void	close_pipe(t_arg *arg, char *who, int fd)
{
	int		ret;

	ret = close(fd);
	if (ret == -1)
		error_exit(ERR_PIPE, NULL, arg);
	dbg_print_str(arg, "[fd] [");
	dbg_print_str(arg, who);
	dbg_print_strint(arg, "] closed:", fd);
}

void	check_and_exit_program(t_arg *arg, t_cmd *c)
{
	if (ft_strncmp("exit", c->param[0], 5) == 0)
	{
		destroy_arg(arg);
		exit (0);
	}
}
