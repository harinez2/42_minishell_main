#include "main.h"

static void	print_env(t_arg *arg)
{
	t_env		*e;

	e = arg->envlst;
	while (e != NULL)
	{
		printf("%s=%s\n", e->env, e->value);
		e = e->next;
	}
}

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
			break ;
		i++;
	}
}

void	builtincmd_env(t_arg *arg, t_cmd *cmd)
{
	dbg_print_cmdstart(arg, cmd->param[0]);
	dbg_print_str(arg, "=== builtin cmd env ===\n");
	if (cmd->param_cnt == 1)
		print_env(arg);
	else
		add_param(arg, cmd);
}
