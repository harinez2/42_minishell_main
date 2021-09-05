#include "main.h"

static void	add_param(t_arg *arg, t_cmd *cmd)
{
	int		i;
	int		eqpos;
	int		paramlen;

	i = 1;
	while (cmd->param[i])
	{
		eqpos = ft_strchr(cmd->param[i], '=');
		paramlen = ft_strlen(cmd->param[i]);
		if (eqpos != paramlen)
			push_back_envlst(&arg->envlst, ft_substr(cmd->param[i], 0, eqpos),
				ft_substr(cmd->param[i], eqpos + 1, paramlen), arg);
		else
		{
			// if included shell vars, add it from shell vars to env vars

			//otherwise
			push_back_envlst(&arg->envlst,
				ft_substr(cmd->param[i], 0, paramlen), NULL, arg);
		}
		i++;
	}
}

void	builtincmd_export(t_arg *arg, t_cmd *cmd)
{
	dbg_print_cmdstart(arg, cmd->param[0]);
	dbg_print_str(arg, "=== builtin cmd export ===\n");
	if (cmd->param_cnt == 1)
		print_env_export(arg);
	else
		add_param(arg, cmd);
}
