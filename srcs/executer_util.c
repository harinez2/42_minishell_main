#include "main.h"

void	print_cmdstart(char *s)
{
	write(2, "/---Executing:", 14);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
}

void	print_cmdend(int status)
{
	printf("\\---Exited (Is exited: %x", WIFEXITED(status));
	if (WIFEXITED(status))
		printf(", Exit status: %d", WEXITSTATUS(status));
	printf(")\n");
}

void	check_and_exit_program(t_arg *arg, t_cmd *c)
{
	if (ft_strncmp("exit", c->param[0], 5) == 0)
	{
		//secure_free(read);
		struct_destroy(arg);
		exit (0);
	}
}
