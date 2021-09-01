#include "main.h"

int	run_builtin_nofork(t_arg *arg, t_cmd *c)
{
	if (ft_strncmp("cd", c->param[0], 3) == 0)
		builtincmd_cd(arg, c);
	else if (ft_strncmp("exit", c->param[0], 5) == 0)
	{
		destroy_arg(arg);
		exit (0);
	}
	else
		return (1);
	return (0);
}
