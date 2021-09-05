#include "main.h"

int	run_builtin_nofork(t_arg *arg, t_cmd *c)
{
	if ((size_t)ft_strchr(c->param[0], '=') != ft_strlen(c->param[0]))
		return (0);
	if (ft_strncmp("cd", c->param[0], 3) == 0)
		builtincmd_cd(arg, c);
	else if (ft_strncmp("export", c->param[0], 7) == 0 && c->param_cnt > 1)
		builtincmd_export_witharg(arg, c);
	else if (ft_strncmp("unset", c->param[0], 6) == 0)
		builtincmd_unset(arg, c);
	else if (ft_strncmp("exit", c->param[0], 5) == 0)
	{
		destroy_arg(arg);
		exit (0);
	}
	else
		return (1);
	return (0);
}
