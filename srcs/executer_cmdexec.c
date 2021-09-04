#include "main.h"

static int	exec_builtincmd(t_cmd *cmd, t_arg *arg)
{
	if (ft_strncmp("echo", cmd->param[0], 5) == 0)
		builtincmd_echo(arg, cmd);
	else
		return (0);
	exit (0);
}

static int	exec_shellcmd(t_cmd *cmd, t_arg *arg)
{
	int		ret;
	char	*param_zero;
	char	**env;
	int		i;

	i = 0;
	ret = -1;
	env = generate_environ(arg);
	param_zero = cmd->param[0];
	while (ret != 0 && arg->path[i] != NULL)
	{
		cmd->param[0] = ft_strjoin3(arg->path[i], "/", param_zero);
		if (access(cmd->param[0], X_OK) == 0)
		{
			dbg_print_cmdstart(arg, cmd->param[0]);
			ret = execve(cmd->param[0], cmd->param, env);
		}
		secure_free(cmd->param[0]);
		i++;
	}
	cmd->param[0] = param_zero;
	destroy_environ(env);
	return (-1);
}

void	exec_command(t_cmd *cmd, t_arg *arg)
{
	update_envpath(arg);
	if (exec_builtincmd(cmd, arg) == 1)
		return ;
	else if (exec_shellcmd(cmd, arg) == 0)
		return ;
	print_custom_error_exit(ERR_FAILED_TO_EXEC, cmd->param[0], NULL, arg);
}
