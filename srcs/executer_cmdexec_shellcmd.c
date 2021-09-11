#include "main.h"

static int	exec_shellcmd_execve(t_cmd *cmd, t_arg *arg, char **env)
{
	int			ret;
	int			stat_ret;
	struct stat	sb;

	ret = -1;
	stat_ret = stat(cmd->param[0], &sb);
	if (arg->dbg)
		printf("trying to exec...%s (stat() ret:%d, S_ISREG:%d)\n",
			cmd->param[0], stat_ret, S_ISREG(sb.st_mode));
	if (stat_ret == 0 && S_ISREG(sb.st_mode))
	{
		dbg_print_cmdstart(arg, cmd->param[0]);
		ret = execve(cmd->param[0], cmd->param, env);
		if (ret == -1)
			ret = errno;
	}
	return (ret);
}

static int	exec_shellcmd_relativepath(t_cmd *cmd, t_arg *arg, char **env)
{
	int		ret;
	char	*param_zero;

	param_zero = cmd->param[0];
	cmd->param[0] = ft_strjoin(arg->pwd, param_zero + 1);
	ret = exec_shellcmd_execve(cmd, arg, env);
	secure_free(cmd->param[0]);
	cmd->param[0] = param_zero;
	return (ret);
}

static int	exec_shellcmd_with_envpath(t_cmd *cmd, t_arg *arg, char **env)
{
	int		ret;
	char	*param_zero;
	int		i;

	ret = MASK_7BIT;
	i = 0;
	param_zero = cmd->param[0];
	while (ret != 0 && i < arg->path_cnt)
	{
		cmd->param[0] = ft_strjoin3(arg->path[i], "/", param_zero);
		ret = exec_shellcmd_execve(cmd, arg, env);
		secure_free(cmd->param[0]);
		i++;
	}
	cmd->param[0] = param_zero;
	return (ret);
}

int	exec_shellcmd(t_cmd *cmd, t_arg *arg)
{
	int		ret;
	char	**env;

	env = generate_environ(arg);
	if (cmd->param[0][0] == '/')
		ret = exec_shellcmd_execve(cmd, arg, env);
	else if (ft_strncmp(cmd->param[0], "./", 2) == 0)
		ret = exec_shellcmd_relativepath(cmd, arg, env);
	else
		ret = exec_shellcmd_with_envpath(cmd, arg, env);
	destroy_environ(env);
	return (ret);
}
