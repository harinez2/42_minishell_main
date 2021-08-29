#include "main.h"

void	print_cmdstart(t_arg *arg, char *s)
{
	dbg_print_str(arg, "/---Executing:");
	dbg_print_str(arg, s);
	dbg_print_str(arg, "\n");
}

void	print_cmdend(t_arg *arg, int status)
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

void	check_and_exit_program(t_arg *arg, t_cmd *c)
{
	if (ft_strncmp("exit", c->param[0], 5) == 0)
	{
		//secure_free(read);
		cmd_destroy(arg);
		exit (0);
	}
}
