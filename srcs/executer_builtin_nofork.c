#include "main.h"

int	run_builtin_nofork(t_arg *arg, t_cmd *c, int *status)
{
	int		ret;

	if ((size_t)ft_strchr(c->param[0], '=') != ft_strlen(c->param[0]))
		ret = 0;
	else if (ft_strncmp("cd", c->param[0], 3) == 0)
		ret = builtincmd_cd(arg, c);
	else if (ft_strncmp("export", c->param[0], 7) == 0 && c->param_cnt > 1)
		ret = builtincmd_export_witharg(arg, c);
	else if (ft_strncmp("unset", c->param[0], 6) == 0)
		ret = builtincmd_unset(arg, c);
	else if (ft_strncmp("exit", c->param[0], 5) == 0)
		ret = builtincmd_exit(arg, c);
	else
		return (1);
	*status = ret << 8 & 0xff00;
	return (0);
}
