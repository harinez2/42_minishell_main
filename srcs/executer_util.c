#include "main.h"

void	print_cmdstart(char *s)
{
	write(2, "/---Executing:", 14);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
}

void	print_cmdend(int status)
{
	write(2, "\\---Exited (Is exited: ", 24);
	print_stderr_int(WIFEXITED(status));
	if (WIFEXITED(status))
	{
		write(2, ", Exit status: ", 15);
		print_stderr_int(WEXITSTATUS(status));
	}
	write(2, ")\n", 2);
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
