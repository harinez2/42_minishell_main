#include "main.h"

void	print_cmdstart(char *s)
{
	print_stderr_str(COL_TX_CYAN"/---Executing:");
	print_stderr_str(s);
	print_stderr_str("\n"COL_TX_RESET);
}

void	print_cmdend(int status)
{
	print_stderr_str(COL_TX_CYAN"\\---Exited (Is exited: ");
	print_stderr_int(WIFEXITED(status));
	if (WIFEXITED(status))
	{
		print_stderr_str(", Exit status: ");
		print_stderr_int(WEXITSTATUS(status));
	}
	print_stderr_str(")\n"COL_TX_RESET);
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
