#include "main.h"

static int	exec_builtincmd(t_cmd *cmd, t_arg *arg)
{
	if (ft_strncmp("echo", cmd->param[0], 5) == 0)
		builtincmd_echo(arg, cmd);
	else if (ft_strncmp("export", cmd->param[0], 7) == 0)
		builtincmd_export(arg, cmd, arg->envp);
	else if (ft_strncmp("env", cmd->param[0], 4) == 0)
		builtincmd_env(arg, cmd);
	else if (ft_strncmp("pwd", cmd->param[0], 4) == 0)
		builtincmd_pwd(arg, cmd);
	else if (ft_strncmp("cd", cmd->param[0], 3) == 0)
		builtincmd_cd(arg, cmd);
	else
		return (0);
	exit (0);
}

static int	exec_shellcmd(t_cmd *cmd, t_arg *arg)
{
	int		ret;
	char	*param_zero;
	int		i;

	i = 0;
	ret = -1;
	param_zero = cmd->param[0];
	while (ret != 0 && arg->path[i] != NULL)
	{
		cmd->param[0] = ft_strjoin3(arg->path[i], "/", param_zero);
		if (access(cmd->param[0], X_OK) == 0)
		{
			dbg_print_cmdstart(arg, cmd->param[0]);
			ret = execve(cmd->param[0], cmd->param, NULL);
		}
		secure_free(cmd->param[0]);
		i++;
	}
	cmd->param[0] = param_zero;
	return (-1);
}

void	exec_command(t_cmd *cmd, t_arg *arg)
{
	update_envpath(arg);
	if (exec_builtincmd(cmd, arg) == 1)
		return ;
	else if (exec_shellcmd(cmd, arg) == 0)
		return ;
	error_exit(ERR_FAILED_TO_EXEC, cmd->param[0], arg);
}
