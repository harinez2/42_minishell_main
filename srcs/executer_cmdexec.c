#include "main.h"

static int	exec_builtincmd(t_cmd *c, t_arg *arg)
{
	int		ret;

	if (ft_strncmp("echo", c->param[0], 5) == 0)
		ret = builtincmd_echo(arg, c);
	else if (ft_strncmp("export", c->param[0], 7) == 0)
		ret = builtincmd_export_noarg(arg, c);
	else if (ft_strncmp("env", c->param[0], 4) == 0)
		ret = builtincmd_env(arg, c);
	else if (ft_strncmp("pwd", c->param[0], 4) == 0)
		ret = builtincmd_pwd(arg, c);
	else
		return (0);
	exit (ret);
}

void	exec_command(t_cmd *cmd, t_arg *arg)
{
	t_env	*e;

	e = get_node_from_envlst(arg->envlst, "PATH");
	if (!e)
		destroy_path(arg);
	else
		update_envpath(arg, e->value);
	if (exec_builtincmd(cmd, arg) != 0)
		return ;
	exec_shellcmd(cmd, arg);
}
