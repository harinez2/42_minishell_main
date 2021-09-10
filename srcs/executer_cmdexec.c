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

static int	exec_shellcmd_execve(t_cmd *cmd, t_arg *arg, char **env)
{
	int		ret;

	ret = -1;
	if (access(cmd->param[0], X_OK) == 0)
	{
		dbg_print_cmdstart(arg, cmd->param[0]);
		ret = execve(cmd->param[0], cmd->param, env);
	}
	return (ret);
}

static int	exec_shellcmd(t_cmd *cmd, t_arg *arg)
{
	int		ret;
	char	*param_zero;
	char	**env;
	int		i;

	i = 0;
	ret = MASK_7BIT;
	env = generate_environ(arg);
	if (cmd->param[0][0] == '/')
		exec_shellcmd_execve(cmd, arg, env);
	else
	{
		param_zero = cmd->param[0];
		while (ret != 0 && i < arg->path_cnt)
		{
			cmd->param[0] = ft_strjoin3(arg->path[i], "/", param_zero);
			ret = exec_shellcmd_execve(cmd, arg, env);
			secure_free(cmd->param[0]);
			i++;
		}
		cmd->param[0] = param_zero;
	}
	destroy_environ(env);
	return (ret);
}

void	exec_command(t_cmd *cmd, t_arg *arg)
{
	t_env	*e;

	e = get_node_from_envlst(arg->envlst, "PATH");
	if (!e)
		destroy_path(arg);
	else
		update_envpath(arg, e->value);
	if (exec_builtincmd(cmd, arg) == 1)
		return ;
	else if (exec_shellcmd(cmd, arg) == 0)
		return ;
	print_custom_error_exit(ERR_FAILED_TO_EXEC, cmd->param[0], NULL, arg);
}
