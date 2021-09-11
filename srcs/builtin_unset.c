#include "main.h"

int	builtincmd_unset(t_arg *arg, t_cmd *cmd)
{
	int		i;
	int		ret;

	dbg_print_cmdstart(arg, cmd->param[0]);
	dbg_print_str(arg, "=== builtin cmd unset ===\n");
	ret = 0;
	i = 1;
	while (i < cmd->param_cnt)
	{
		if ((size_t)ft_strchr(cmd->param[i], '=') != ft_strlen(cmd->param[i]))
		{
			print_custom_error(
				ERR_NOT_VALID_IDENTIFIER, cmd->param[0], cmd->param[i], arg);
			ret = 1;
		}
		else
		{
			delete_env_from_envlst(&arg->envlst, cmd->param[i]);
			delete_env_from_envlst(&arg->shellenvlst, cmd->param[i]);
		}
		i++;
	}
	return (ret);
}
