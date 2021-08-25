#include "main.h"

void	exec_command(t_cmd *cmd, t_arg *arg)
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
		ret = access(cmd->param[0], X_OK);
		if (ret == 0)
			ret = execve(cmd->param[0], cmd->param, NULL);
		secure_free(cmd->param[0]);
		i++;
	}
	cmd->param[0] = param_zero;
	if (ret != 0)
		error_exit(ERR_FAILED_TO_EXEC, arg);
}
